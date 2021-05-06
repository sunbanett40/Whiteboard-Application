/*
Project:    Whiteboard Chat Application - P20 Qt Project
Author:     Joseph Butterworth
License:    This work is licensed under the Creative Commons Attribution-ShareAlike License.
            View this license at https://creativecommons.org/licenses/
*/

#include <QApplication>
#include <QScreen>
#include <QDir>
#include <QDebug>

#include "sendwindow.h"
#include "receivewindow.h"
#include "queue.h"

void* worker(void* thread_id)
{
    //long tid = (long)thread_id;
    // do something....
    //qDebug() << "Worker thread " << tid << "started.";

    // end thread
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    // Setup Qt GUI
    QApplication a(argc, argv);

    // Get screen geometry
    // Andrey @ https://stackoverflow.com/questions/18975734/how-can-i-find-the-screen-desktop-size-in-qt-so-i-can-display-a-desktop-notific
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();

    // Create Queue to pass serial information between threads
    //queue<command> serialQueue(40);

    // Creating send window
    QPixmap sendpix(QDir::currentPath() + "/Icons/send_icon.png");

    sendWindow sendW(nullptr);
    sendW.setWindowIcon(sendpix);
    sendW.setWindowTitle("Send Window");
    sendW.resize(width/3, height/2);
    sendW.move(width/9, height/4);
    sendW.show();

    // Creating receive window
    QPixmap recievepix(QDir::currentPath() + "/Icons/recieve_icon.png");

    receiveWindow receiveW(nullptr);
    receiveW.setWindowIcon(recievepix);
    receiveW.setWindowTitle("Receive Window");
    receiveW.resize(width/3, height/2);
    receiveW.move(width*5/9, height/4);
    receiveW.show();

    QObject::connect(sendW.canvas, SIGNAL(syncSignal(QImage)), receiveW.receive, SLOT(receiveImage(QImage)));

    // Starting worker thread(s)
    int rc;
    pthread_t worker_thread;
    rc = pthread_create(&worker_thread, NULL, worker, (void*)1);
    if (rc) {
        qDebug() << "Unable to start worker thread.";
        exit(1);
    }

    // Start window event loop
    qDebug() << "Starting event loop...";
    int ret = a.exec();
    qDebug() << "Event loop stopped.";

    // Cleanup pthreads
    pthread_exit(NULL);

    // Exit
    return ret;
}
