#include <QApplication>
#include <QDebug>

#include <QScreen>
#include <QRect>

#include <pthread.h>
#include <wiringPi.h>

#include "sendwindow.h"
#include "recievewindow.h"

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
    // setup GPIO interface - uncomment when needed
    // needs to run with root via sudo in terminal.
    //wiringPiSetup();
    //pinMode (0, OUTPUT);

    // setup Qt GUI
    QApplication a(argc, argv);

    //get screen geometry
    //Andrey @ https://stackoverflow.com/questions/18975734/how-can-i-find-the-screen-desktop-size-in-qt-so-i-can-display-a-desktop-notific
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();

    //creating send window
    sendWindow send;
    send.setWindowTitle("Send Window");
    send.resize(width/3, height/2);
    send.move(width/9, height/4);
    send.show();

    //creating receive window
    recieveWindow recieve;
    recieve.setWindowTitle("Receive Window");
    recieve.resize(width/3, height/2);
    recieve.move(width*5/9, height/4);
    recieve.show();

    // starting worker thread(s)
    int rc;
    pthread_t worker_thread;
    rc = pthread_create(&worker_thread, NULL, worker, (void*)1);
    if (rc) {
        qDebug() << "Unable to start worker thread.";
        exit(1);
    }

    // start window event loop
    qDebug() << "Starting event loop...";
    int ret = a.exec();
    qDebug() << "Event loop stopped.";

    // cleanup pthreads
    pthread_exit(NULL);

    // exit
    return ret;
}
