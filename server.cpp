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

JSON Server::acceso(JSON receivedObject)
{
    JSON respuesta;

    respuesta["idServidor"]=dameIdMensaje();
    respuesta["idCliente"]=receivedObject["id"];
    respuesta["hayError"]=false;


            int userid=receivedObject["idTarjeta"];
            if(Usuarios::existe(userid)){
                int regid=Registro::estaDentro(userid);
                 if (regid!=0){
                         Registro::salir(regid);
                         respuesta["mensaje"]="Hasta otra";
                 }else{
                     Registro::entrar(userid);
                     respuesta["mensaje"]="Bienvenido";
                 };
            }else{
                respuesta["mensaje"]="Tarjeta no valida";
            };

            return respuesta;
}

JSON Server::registro(JSON receivedObject)
{


      }
JSON Server::lista(JSON receivedObject)
{
    JSON respuesta;

    respuesta["idServidor"]=dameIdMensaje();
    respuesta["idCliente"]=receivedObject["id"];
    respuesta["hayError"]=false;

    respuesta= Usuarios::listar(respuesta);
    return respuesta;
 }
JSON Server::listareg(JSON receivedObject)
{
    JSON respuesta;

    respuesta["idServidor"]=dameIdMensaje();
    respuesta["idCliente"]=receivedObject["id"];
    respuesta["hayError"]=false;

    respuesta= Registro::listar(respuesta);
    return respuesta;
 }
JSON Server::admin(JSON receivedObject)
{
    JSON respuesta;
    respuesta["idServidor"]=dameIdMensaje();
    respuesta["idCliente"]=receivedObject["id"];
    respuesta["hayError"]=false;


            int userid=receivedObject["idTarjeta"];
            if(Usuarios::existe(userid)){
                if(Usuarios::esAdmin(userid)){
                    respuesta["mensaje"]="Modo admin";
                }else{
                    respuesta["mensaje"]="No tienes acceso al modo administrador";
                }
            }else{
                respuesta["mensaje"]="Tarjeta no valida";

            }

return respuesta;

      }
JSON Server::nuevo(JSON receivedObject)
{
    JSON respuesta;
    respuesta["idServidor"]=dameIdMensaje();
    respuesta["idCliente"]=receivedObject["id"];
    respuesta["hayError"]=false;

    int userid=receivedObject["idTarjeta"];
    if(!Usuarios::existe(userid)){
         std::string nom=receivedObject["nombre"];
         QString nombre=QString::fromUtf8(nom.c_str());
         std::string ape=receivedObject["apellidos"];
         QString apellidos=QString::fromUtf8(ape.c_str());
        int admin=receivedObject["admin"];
        Usuarios u(userid,nombre,apellidos,admin);
        u.crearUsuario();

        respuesta["mensaje"]="Creado con Exito.";
    }


return respuesta;

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
                        auto receivedObject =JSON::parse(msg->str);

                        if(receivedObject.is_discarded())
                        {
                            std::cout << "Error" << std::endl;
                        }else
                        {
                            if(exists(receivedObject,"tipo")){
                                if(receivedObject["tipo"]=="acceso"){
                                    auto respuesta=Server::acceso(receivedObject).dump();
                                    webSocket->send(respuesta);
                                    std::cout << "Message Sent: " <<respuesta<< std::endl;
                                }else if (receivedObject["tipo"]=="admin") {
                                    auto respuesta=Server::admin(receivedObject).dump();
                                    webSocket->send(respuesta);
                                    std::cout << "Message Sent: " <<respuesta<< std::endl;
                                }else if (receivedObject["tipo"]=="lista") {
                                    auto respuesta=Server::lista(receivedObject).dump();
                                    webSocket->send(respuesta);
                                    std::cout << "Message Sent: " <<respuesta<< std::endl;
                                }else if (receivedObject["tipo"]=="listareg") {
                                    auto respuesta=Server::listareg(receivedObject).dump();
                                    webSocket->send(respuesta);
                                    std::cout << "Message Sent: " <<respuesta<< std::endl;
                                }else if (receivedObject["tipo"]=="nuevo") {
                                    auto respuesta=Server::nuevo(receivedObject).dump();
                                    webSocket->send(respuesta);
                                    std::cout << "Message Sent: " <<respuesta<< std::endl;
                                }

}
                            }
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
