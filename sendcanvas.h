#ifndef SENDCANVAS_H
#define SENDCANVAS_H

#include <QWidget>
#include <QList>
#include <QThread>

#include "queue.h"
#include "serialstruct.h"
#include "drawInformation.h"

class sendCanvas : public QWidget
{
    Q_OBJECT

public:
    sendCanvas(QWidget *parent = nullptr, queue<command> *sQueue = nullptr);

    bool openArea(const QString &file);
    bool saveArea(const QString &file, const char *format);
    bool syncArea();

    // Control pen colour
    QColor penColour();
    void setColour(const QColor &colour);

    // Control pen width
    int penWidth();
    void setPenWidth(int width);

    // Undo Control
    void undo();

signals:
    void syncSignal(QImage sendImage);
    void drawSignal(drawInfoPosition point);
    void drawSignal(drawInfoPen pen);

public slots:
    void clearArea();

protected:
    // Overwrite mouse press events
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

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

#endif // RECIEVEAREA_H
