#ifndef RECIEVEAREA_H
#define RECIEVEAREA_H

#include <QWidget>
#include <QList>

class recieveArea : public QWidget
{
    Q_OBJECT

public:
    recieveArea(QWidget *parent = nullptr);
    ~recieveArea();

    QColor penColour();
    int penWidth();
    Qt::PenCapStyle capStyle();


    //history of edits on the board
    QList<QImage> history;
    int historyLength;

public slots:
    void syncArea();
    void clearArea();
    void undo();

    void setColour(const QColor &colour);
    void setPenWidth(int width);
    void setCapStyle(Qt::PenCapStyle style);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

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
};

#endif // RECIEVEAREA_H
