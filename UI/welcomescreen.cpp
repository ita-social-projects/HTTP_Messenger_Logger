#include "welcomescreen.h"
#include "ui_welcomescreen.h"
#include <fstream>
#include <QFileDialog>
#include <QMessageBox>
#include <QException>
#include <string>
#include <QDropEvent>
#include <QUrl>
#include <QMimeData>
WelcomeScreen::WelcomeScreen(QWidget *parent) :
    BaseWindow(parent),
    ui(new Ui::WelcomeScreen)
{
    ui->setupUi(this);
}

WelcomeScreen::~WelcomeScreen()
{
    delete ui;
    delete m_main_window;
}

void WelcomeScreen::ProcessNewFile(QString path){
    if(m_main_window == nullptr){
        m_main_window = new MainWindow(path);

        m_main_window->show();
        m_main_window->resizeEvent();
        this->hide();
    }else{
        m_main_window->ProcessNewFile(path);
    }
}

void WelcomeScreen::on_open_file_Button_clicked()
{
    QString file = GetNewFilePath();
    if(file != ""){
        ProcessNewFile(file);
    }
}

void WelcomeScreen::on_exit_Button_clicked()
{
    this->hide();
    this->close();
}

