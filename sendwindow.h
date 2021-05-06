/*
Project:    Whiteboard Chat Application - P20 Qt Project
Author:     Joseph Butterworth
License:    This work is licensed under the Creative Commons Attribution-ShareAlike License.
            View this license at https://creativecommons.org/licenses/
*/

#ifndef SENDWINDOW_H
#define SENDWINDOW_H

#include <QMainWindow>
#include "drawarea.h"
#include "serialstruct.h"
#include "queue.h"
#include "drawinformation.h"

class sendWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit sendWindow(QWidget *parent = nullptr);
    ~sendWindow();

    void createMenus();

    sendCanvas *canvas;

public slots:
    void open();
    void saveas();
    void sync();

    //super special jank undo (c)
    void undo();

    void colour();
    void penWidth();

private:

};

#endif // SENDWINDOW_H
