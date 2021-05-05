#include <QApplication>

#include "receivewindow.h"
#include "receivethread.h"

receiveWindow::receiveWindow(QWidget *parent, queue<command> *sQueue)
    : QMainWindow(parent), receive(new receiveArea(this))
{

    setCentralWidget(receive);

    qApp->setAttribute(Qt::AA_DontShowIconsInMenus, false);

}

receiveWindow::~receiveWindow() = default;

void receiveWindow::receivedSerialStruct(QImage serialData)
{

}
