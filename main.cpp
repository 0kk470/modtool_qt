#include "steam_api.h"
#include "mainwindow.h"
#include <QApplication>
#include <QTimer>

const int frameTime = 33; //30fps update

int frameCount = 0;

void UpdateSteamMessage()
{
    SteamAPI_RunCallbacks();
    ++frameCount;
    //qDebug("Update Steam, frame:%d", frameCount);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QTimer* timer = new QTimer(&w);
    QTimer::connect(timer, &QTimer::timeout, &w, &UpdateSteamMessage);
    timer->start(frameTime);

    return a.exec();
}
