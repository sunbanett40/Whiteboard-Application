#include <QApplication>
#include <QDir>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QMainWindow>
#include <QFileDialog>
#include <QColorDialog>
#include <QInputDialog>
#include <QImageWriter>

#include "sendwindow.h"

sendWindow::sendWindow(QWidget *parent)
    : QMainWindow(parent), draw(new drawArea(this))
{
    setCentralWidget(draw);

    sendWindow::createMenus();
    qApp->setAttribute(Qt::AA_DontShowIconsInMenus, false);
}

sendWindow::~sendWindow() = default;


void sendWindow::createMenus()
{
    //File Menu
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

     //Edit Menu
     QPixmap undopix(QDir::currentPath() + "/Icons/undo.png");
     auto *undo = new QAction(undopix, "&Undo", this);
     undo->setShortcut(tr("CTRL+Z"));

     QMenu *edit = menuBar()->addMenu("&Edit");
     edit->addAction(undo);

     connect(undo, &QAction::triggered, this, &sendWindow::undo);

     //Board Menu
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
     connect(clear, &QAction::triggered, draw, &drawArea::clearArea);

     //Toolbar
     auto *colour = new QAction("&Colour", this);
     auto *width = new QAction("&Pen Width", this);
     auto *capS = new QAction("&Cap Style", this);

     QToolBar *toolbar = addToolBar("main toolbar");
     toolbar->addAction(colour);
     toolbar->addSeparator();
     toolbar->addAction(width);
     toolbar->addAction(capS);

     connect(colour, &QAction::triggered, this, &sendWindow::colour);
     connect(width, &QAction::triggered, this, &sendWindow::penWidth);
     connect(capS, &QAction::triggered, this, &sendWindow::capStyle);
}

void sendWindow::open()
{
        QString fileName = QFileDialog::getOpenFileName(this,
                                   tr("Open File"), QDir::currentPath());
        if (!fileName.isEmpty())
            draw->openArea(fileName);
}

//jank undo
void sendWindow::undo()
{
    draw->undo();

}

void sendWindow::saveas()
{

    //get image file formats
    const QList<QByteArray> imageFormats = QImageWriter::supportedImageFormats();

    //create file filter from QList
    QString fileFilter = "";
    for(const QByteArray &format : imageFormats)
    {
        fileFilter.append(tr("%1 Files (*.%2)").arg(QString::fromLatin1(format).toUpper(), QString::fromLatin1(format)));
        fileFilter.append(";;");
    }
    //qDebug() << fileFilter;

    //set filename from dialog box
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QDir::currentPath() + "/untitled", fileFilter);

    //absolute pain
    char *format = fileName.split(".").last().toUtf8().data();

    //pass to draw area function
    if (!fileName.isEmpty())
        draw->saveArea(fileName, format);
}
void sendWindow::sync()
{}

void sendWindow::colour()
{
    //open colour dialogbox
    QColor newColour = QColorDialog::getColor(draw->penColour());

    //set new colour
    draw->setColour(newColour);
}
void sendWindow::penWidth()
{
    bool ok;

    //get pen width
    int newWidth = QInputDialog::getInt(this, tr("Pen Width"), tr("Select pen width:"),
                                        draw->penWidth(), 1, 50, 1, &ok);
    if (ok)
    {
        draw->setPenWidth(newWidth);
    }
}
void sendWindow::capStyle()
{
    bool ok;

    //List of options
    QMap<QString, Qt::PenCapStyle> styleMap;
    styleMap["Round Cap"] = Qt::RoundCap;
    styleMap["Square Cap"] = Qt::SquareCap;
    styleMap["Rough Cap"] = Qt::FlatCap;

    //get pen style
    QString newCapStyle = QInputDialog::getItem(this, tr("Cap Style"), tr("Select cap style:"),
                                        styleMap.keys(), 1, false, &ok);
    if (ok)
    {
        draw->setCapStyle(styleMap[newCapStyle]);
    }
}

