#ifndef RECEIVEWINDOW_H
#define RECEIVEWINDOW_H

#include <QMainWindow>

#include "receivearea.h"


class receiveWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit receiveWindow(QWidget *parent = nullptr);
    ~receiveWindow();

private:

    receiveArea *receive;
};

#endif // RECEIVEWINDOW_H
