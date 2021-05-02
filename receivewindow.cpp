#include <QApplication>

#include "receivewindow.h"


receiveWindow::receiveWindow(QWidget *parent)
    : QMainWindow(parent), receive(new receiveArea(this))
{
    setCentralWidget(receive);

    qApp->setAttribute(Qt::AA_DontShowIconsInMenus, false);
}

receiveWindow::~receiveWindow() = default;
