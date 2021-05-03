#ifndef RECEIVEWINDOW_H
#define RECEIVEWINDOW_H

#include <QMainWindow>
#include <QThread>

#include "receivearea.h"
#include "serialstruct.h"

class receiveWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit receiveWindow(QWidget *parent = nullptr);
    ~receiveWindow();

signals:
    void startPoll();

public slots:
    void receivedSerialStruct(const command &serialData);

private:

    QThread receiver;
    receiveArea *receive;
};

#endif // RECEIVEWINDOW_H
