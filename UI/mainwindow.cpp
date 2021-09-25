#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QString path_to_file, QWidget *parent)
    : BaseWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    de = new DeSerializer(path_to_file.toStdString());

    SetTable();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete de;
}

void MainWindow::ProcessNewFile(QString file_path){
    de->SetPath(file_path.toStdString());
    SetTable();
}

void MainWindow::SetTable(){
    ui->tableWidget->clear();
    ui->tableWidget->setSortingEnabled(false);

    std::vector<Log> logs = de->GetAllLogs();
    ui->tableWidget->setRowCount(logs.size());
    ui->tableWidget->setColumnCount(AMOUNT_OF_COLS);

    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "TYPE" << "TIME" << "FILE" << "FUNCTION" << "MESSAGE");
    ui->tableWidget->horizontalHeader()->setSectionsClickable(true);

    for(size_t i=0; i<logs.size(); ++i){
        QTableWidgetItem *itm1 = new QTableWidgetItem(QString::fromUtf8(Log::TypeToString(logs.at(i).GetType())));
        ui->tableWidget->setItem(i, 0, itm1);

        QTableWidgetItem *itm2 = new QTableWidgetItem(QString::fromUtf8(logs.at(i).GetTime().c_str()));
        ui->tableWidget->setItem(i, 1, itm2);
        QTableWidgetItem *itm3 = new QTableWidgetItem(QString::fromUtf8(logs.at(i).GetFile().c_str()));
        ui->tableWidget->setItem(i, 2, itm3);
        QTableWidgetItem *itm4 = new QTableWidgetItem(QString::fromUtf8(logs.at(i).GetFunction().c_str()));
        ui->tableWidget->setItem(i, 3, itm4);
        QTableWidgetItem *itm5 = new QTableWidgetItem(QString::fromUtf8(logs.at(i).GetMessage().c_str()));
        ui->tableWidget->setItem(i, 4, itm5);


        if(logs.at(i).GetType() == t_FATAL){
            for(int j=0;j<AMOUNT_OF_COLS; j++){
                ui->tableWidget->item(i, j)->setBackground(QBrush(QColor(140, 22, 28)));
                ui->tableWidget->item(i, j)->setForeground(QBrush(QColor(255, 255, 255)));
            }
        }
        if(logs.at(i).GetType() == t_ERROR){
            for(int j=0;j<AMOUNT_OF_COLS; j++){
                ui->tableWidget->item(i, j)->setBackground(QBrush(QColor(212, 25, 53)));
                ui->tableWidget->item(i, j)->setForeground(QBrush(QColor(255, 255, 255)));
            }
        }
        if(logs.at(i).GetType() == t_DEBUG){
            for(int j=0;j<AMOUNT_OF_COLS; j++){
                ui->tableWidget->item(i, j)->setBackground(QBrush(QColor(153, 153, 0)));
                ui->tableWidget->item(i, j)->setForeground(QBrush(QColor(255, 255, 255)));
            }
        }
        if(logs.at(i).GetType() == t_VERBOSE){
            for(int j=0;j<AMOUNT_OF_COLS; j++){
                ui->tableWidget->item(i, j)->setBackground(QBrush(QColor(18, 90, 153)));
                ui->tableWidget->item(i, j)->setForeground(QBrush(QColor(255, 255, 255)));
            }
        }
    }
    ui->tableWidget->setSortingEnabled(true);
    resizeEvent();

}

void MainWindow::on_open_new_file_Button_clicked()
{
    QString file = GetNewFilePath();
    if(file == ""){
        return;
    }
    de->DeleteAllLogs();
    ProcessNewFile(file);
}


void MainWindow::on_add_file_Button_clicked()
{
    QString file = GetNewFilePath();
    if(file == ""){
        return;
    }
    ProcessNewFile(file);
}

void MainWindow::FilterTable(QString filter_text){
    for( int i = 0; i < ui->tableWidget->rowCount(); ++i )
    {
        bool match = false;
        for( int j = 0; j < ui->tableWidget->columnCount(); ++j )
        {
            QTableWidgetItem *item = ui->tableWidget->item( i, j );
            if( item->text().contains(filter_text) )
            {
                match = true;
                break;
            }
        }
        ui->tableWidget->setRowHidden( i, !match );
    }
}

void MainWindow::UnFilterTable(){
    for( int i = 0; i < ui->tableWidget->rowCount(); ++i )
    {
        ui->tableWidget->setRowHidden( i, false );
    }
}

void MainWindow::on_lineEdit_editingFinished()
{
    QString filter = ui->lineEdit->text();
    if(filter == ""){
        UnFilterTable();
    }else{
        FilterTable(filter);
    }

}

void MainWindow::on_tableWidget_cellDoubleClicked()
{
    UnFilterTable();
}

void MainWindow::FilterTableByColumn(int column, QString filter_text){
    for( int i = 0; i < ui->tableWidget->rowCount(); ++i )
    {
        if(QString::compare(ui->tableWidget->item( i, column )->text(), filter_text , Qt::CaseInsensitive) != 0){
            ui->tableWidget->setRowHidden( i, true );
        }
    }
}

void MainWindow::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    QString filter = item->text();
    FilterTableByColumn(item->column(), filter);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{

    int used_width = 0;
    ui->tableWidget->setColumnWidth(0, 595/8);
    used_width += 595/8;

    ui->tableWidget->setColumnWidth(1, 595/4);
    used_width += 595/4;
    ui->tableWidget->setColumnWidth(2, 595/6);
    used_width += 595/6;
    ui->tableWidget->setColumnWidth(3, ui->tableWidget->width()/2.5);
    used_width += ui->tableWidget->width()/2.5;
    ui->tableWidget->setColumnWidth(4, ui->tableWidget->width() - used_width - 40);
}
