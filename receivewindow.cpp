#include <QApplication>

#include "receivewindow.h"
#include "receivethread.h"

receiveWindow::receiveWindow(QWidget *parent)
    : QMainWindow(parent), receive(new receiveArea(this))
{
    receiveThread *worker = new receiveThread;
        worker->moveToThread(&receiver);
        connect(&receiver, &QThread::finished, worker, &QObject::deleteLater);
        connect(this, &receiveWindow::startPoll, worker, &receiveThread::poll);
        connect(worker, &receiveThread::pulledItem, this, &receiveWindow::receivedItem);
        receiver.start();

    setCentralWidget(receive);

    qApp->setAttribute(Qt::AA_DontShowIconsInMenus, false);
}

receiveWindow::~receiveWindow() = default;
