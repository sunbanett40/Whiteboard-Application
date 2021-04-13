#include <QMouseEvent>
#include <QPainter>
#include <QGuiApplication>

#include "drawarea.h"

drawArea::drawArea(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
}

bool drawArea::openArea(const QString &file)
{
    QImage loadImage;

    //load a new image
    if (loadImage.load(file))
    {
        QSize newSize = loadImage.size().expandedTo(size());
        resizeImage(&loadImage, newSize);

        //set image to loaded image
        drawImage = loadImage;
        update();
        return true;
    }

    return false;
}
bool drawArea::saveArea(const QString &file, const char *format)
{
    //create image and size appropriately
    QImage visibleImage = drawImage;
    resizeImage(&visibleImage, size());

    //save file
    return visibleImage.save(file, format);
}
bool drawArea::syncArea()
{}

QColor drawArea::penColour()
{
    return areaColour;
}
void drawArea::setColour(const QColor &colour)
{
    areaColour = colour;
}
int drawArea::penWidth()
{
    return areaPenWidth;
}
void drawArea::setPenWidth(int width)
{
    areaPenWidth = width;
}
Qt::PenCapStyle drawArea::capStyle()
{
    return areaCapStyle;
}
void drawArea::setCapStyle(Qt::PenCapStyle style)
{
    areaCapStyle = style;
}

void drawArea::clearArea()
{
    //replace screen with blank white canvas
    drawImage.fill(qRgb(255, 255, 255));
    update();
}

void drawArea::mousePressEvent(QMouseEvent *event)
{
    //if left mouse button pressed
    if (event->button() == Qt::LeftButton)
    {
        //save position and start drawing
        prevPoint = event->pos();
        drawing = true;
    }
}
void drawArea::mouseMoveEvent(QMouseEvent *event)
{
    //if drawing is enabled
    if (drawing)
    {
        //draw line to new position
        drawLine(event->pos());
    }
}
void drawArea::mouseReleaseEvent(QMouseEvent *event)
{
    //if left mouse button is released and drawing is enabled
    if ((event->button() == Qt::LeftButton) && drawing)
    {
        //draw line to final position and end drawing
        drawLine(event->pos());
        drawing = false;
    }
}

void drawArea::paintEvent(QPaintEvent *event)
{
    //initiate editable area
    QPainter paintArea(this);
    QRect newRectangle = event->rect();

    //updates drawImage to edited area
    paintArea.drawImage(newRectangle, drawImage, newRectangle);
}
void drawArea::resizeEvent(QResizeEvent *event)
{
    //if resized window is larger
    if (width() > drawImage.width() || height() > drawImage.height())
    {
        //Create new size information
        QSize newSize(qMax(width() + 128, drawImage.width()), qMax(height() + 128, drawImage.height()));

        //and resize the widget to the bigger size
        resizeImage(&drawImage, newSize);
        update();
    }

    QWidget::resizeEvent(event);
}

void drawArea::drawLine(const QPoint &endPoint)
{
    QPainter painter(&drawImage);

    //create pen and draw line
    QPen newPen(areaBrushStyle, areaPenWidth, areaPenStyle, areaCapStyle, Qt::RoundJoin);
    newPen.setColor(areaColour);
    painter.setPen(newPen);
    painter.drawLine(prevPoint, endPoint);

    //maintain radius whilst drawing
    //https://doc.qt.io/qt-5/qtwidgets-widgets-scribble-example.html
    int radius = (areaPenWidth / 2) + 2;
    update(QRect(prevPoint, endPoint).normalized().adjusted(-radius, -radius, +radius, +radius));

    //update point
    prevPoint = endPoint;
}

void drawArea::resizeImage(QImage *image, const QSize &newSize)
{
    //if the image size is different
    if (!(image->size() == newSize))
    {
        //create blank image of the new size
        QImage newImage(newSize, QImage::Format_RGB32);
        newImage.fill(qRgb(255, 255, 255));

        //paint old image to the new image
        QPainter painter(&newImage);
        painter.drawImage(QPoint(0, 0), *image);

        //return new image
        *image = newImage;
    }
}
