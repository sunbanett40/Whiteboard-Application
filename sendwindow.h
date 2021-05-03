#ifndef SENDWINDOW_H
#define SENDWINDOW_H

#include <QThread>
#include <QMainWindow>
#include "drawarea.h"
#include "serialstruct.h"

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

    //super special jank undo (c)
    void undo();

    void colour();
    void penWidth();
    void capStyle();

signals:
    void sendCommand(const command &serialData);

private:
    QThread sender;
    drawArea *draw;
};

#endif // SENDWINDOW_H
