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

    bool openArea(const QString &file);
    bool saveArea(const QString &file, const char *format);
    bool syncArea();
    void undo();

    QColor penColour();
    void setColour(const QColor &colour);

    int penWidth();
    void setPenWidth(int width);

    Qt::PenCapStyle capStyle();
    void setCapStyle(Qt::PenCapStyle style);

    //history of edits on the board
    QList<QImage> history;
    int historyLength;

public slots:
    void clearArea();

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
