#include "mainwindow.h"
#include "welcomescreen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    try{
        WelcomeScreen w_screen;
        w_screen.show();
        a.exec();
    }catch(...){

    }
    return 0;
}
