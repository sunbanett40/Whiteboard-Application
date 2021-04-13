#ifndef SENDWINDOW_H
#define SENDWINDOW_H

#include <QMainWindow>

#include "drawarea.h"


class sendWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit sendWindow(QWidget *parent = nullptr);
        void createMenus();
    ~sendWindow();

private:
    drawArea *draw;

};

#endif // SENDWINDOW_H
