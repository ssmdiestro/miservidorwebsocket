#include <iostream>
#include "ixwebsocket/IXWebSocketServer.h"
#include "ixwebsocket/IXWebSocket.h"
#include "ixwebsocket/IXConnectionState.h"
#include "json.hpp"
#include "usuarios.h"
#include "registro.h"
#include <QSqlDatabase>
#include <QObject>
#include <QDebug>
#include <QSqlError>
#include "server.h"
#include <QTranslator>
#include <QCoreApplication>
#include <QFile>
#include <QString>
#include <QIODevice>




int main(int argc, char *argv[])
{
    //Soporte de idioma
    QCoreApplication app(argc,argv);
    QTranslator traductor;
    if (traductor.load("traductor_en_US","./"))
    {
        //QLocale::system().name()
        app.installTranslator(&traductor);
    }
    Server servidor;
    //Inicializacion del servidor
    servidor.iniciarServer();
}
