#include <QMouseEvent>
#include <QPainter>
#include <QGuiApplication>

#include "receivecanvas.h"
#include "receivethread.h"

receiveCanvas::receiveCanvas(QWidget *parent)
    : QWidget(parent)
{

    receiveThread *worker = new receiveThread();
    worker->moveToThread(&receiver);
    connect(&receiver, &QThread::finished, worker, &QObject::deleteLater);
    //connect(worker, &receiveThread::pulledFromQueue, this, &receiveCanvas::syncSlot);
    receiver.start();

    setAttribute(Qt::WA_StaticContents);
}

receiveCanvas::~receiveCanvas() = default;

void receiveCanvas::clearArea()
{
    // Replace screen with blank white canvas
    drawImage.fill(qRgb(255, 255, 255));
    update();

    // Send draw information to receive window
}

QColor receiveCanvas::penColour()
{
    return areaColour;
}
void receiveCanvas::setColour(const QColor &colour)
{
    areaColour = colour;
}
int receiveCanvas::penWidth()
{
    return areaPenWidth;
}
void receiveCanvas::setPenWidth(int width)
{
    areaPenWidth = width;
}

void receiveCanvas::syncSlot(QImage receiveImage)
{
    QSize newSize = receiveImage.size().expandedTo(size());
    resizeImage(&receiveImage, newSize);

    //set image to loaded image
    drawImage = receiveImage;
    update();
}

void receiveCanvas::paintEvent(QPaintEvent *event)
{
    // Initiate editable area
    QPainter paintArea(this);
    QRect newRectangle = event->rect();

    // Updates sendCanvas to edited area
    paintArea.drawImage(newRectangle, drawImage, newRectangle);
}
void receiveCanvas::resizeEvent(QResizeEvent *event)
{
    // If resized window is larger
    if (width() > drawImage.width() || height() > drawImage.height())
    {
        // Create new size information
        QSize newSize(qMax(width() + 128, drawImage.width()), qMax(height() + 128, drawImage.height()));

        // Then resize the widget to the bigger size
        resizeImage(&drawImage, newSize);
        update();
    }

    QWidget::resizeEvent(event);
}

drawInfoPosition receiveCanvas::setDrawSignalPosition(uint8_t op, QPoint pos)
{
    drawInfoPosition point;
    point.opcode = op;
    point.xPosition = pos.x();
    point.yPosition = pos.y();

    return point;
}
drawInfoPen receiveCanvas::setDrawSignalPen(uint8_t op, int penWidth, QColor penColour)
{
    drawInfoPen pen;
    pen.opcode = op;
    pen.width = penWidth;
    pen.red = penColour.red();
    pen.green = penColour.green();
    pen.blue = penColour.blue();

    return pen;
}

void receiveCanvas::drawLine(const QPoint &endPoint)
{
    QPainter painter(&drawImage);

    // Create pen and draw line
    QPen newPen(areaBrushStyle, areaPenWidth, areaPenStyle, areaCapStyle, Qt::RoundJoin);
    newPen.setColor(areaColour);
    painter.setPen(newPen);
    painter.drawLine(prevPoint, endPoint);

    // Maintain radius whilst drawing
    //https://doc.qt.io/qt-5/qtwidgets-widgets-scribble-example.html
    int radius = (areaPenWidth / 2) + 2;
    update(QRect(prevPoint, endPoint).normalized().adjusted(-radius, -radius, +radius, +radius));

    // Update point
    prevPoint = endPoint;
}
void receiveCanvas::resizeImage(QImage *image, const QSize &newSize)
{
    // If the image size is different
    if (!(image->size() == newSize))
    {
        // Create blank image of the new size
        QImage newImage(newSize, QImage::Format_RGB32);
        newImage.fill(qRgb(255, 255, 255));

        // Paint old image to the new image
        QPainter painter(&newImage);
        painter.drawImage(QPoint(0, 0), *image);

        // Return new image
        *image = newImage;
    }
}
