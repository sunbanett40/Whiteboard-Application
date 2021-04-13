#include <QWidget>

class drawArea : public QWidget
{
    Q_OBJECT

public:
    drawArea(QWidget *parent = nullptr);

    bool openArea(const QString &file);
    bool saveArea(const QString &file, const char *format);
    bool syncArea();

    QColor penColour();
    void setColour(const QColor &colour);

    int penWidth();
    void setPenWidth(int width);

    Qt::PenCapStyle capStyle();
    void setCapStyle(Qt::PenCapStyle style);

public slots:



    void clearArea();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

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
