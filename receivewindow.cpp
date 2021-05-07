#include <QApplication>

#include "receivewindow.h"
#include "receivethread.h"

receiveWindow::receiveWindow(QWidget *parent)
    : QMainWindow(parent), canvas(new receiveCanvas(this))
{
    setCentralWidget(canvas);

    qApp->setAttribute(Qt::AA_DontShowIconsInMenus, false);

    //emit startPoll();
}

receiveWindow::~receiveWindow() = default;

void receiveWindow::receivedSerialStruct(const command &serialData)
{

}
