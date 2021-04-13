#ifndef SENDWINDOW_H
#define SENDWINDOW_H

#include <QMainWindow>

#include "drawarea.h"


class sendWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit sendWindow(QWidget *parent = nullptr);
        void createMenus();
    ~sendWindow();

public slots:
        void open();
        void saveas();
        void sync();

        void colour();
        void penWidth();
        void penStyle();
        void capStyle();
        void brushStyle();

private:
    bool saveFile(const QByteArray &format);

    drawArea *draw;
};

#endif // SENDWINDOW_H
