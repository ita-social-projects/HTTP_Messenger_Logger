#include <QFileDialog>
#include <QMessageBox>
#include <QDropEvent>
#include <QMimeData>


//#include <QException>
//#include <string>
//#include <QUrl>

#include "BaseWindow.h"

BaseWindow::BaseWindow(QWidget *parent)
    : QMainWindow(parent)
{
setAcceptDrops(true);
}

BaseWindow::~BaseWindow()
{

}

QString BaseWindow::GetNewFilePath()
{
    QString path = QFileDialog::getOpenFileName(this, "Give me your file!", NULL,  "json file (*.json);;ALL files (*)");
    if(!path.contains(".json")){
        QMessageBox messageBox;
        messageBox.warning(0,"Error","You didnt choose .json file.. sorry, we can't read your thoughts");
        messageBox.setStyleSheet("background-color: black; color: white;");
        messageBox.setFixedSize(500,200);
        return "";
    }
    return path;
}

void BaseWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

void BaseWindow::dropEvent(QDropEvent *e)
{
    foreach (const QUrl &url, e->mimeData()->urls()) {
        QString fileName = url.toLocalFile();
        ProcessNewFile(fileName);
    }
}
