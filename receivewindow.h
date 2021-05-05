#ifndef RECEIVEWINDOW_H
#define RECEIVEWINDOW_H

#include <QMainWindow>
#include <QThread>

#include "receivearea.h"
#include "serialstruct.h"
#include "queue.h"

class receiveWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit receiveWindow(QWidget *parent = nullptr, queue<command> *sQueue = nullptr);
    ~receiveWindow();

    receiveArea *receive;

signals:
    void startPoll();

public slots:
    void receivedSerialStruct(const command &serialData);

private:

    QThread receiver;

};

#endif // RECEIVEWINDOW_H
