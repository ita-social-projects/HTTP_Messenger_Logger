#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H


#include "BaseWindow.h"
#include "mainwindow.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class WelcomeScreen;
}
QT_END_NAMESPACE
class WelcomeScreen : public BaseWindow
{
    Q_OBJECT

public:
     WelcomeScreen(QWidget *parent = nullptr);
    ~WelcomeScreen();
    virtual void ProcessNewFile(QString path) override;
private slots:

    void on_open_file_Button_clicked();

    void on_exit_Button_clicked();

private:
    Ui::WelcomeScreen *ui;
    MainWindow *m_main_window = nullptr;
};

#endif // WELCOMESCREEN_H

