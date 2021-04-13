#include <QMouseEvent>
#include <QPainter>

#include "drawarea.h"

drawArea::drawArea(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
}

bool drawArea::openArea(const QString &file)
{}
bool drawArea::saveArea(const QString &file, const char *format)
{}
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
int drawArea::penStyle()
{
    return areaPenStyle;
}
void drawArea::setPenStyle(int style)
{
    areaPenStyle = style;
}
int drawArea::capStyle()
{
    return areaCapStyle;
}
void drawArea::setCapStyle(int style)
{
    areaCapStyle = style;
}
int drawArea::brushStyle()
{
    return areaBrushStyle;
}
void drawArea::setBrushStyle(int style)
{
    areaBrushStyle = style;
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
    if (width() > drawImage.width() || height() > drawImage.height()) {
        int newWidth = qMax(width() + 128, drawImage.width());
        int newHeight = qMax(height() + 128, drawImage.height());
        resizeImage(&drawImage, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void drawArea::drawLine(const QPoint &endPoint)
{
    QPainter painter(&drawImage);
    painter.setPen(QPen(areaColour, areaPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(prevPoint, endPoint);


    int rad = (areaPenWidth / 2) + 2;
    update(QRect(prevPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    prevPoint = endPoint;
}

void drawArea::resizeImage(QImage *image, const QSize &newSize)
{
if (!(image->size() == newSize))
{
    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));

    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);

    *image = newImage;
}}
