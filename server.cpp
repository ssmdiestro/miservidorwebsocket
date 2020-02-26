#include "server.h"
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

Server::Server()
{

}

static int g_idMensaje=0;
using JSON = nlohmann::json;

int Server::dameIdMensaje(){
    g_idMensaje++;
    return g_idMensaje;
}

bool Server::exists(const JSON& json, const std::string& key)
{
    return json.find(key)!=json.end();
}

JSON Server::registro(JSON receivedObject)
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
int Server::iniciarServer(){

    ix::WebSocketServer server(9990, "0.0.0.0");
    server.setOnConnectionCallback(
        [&server,this](std::shared_ptr<ix::WebSocket> webSocket,
                  std::shared_ptr<ix::ConnectionState> connectionState)
        {
            webSocket->setOnMessageCallback(
                [webSocket, connectionState, &server,this](const ix::WebSocketMessagePtr msg)
                {
                    if (msg->type == ix::WebSocketMessageType::Open)
                    {
                        std::cout << "New connection" << std::endl;
                        int userid=123;
                       int id=Registro::estaDentro(userid);
                        if (id!=0){
                                Registro::salir(id);
                        }else{
                            Registro::entrar(userid);
                        };

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

                        auto respuesta=Server::registro(receiveObject).dump();

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
