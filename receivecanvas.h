#ifndef RECEIVECANVAS_H
#define RECEIVECANVAS_H

#include <QWidget>
#include <QList>

#include "drawinformation.h"

class receiveCanvas : public QWidget
{
    Q_OBJECT

public:
    receiveCanvas(QWidget *parent = nullptr);
    ~receiveCanvas();

    void clearArea();

    // Control pen colour
    QColor penColour();
    void setColour(const QColor &colour);

    // Control pen width
    int penWidth();
    void setPenWidth(int width);

public slots:
    void syncSlot(QImage receiveImage);
    //void drawSlot(drawInfoPosition point);
    //void drawSlot(drawInfoPen pen);

protected:

    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    // Converts window information into data Structs
    drawInfoPosition setDrawSignalPosition(uint8_t op, QPoint pos);
    drawInfoPen setDrawSignalPen(uint8_t op, int penWidth, QColor penColour);

private:
    void drawLine(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);

    bool drawing = false;

    QImage drawImage;
    QPoint prevPoint;

    // History of edits on the board for undo function
    int historyLength = 20;
    QList<QImage> undoHistory;

    // Initialising pen with default values
    QColor areaColour = Qt::black;
    int areaPenWidth = 4;
    Qt::PenStyle areaPenStyle = Qt::SolidLine;
    Qt::PenCapStyle areaCapStyle = Qt::SquareCap;
    Qt::BrushStyle areaBrushStyle = Qt::SolidPattern;

};

#endif // RECEIVECANVAS_H
