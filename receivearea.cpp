#include <QMouseEvent>
#include <QPainter>
#include <QGuiApplication>

#include "receivearea.h"

receiveArea::receiveArea(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    historyLength = 20;
}

receiveArea::~receiveArea() = default;

void receiveArea::syncArea()
{}

//Regresses the state of the draw area to the previous snapshot (if available).
void receiveArea::undo()
{
    //Can the draw area be rolled back?
    if (history.count() > 0)
    {
        //Create a painter, overwrite entire image to latest snapshot.
        clearArea();
        drawImage = history.last();
        update();

        //Remove the snapshot we just rolled back to.
        history.removeAt(history.count() - 1);
    }
}

QColor receiveArea::penColour()
{
    return areaColour;
}
void receiveArea::setColour(const QColor &colour)
{
    areaColour = colour;
}
int receiveArea::penWidth()
{
    return areaPenWidth;
}
void receiveArea::setPenWidth(int width)
{
    areaPenWidth = width;
}
Qt::PenCapStyle receiveArea::capStyle()
{
    return areaCapStyle;
}
void receiveArea::setCapStyle(Qt::PenCapStyle style)
{
    areaCapStyle = style;
}

void receiveArea::clearArea()
{
    //replace screen with blank white canvas
    drawImage.fill(qRgb(255, 255, 255));
    update();
}

void receiveArea::paintEvent(QPaintEvent *event)
{
    //initiate editable area
    QPainter paintArea(this);
    QRect newRectangle = event->rect();

    //updates drawImage to edited area
    paintArea.drawImage(newRectangle, drawImage, newRectangle);
}
void receiveArea::resizeEvent(QResizeEvent *event)
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

void receiveArea::drawLine(const QPoint &endPoint)
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

void receiveArea::resizeImage(QImage *image, const QSize &newSize)
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