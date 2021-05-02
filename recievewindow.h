#ifndef RECIEVEWINDOW_H
#define RECIEVEWINDOW_H

#include <QMainWindow>

#include "recievearea.h"


class recieveWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit recieveWindow(QWidget *parent = nullptr);
    ~recieveWindow();

private:

    recieveArea *recieve;
};

#endif // RECIEVEWINDOW_H
