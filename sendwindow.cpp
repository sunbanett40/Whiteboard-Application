/*
Project:    Whiteboard Chat Application - P20 Qt Project
Author:     Joseph Butterworth
License:    This work is licensed under the Creative Commons Attribution-ShareAlike License.
            View this license at https://creativecommons.org/licenses/
*/

#include <QApplication>
#include <QDir>
#include <QFileDialog>
#include <QInputDialog>
#include <QColorDialog>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QImageWriter>

#include "sendwindow.h"
#include "sendthread.h"


sendWindow::sendWindow(QWidget *parent)
    : QMainWindow(parent), canvas(new sendCanvas(this))
{

    setCentralWidget(canvas);

    sendWindow::createMenus();
    qApp->setAttribute(Qt::AA_DontShowIconsInMenus, false);
}

sendWindow::~sendWindow() = default;


void sendWindow::createMenus()
{
    // File Menu
    QPixmap openpix(QDir::currentPath() + "/Icons/open.png");
    auto *open = new QAction(openpix, "&Open", this);
    open->setShortcut(tr("CTRL+O"));

    QPixmap saveaspix(QDir::currentPath() + "/Icons/save_as.png");
    auto *saveas = new QAction(saveaspix, "&Save", this);
    saveas->setShortcut(tr("CTRL+S"));

    QPixmap quitpix(QDir::currentPath() + "/Icons/quit.png");
    auto *quit = new QAction(quitpix, "&Quit", this);
    quit->setShortcut(tr("ALT+F4"));

    QMenu *file = menuBar()->addMenu("&File");
    file->addAction(open);
    file->addAction(saveas);
    file->addSeparator();
    file->addAction(quit);

    connect(open, &QAction::triggered, this, &sendWindow::open);
    connect(saveas, &QAction::triggered, this, &sendWindow::saveas);
    connect(quit, &QAction::triggered, qApp, &QApplication::quit);

    // Edit Menu
    QPixmap undopix(QDir::currentPath() + "/Icons/undo.png");
    auto *undo = new QAction(undopix, "&Undo", this);
    undo->setShortcut(tr("CTRL+Z"));

    QMenu *edit = menuBar()->addMenu("&Edit");
    edit->addAction(undo);

    connect(undo, &QAction::triggered, this, &sendWindow::undo);

    // Board Menu
    QPixmap syncpix(QDir::currentPath() + "/Icons/sync.png");
    auto *sync = new QAction(syncpix, "&Sync", this);
    sync->setShortcut(tr("F5"));

    QPixmap clearpix(QDir::currentPath() + "/Icons/clear.png");
    auto *clear = new QAction(clearpix, "&Clear", this);
    clear->setShortcut(tr("CTRL+N"));

    QMenu *board = menuBar()->addMenu("&Board");
    board->addAction(sync);
    board->addAction(clear);

    connect(open, &QAction::triggered, this, &sendWindow::sync);
    connect(clear, &QAction::triggered, canvas, &sendCanvas::clearArea);

    // Toolbar
    auto *colour = new QAction("&Colour", this);
    auto *width = new QAction("&Pen Width", this);

    QToolBar *toolbar = addToolBar("main toolbar");
    toolbar->addAction(colour);
    toolbar->addSeparator();
    toolbar->addAction(width);

    connect(colour, &QAction::triggered, this, &sendWindow::colour);
    connect(width, &QAction::triggered, this, &sendWindow::penWidth);
}

void sendWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty())
        canvas->openArea(fileName);
}

void sendWindow::undo()
{
    canvas->undo();

}

void sendWindow::saveas()
{
    // Get image file formats
    const QList<QByteArray> imageFormats = QImageWriter::supportedImageFormats();

    // Create file filter from QList
    QString fileFilter = "";
    for(const QByteArray &format : imageFormats)
    {
        fileFilter.append(tr("%1 Files (*.%2)").arg(QString::fromLatin1(format).toUpper(), QString::fromLatin1(format)));
        fileFilter.append(";;");
    }
    //qDebug() << fileFilter;

    // Set filename from dialog box
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QDir::currentPath() + "/untitled", fileFilter);

    // Set fileformat from dialog box
    //absolute pain
    char *format = fileName.split(".").last().toUtf8().data();

    // Pass to draw area function
    if (!fileName.isEmpty())
        canvas->saveArea(fileName, format);
}
void sendWindow::sync()
{
    canvas->syncArea();
}

void sendWindow::colour()
{
    // Open colour dialogbox
    QColor newColour = QColorDialog::getColor(canvas->penColour());

    // Set new colour
    canvas->setColour(newColour);
}
void sendWindow::penWidth()
{
    // Select button
    bool ok;

    // Get pen width
    int newWidth = QInputDialog::getInt(this, tr("Pen Width"), tr("Select pen width:"), canvas->penWidth(), 1, 50, 1, &ok);

    // When button is hit
    if (ok)
    {
        canvas->setPenWidth(newWidth);
    }
}


