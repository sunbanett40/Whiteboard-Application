/*
Project:    Whiteboard Chat Application - P20 Qt Project
Author:     Joseph Butterworth
License:    This work is licensed under the Creative Commons Attribution-ShareAlike License.
            View this license at https://creativecommons.org/licenses/
*/

#include <QPainter>
#include <QPen>
#include <QMouseEvent>

#include "sendthread.h"
#include "sendcanvas.h"
#include "serialstruct.h"

sendCanvas::sendCanvas(QWidget *parent)
    : QWidget(parent)
{

    sendThread *worker = new sendThread();
    worker->moveToThread(&sender);
    connect(&sender, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, SIGNAL(drawSignal(drawInfoPosition)), worker, SLOT(pushSerialStruct(drawInfoPosition)));
    connect(this, SIGNAL(drawSignal(drawInfoPen)), worker, SLOT(pushSerialStruct(drawInfoPen)));
    sender.start();


    setAttribute(Qt::WA_StaticContents);
}

bool sendCanvas::openArea(const QString &file)
{
    QImage loadImage;

    // Load a new image
    if (loadImage.load(file))
    {
        QSize newSize = loadImage.size().expandedTo(size());
        resizeImage(&loadImage, newSize);

        // Set canvas image to loaded image
        drawImage = loadImage;
        update();

        // Tell receiveWindow to do the same
        emit syncSignal(loadImage);

        return true;
    }

    return false;
}
bool sendCanvas::saveArea(const QString &file, const char *format)
{
    // Create image and size appropriately
    QImage visibleImage = drawImage;
    resizeImage(&visibleImage, size());

    // Save file
    return visibleImage.save(file, format);
}
bool sendCanvas::syncArea()
{
    emit syncSignal(drawImage);
}

QColor sendCanvas::penColour()
{
    return areaColour;
}
void sendCanvas::setColour(const QColor &colour)
{
    areaColour = colour;
    drawInfoPen sendItem = setDrawSignalPen(opcodes::setPen, sendCanvas::penWidth(), sendCanvas::penColour());
    emit drawSignal(sendItem);
}
int sendCanvas::penWidth()
{
    return areaPenWidth;
}
void sendCanvas::setPenWidth(int width)
{
    areaPenWidth = width;
    drawInfoPen sendItem = setDrawSignalPen(opcodes::setPen, sendCanvas::penWidth(), sendCanvas::penColour());
    emit drawSignal(sendItem);
}

void sendCanvas::undo()
{
    // Regresses the state of the draw area to the previous snapshot (if available).

    // Can the draw area be rolled back?
    if (undoHistory.count() > 0)
    {
        // Create a painter, overwrite entire image to latest snapshot.
        clearArea();
        drawImage = undoHistory.last();
        update();

        // Remove the snapshot we just rolled back to.
        undoHistory.removeAt(undoHistory.count() - 1);

        emit syncSignal(drawImage);
    }
}

void sendCanvas::clearArea()
{
    // Replace screen with blank white canvas
    drawImage.fill(qRgb(255, 255, 255));
    update();

    // Send draw information to receive window
    emit syncSignal(drawImage);
}

void sendCanvas::mousePressEvent(QMouseEvent *event)
{
    // Snapshot the canvas (jank mode engage)
    undoHistory.append(drawImage.copy());
    if (undoHistory.count() > historyLength)
    {
        undoHistory.removeAt(0);
    }

    // If left mouse button pressed
    if (event->button() == Qt::LeftButton)
    {
        // Save position and start drawing
        prevPoint = event->pos();
        drawing = true;
    }

    // Send draw information to receive window
    drawInfoPosition sendItem = setDrawSignalPosition(opcodes::pressEvent, event->pos());
    emit drawSignal(sendItem);
}
void sendCanvas::mouseMoveEvent(QMouseEvent *event)
{
    // If drawing is enabled
    if (drawing)
    {
        // Draw line to new position
        drawLine(event->pos());

        // Send draw information to receive window
        drawInfoPosition sendItem = setDrawSignalPosition(opcodes::moveEvent, event->pos());
        emit drawSignal(sendItem);

        // Remove when thread communication works
        emit syncSignal(drawImage);
    }
}
void sendCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    // If left mouse button is released and drawing is enabled
    if ((event->button() == Qt::LeftButton) && drawing)
    {
        // Draw line to final position and end drawing
        drawLine(event->pos());

        // Send draw information to receive window
        drawInfoPosition sendItem = setDrawSignalPosition(opcodes::releaseEvent, event->pos());
        emit drawSignal(sendItem);

        // Remove when thread communication works
        emit syncSignal(drawImage);

        drawing = false;
    }
}

void sendCanvas::paintEvent(QPaintEvent *event)
{
    // Initiate editable area
    QPainter paintArea(this);
    QRect newRectangle = event->rect();

    // Updates sendCanvas to edited area
    paintArea.drawImage(newRectangle, drawImage, newRectangle);
}
void sendCanvas::resizeEvent(QResizeEvent *event)
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

drawInfoPosition sendCanvas::setDrawSignalPosition(uint8_t op, QPoint pos)
{
    drawInfoPosition point;
    point.opcode = op;
    point.xPosition = pos.x();
    point.yPosition = pos.y();

    return point;
}
drawInfoPen sendCanvas::setDrawSignalPen(uint8_t op, int penWidth, QColor penColour)
{
    drawInfoPen pen;
    pen.opcode = op;
    pen.width = penWidth;
    pen.red = penColour.red();
    pen.green = penColour.green();
    pen.blue = penColour.blue();

    return pen;
}

void sendCanvas::drawLine(const QPoint &endPoint)
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
void sendCanvas::resizeImage(QImage *image, const QSize &newSize)
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
