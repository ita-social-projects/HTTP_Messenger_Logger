#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTableWidget>

#include "BaseWindow.h"
#include "../src/DeSerializer.h"

#define AMOUNT_OF_COLS 5

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public BaseWindow
{
    Q_OBJECT

public:
    MainWindow(QString path_to_file, QWidget *parent = nullptr);
    ~MainWindow();
    void ProcessNewFile(QString path) override;
    void SetTable();
    void FilterTable(QString filter_text);
    void UnFilterTable();
    void FilterTableByColumn(int column, QString filter_text);
    void resizeEvent(QResizeEvent* event = nullptr) override;
private slots:
    void on_open_new_file_Button_clicked();
    void on_add_file_Button_clicked();
    void on_lineEdit_editingFinished();
    void on_tableWidget_cellDoubleClicked();

    void on_tableWidget_itemClicked(QTableWidgetItem *item);

private:
    Ui::MainWindow *ui;
    DeSerializer *de;
};
#endif // MAINWINDOW_H
