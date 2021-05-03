#include <QApplication>

#include "receivewindow.h"
#include "receivethread.h"

receiveWindow::receiveWindow(QWidget *parent, queue<command> *sQueue)
    : QMainWindow(parent), receive(new receiveArea(this))
{
    command serialData;

    receiveThread *worker = new receiveThread(sQueue);
    worker->moveToThread(&receiver);
    connect(&receiver, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &receiveWindow::startPoll, worker, &receiveThread::pullSerialStruct);
    connect(worker, &receiveThread::pulledSerialStruct, this, &receiveWindow::receivedSerialStruct);
    receiver.start();

    setCentralWidget(receive);

    qApp->setAttribute(Qt::AA_DontShowIconsInMenus, false);

    emit startPoll();
}

receiveWindow::~receiveWindow() = default;

void receiveWindow::receivedSerialStruct(const command &serialData)
{

}
