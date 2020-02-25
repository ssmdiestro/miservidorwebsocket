#include <iostream>
#include "ixwebsocket/IXWebSocketServer.h"
#include "ixwebsocket/IXWebSocket.h"
#include "ixwebsocket/IXConnectionState.h"
#include "json.hpp"
#include "usuarios.h"
#include <QSqlDatabase>
#include <QObject>
#include <QDebug>
#include <QSqlError>

using JSON = nlohmann::json;

int g_idMensaje=0;

int dameIdMensaje(){
    g_idMensaje++;
    return g_idMensaje;
}
bool exists(const JSON& json, const std::string& key)
{
    return json.find(key)!=json.end();
}

JSON registro(JSON receivedObject)
{
    if(receivedObject.is_discarded())
    {
        std::cout << "Error" << std::endl;
    }else
    {
        JSON respuesta;
        static bool estaDentro {false};

        respuesta["idServidor"]=dameIdMensaje();
        respuesta["idCliente"]=receivedObject["id"];
        respuesta["hayError"]=false;

        if(exists(receivedObject,"idTarjeta")){
            if(receivedObject["idTarjeta"]!="12345"){
                respuesta["hayError"]=true;
                respuesta["mensaje"]="Tarjeta no valida";
            }else{
               std::string nombre="Samuel";
               respuesta["nombre"]=nombre;
                if (estaDentro)
                {
                    respuesta["mensaje"]="Hasta otra "+nombre;
                    estaDentro=false;
                }else{
                    respuesta["mensaje"]="Bienvenido "+nombre;
                    estaDentro=true;

                }

            }
             return respuesta;
        }
    }



}

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


    ix::WebSocketServer server(9990, "0.0.0.0");
    server.setOnConnectionCallback(
        [&server](std::shared_ptr<ix::WebSocket> webSocket,
                  std::shared_ptr<ix::ConnectionState> connectionState)
        {
            webSocket->setOnMessageCallback(
                [webSocket, connectionState, &server](const ix::WebSocketMessagePtr msg)
                {


                    if (msg->type == ix::WebSocketMessageType::Open)
                    {
                        std::cout << "New connection" << std::endl;
                        Usuarios::modificarUsuario(12345,"Sam","Lopez",0);
                    }
                    else if (msg->type == ix::WebSocketMessageType::Close)
                    {
                        std::cout << "Bye bye connection" << std::endl;
                    }
                    else if (msg->type == ix::WebSocketMessageType::Message)
                    {
                        if (!msg->binary)
                        {
                            /// Text format
                          std::cout << "Received message: " << msg->str << std::endl;
                        }
                        auto receiveObject =JSON::parse(msg->str);

                        auto respuesta=registro(receiveObject).dump();

                        webSocket->send(respuesta);
                         std::cout << "Message Sent: " <<respuesta<< std::endl;

                    }
                }
            );
        }
    );



    auto res = server.listen();
    if (!res.first)
    {
        // Error handling
        return 1;
    }

    server.start();
    server.wait();
    server.stop();



}
