#include <QImage>

#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent) :
    QMainWindow(parent){

    //creating an empty image, making it white
    QImage image;
    image = QImage(600,400,QImage::Format_RGB32);
    image.fill(qRgb(255,255,255));
};
 /*   ui(new Ui::Window)
{
    ui->setupUi(this);
}
*/
Window::~Window()
{
    delete ui;
}
