#include "steam_api.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    if ( !SteamAPI_Init() )
    {
        qDebug( "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed).\n" );
        return 1;
    }
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
