#include <QFileDialog>
#include <QMessageBox>
#include <QDropEvent>
#include <QMimeData>

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
    QString path = QFileDialog::getOpenFileName(this, "Give me your file!", NULL,  "txt file (*.txt);;ALL files (*)");
    if(!path.contains(".txt")){
        QMessageBox messageBox;
        messageBox.warning(0,"Error","You didnt choose file.. sorry, we can't read your thoughts");
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
