#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QWidget>
#include <QList>
#include <QThread>

#include "queue.h"
#include "serialstruct.h"

class drawArea : public QWidget
{
    Q_OBJECT

public:
    drawArea(QWidget *parent = nullptr, queue<command> *sQueue = nullptr);

    bool openArea(const QString &file);
    bool saveArea(const QString &file, const char *format);
    bool syncArea();
    void undo();

    QColor penColour();
    void setColour(const QColor &colour);

    int penWidth();
    void setPenWidth(int width);
    
    //history of edits on the board
    QList<QImage> history;
    int historyLength;

public slots:
    void clearArea();
signals:
    void sendCommand(const command &serialData);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    command setSerialStruct(uint8_t op, QPoint pos);
    command setSerialStruct(uint8_t op, int penWidth, QColor penColour);
    command setSerialStruct(uint8_t op);

private:
    void drawLine(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);

    bool drawing = false;

    QImage drawImage;
    QPoint prevPoint;

    QColor areaColour = Qt::black;
    int areaPenWidth = 4;
    Qt::PenStyle areaPenStyle = Qt::SolidLine;
    Qt::PenCapStyle areaCapStyle = Qt::SquareCap;
    Qt::BrushStyle areaBrushStyle = Qt::SolidPattern;

    QThread sender;
};

#endif // RECIEVEAREA_H
