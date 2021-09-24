#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QMainWindow>

class BaseWindow : public QMainWindow
{
    Q_OBJECT

public:
    BaseWindow(QWidget *parent = nullptr);
    ~BaseWindow();

    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);
    virtual void ProcessNewFile(QString path) = 0;

    QString GetNewFilePath();
private:
};
#endif // BASEWINDOW_H
