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
                JSON res=Usuarios::cargar(userid);
                 std::string nombre =  res["nombre"];
                int regid=Registro::estaDentro(userid);
                 if (regid!=0){
                         Registro::salir(regid);
                         respuesta["mensaje"]="Hasta otra "+nombre;
                 }else{
                     Registro::entrar(userid);
                     respuesta["mensaje"]="Bienvenido "+nombre;;
                 };
            }else{
                respuesta["mensaje"]="Tarjeta no valida";
                respuesta["hayError"]=true;
            };
            respuesta["tipoRespuesta"]="notificacion";
            return respuesta;
}


JSON Server::lista(JSON receivedObject)
{
    JSON respuesta;

    respuesta["idServidor"]=dameIdMensaje();
    respuesta["idCliente"]=receivedObject["id"];
    respuesta["hayError"]=false;
    respuesta["tipoRespuesta"]="lista";
    respuesta["tipoLista"]="todosUsuarios";
    respuesta= Usuarios::listar(respuesta);

    return respuesta;
 }
JSON Server::listareg(JSON receivedObject)
{
    JSON respuesta;

    respuesta["idServidor"]=dameIdMensaje();
    respuesta["idCliente"]=receivedObject["id"];
    respuesta["hayError"]=false;
    respuesta["tipoRespuesta"]="lista";
    respuesta["tipoLista"]="todosRegistros";
    respuesta= Registro::listar(respuesta);
    return respuesta;
 }
JSON Server::listaDentro(JSON receivedObject)
{
    JSON respuesta;

    respuesta["idServidor"]=dameIdMensaje();
    respuesta["idCliente"]=receivedObject["id"];
    respuesta["hayError"]=false;

    respuesta= Registro::listardentro(respuesta);
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
                    respuesta["tipoRespuesta"]="admin";
                    respuesta["mensaje"]="Modo admin";
                    respuesta["administrar"]=true;
                }else{
                    respuesta["tipoRespuesta"]="notificacion";
                    respuesta["mensaje"]="No tienes acceso al modo administrador";
                     respuesta["administrar"]=false;
                     respuesta["hayError"]=true;

                }
            }else{
                respuesta["tipoRespuesta"]="notificacion";
                respuesta["mensaje"]="Tarjeta no valida";
                respuesta["hayError"]=true;

            }

return respuesta;

      }
JSON Server::nuevo(JSON receivedObject)
{
    JSON respuesta;
    respuesta["idServidor"]=dameIdMensaje();
    respuesta["idCliente"]=receivedObject["id"];
    respuesta["hayError"]=false;
    respuesta["creado"]=false;
    int userid=receivedObject["idTarjeta"];
    if(!Usuarios::existe(userid)){
         std::string nom=receivedObject["nombre"];
         QString nombre=QString::fromUtf8(nom.c_str());
         std::string ape=receivedObject["apellidos"];
         QString apellidos=QString::fromUtf8(ape.c_str());
        int admin=receivedObject["admin"];
        Usuarios u(userid,nombre,apellidos,admin);
        u.crearUsuario();
        respuesta["tipoRespuesta"]="notificacion";
        respuesta["mensaje"]="Creado con Exito.";
        respuesta["creado"]=true;
    }else{
        respuesta["tipoRespuesta"]="notificacion";
        respuesta["hayError"]=true;
        respuesta["mensaje"]="Ese usuario ya existe";
    }


return respuesta;

      }

JSON Server::reguser(JSON receivedObject)
{
    JSON respuesta;
    respuesta["idServidor"]=dameIdMensaje();
    respuesta["idCliente"]=receivedObject["id"];
    respuesta["hayError"]=false;

    int userid=receivedObject["idTarjeta"];
    if(Usuarios::existe(userid)){

        respuesta= Registro::listar(respuesta,userid);
    }
    return respuesta;
}
int Server::iniciarServer(){

    ix::WebSocketServer server(9990, "0.0.0.0");
    /*ix::SocketTLSOptions tlsOptions;
    tlsOptions.tls=true;
    tlsOptions.certFile ="./localhost.crt";
            tlsOptions.keyFile="./localhost.key";
            tlsOptions.caFile="NONE";
            if(tlsOptions.isValid())
            {
                std::cerr <<"SSL VALID" << std::endl;
            }
            server.setTLSOptions(tlsOptions);*/

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
                                }else if (receivedObject["tipo"]=="reguser") {
                                    auto respuesta=Server::reguser(receivedObject).dump();
                                    webSocket->send(respuesta);
                                    std::cout << "Message Sent: " <<respuesta<< std::endl;
                                }else if (receivedObject["tipo"]=="listadentro") {
                                    auto respuesta=Server::listaDentro(receivedObject).dump();
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
