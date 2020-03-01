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
    //Conexion con la base de datos
    QSqlDatabase db;
    db =(QSqlDatabase::addDatabase("QPSQL"));
    db.setHostName("localhost");
    db.setPort(5432);
    db.setDatabaseName("controlAccesoDB");
    db.setUserName("postgres");
    db.setPassword("");

    bool ok =db.open();
    if(!ok)
    {
        qDebug()<< QObject::tr("Error al iniciar la base de datos");
        qDebug()<< QObject::tr("Error");
        qDebug()<< db.lastError().text();
    }else{
        qDebug() << QObject::tr("Base de datos iniciada correctamente");
    }
    Server servidor;
    //Inicializacion del servidor
    servidor.iniciarServer();


}
