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

    int penStyle();
    void setPenStyle(int style);

    int capStyle();
    void setCapStyle(int style);

    int brushStyle();
    void setBrushStyle(int style);

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
    int areaPenStyle = 1;
    int areaCapStyle = 1;
    int areaBrushStyle = 1;
};
