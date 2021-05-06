#ifndef RECEIVEWINDOW_H
#define RECEIVEWINDOW_H

#include <QMainWindow>
#include <QThread>

#include "receivecanvas.h"
#include "serialstruct.h"
#include "queue.h"

class receiveWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit receiveWindow(QWidget *parent = nullptr);
    ~receiveWindow();

    receiveCanvas *canvas;

signals:
    //void startPoll();

public slots:
    void receivedSerialStruct(const command &serialData);

private:

    QThread receiver;

};

#endif // RECEIVEWINDOW_H
