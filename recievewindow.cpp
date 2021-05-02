#include <QApplication>

#include "recievewindow.h"


recieveWindow::recieveWindow(QWidget *parent)
    : QMainWindow(parent), recieve(new recieveArea(this))
{
    setCentralWidget(recieve);

    qApp->setAttribute(Qt::AA_DontShowIconsInMenus, false);
}

recieveWindow::~recieveWindow() = default;
