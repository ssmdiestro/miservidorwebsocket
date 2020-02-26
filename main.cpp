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


int main(int argc, char *argv[])
{
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
        qDebug()<< "Error al iniciar la base de datos";
        std::cout << "error" << std::endl;
        qDebug()<< db.lastError().text();
    }else{
        std::cout << "Biien" << std::endl;
    }
    Server servidor;
    //Inicializacion del servidor
    servidor.iniciarServer();


}
