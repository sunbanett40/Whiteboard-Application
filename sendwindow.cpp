#include <QApplication>
#include <QDir>
#include <QMenu>
#include <QMenuBar>
#include <QAction>

#include "sendwindow.h"

sendWindow::sendWindow()
{
    QPixmap saveaspix(QDir::currentPath() + "/save_as.png");
    auto *saveas = new QAction(saveaspix, "&Save", this);
    saveas->setShortcut(tr("CTRL+S"));

    QPixmap syncpix(QDir::currentPath() + "/sync.png");
    auto *sync = new QAction(syncpix, "&Sync", this);
    sync->setShortcut(tr("F5"));

    QPixmap clearpix(QDir::currentPath() + "/clear.png");
    auto *clear = new QAction(clearpix, "&Clear", this);
    clear->setShortcut(tr("CTRL+N"));

    QPixmap quitpix(QDir::currentPath() + "/quit.png");
    auto *quit = new QAction(quitpix, "&Quit", this);
    quit->setShortcut(tr("ALT+F4"));

    QMenu *file = menuBar()->addMenu("&File");
    file->addAction(saveas);
    file->addSeparator();
    file->addAction(sync);
    file->addAction(clear);
    file->addSeparator();
    file->addAction(quit);


    qApp->setAttribute(Qt::AA_DontShowIconsInMenus, false);

    connect(saveas, SIGNAL(triggered()), this, SLOT(solveSudoku()));
    connect(quit, &QAction::triggered, qApp, &QApplication::quit);
}
