#include "server.h"
#include <iostream>
#include "./websocket/include/ixwebsocket/IXWebSocketServer.h"
#include "./websocket/include/ixwebsocket/IXWebSocket.h"
#include "./websocket/include/ixwebsocket/IXConnectionState.h"
#include "json.hpp"
#include "usuarios.h"
#include "registro.h"
#include <QSqlDatabase>
#include <QObject>
#include <QDebug>
#include <QSqlError>
#include <QFile>
Server::Server()
{

}

static int g_idMensaje=0;
static QSqlDatabase db;
using JSON = nlohmann::json;

//Se genera un ID de conexion que relaciona al cliente con el servidor
int Server::dameIdMensaje(){
    g_idMensaje++;
    return g_idMensaje;
}
void Server::processLine(std::string line)
{
    std::string newLine = line.substr(0, line.rfind("\n"));
    std::string clave = line.substr(0, newLine.rfind("="));
    std::string valor = newLine.substr(newLine.rfind("=")+1, newLine.size());
    prop[clave]=valor;
}

void Server::readFile()
{

    QString nombreArchivo ="./baseDatos.conf";
    if(QFile::exists(nombreArchivo))
    {
        QFile file(nombreArchivo);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            while(!file.atEnd())
            {
                std::string line= QString(file.readLine()).toUtf8().constData();
                processLine(line);
            }
        }
    }else {
        exit(0);
    }
}
void Server::loadProperties()
{
    readFile();
    m_hostname= QString::fromUtf8(prop["hostname"].c_str());
    m_database= QString::fromUtf8(prop["database"].c_str());
    m_port= QString::fromUtf8(prop["port"].c_str());
    m_userName= QString::fromUtf8(prop["userName"].c_str());
    m_password= QString::fromUtf8(prop["password"].c_str());
}
QSqlDatabase Server::conectar(){
    //Conexion con la base de datos

    loadProperties();
    db =(QSqlDatabase::addDatabase("QPSQL"));
    db.setHostName(m_hostname);
    db.setPort(5432);
    db.setDatabaseName(m_database);
    db.setUserName(m_userName);
    db.setPassword(m_password);
    bool ok =db.open();
    if(!ok)
    {
        qDebug()<< QObject::tr("Error al iniciar la base de datos");
        qDebug()<< QObject::tr("Error");
        qDebug()<< db.lastError().text();
    }else{
        qDebug() << QObject::tr("Base de datos iniciada correctamente");
        return db;
    }
}


bool Server::exists(const JSON& json, const std::string& key)
{
    return json.find(key)!=json.end();
}
//Mensaje JSON que solicita añadir un nuevo registro cuando un usuario entra con su clave
//o añadirle hora de salida si el Usuario ya estaba dentro
JSON Server::acceso(JSON receivedObject)
{
    JSON respuesta;
    respuesta["idServidor"]=dameIdMensaje();
    respuesta["idCliente"]=receivedObject["id"];
    respuesta["hayError"]=false;
    int userid=receivedObject["idTarjeta"];
    if(Usuarios::existe(userid,db))
    {
        JSON res=Usuarios::cargar(userid, db);
        std::string nombre =  res["nombre"];
        int regid=Registro::estaDentro(userid,db);
         if (regid!=0)
         {
             Registro::salir(regid,db);
             respuesta["mensaje"]="Hasta otra "+nombre;
         }else
         {
             Registro::entrar(userid,db);
             respuesta["mensaje"]="Bienvenido/a "+nombre;
         };
    }else
    { //Si el numero de Id no corresponde con un Usuario devuelve un error
        respuesta["mensaje"]="Tarjeta no valida";
        respuesta["hayError"]=true;
    };
    respuesta["tipoRespuesta"]="notificacion";
    return respuesta;
}
//Mensaje JSON que solicita listar todos los usuarios
JSON Server::lista(JSON receivedObject)
{
    JSON respuesta;

    respuesta["idServidor"]=dameIdMensaje();
    respuesta["idCliente"]=receivedObject["id"];
    respuesta["hayError"]=false;
    respuesta["tipoRespuesta"]="lista";
    respuesta["tipoLista"]="todosUsuarios";
    respuesta= Usuarios::listar(respuesta,db);

    return respuesta;
 }
//Mensaje JSON que solicita listar todos los registros
JSON Server::listareg(JSON receivedObject)
{
    JSON respuesta;

    respuesta["idServidor"]=dameIdMensaje();
    respuesta["idCliente"]=receivedObject["id"];
    respuesta["hayError"]=false;
    respuesta["tipoRespuesta"]="lista";
    respuesta["tipoLista"]="todosRegistros";
    respuesta= Registro::listar(respuesta,db);
    return respuesta;
 }
//Mensaje JSON que solicita listar todos los usuarios que estan dentro
JSON Server::listaDentro(JSON receivedObject)
{
    JSON respuesta;

    respuesta["idServidor"]=dameIdMensaje();
    respuesta["idCliente"]=receivedObject["id"];
    respuesta["hayError"]=false;
    respuesta["tipoRespuesta"]="lista";
    respuesta["tipoLista"]="usuariosDentro";

    respuesta= Registro::listardentro(respuesta,db);
    return respuesta;

 }
//Mensaje JSON que solicita entrar en el panel de administracion si el usuario tiene dichos privilegios
JSON Server::admin(JSON receivedObject)
{
    JSON respuesta;
    respuesta["idServidor"]=dameIdMensaje();
    respuesta["idCliente"]=receivedObject["id"];
    respuesta["hayError"]=false;
    int userid=receivedObject["idTarjeta"];
    if(Usuarios::existe(userid,db))
    {
        if(Usuarios::esAdmin(userid,db))
        {
            respuesta["tipoRespuesta"]="admin";
            respuesta["mensaje"]="Modo admin";
            respuesta["administrar"]=true;
        }else
        {
            respuesta["tipoRespuesta"]="notificacion";
            respuesta["mensaje"]="No tienes acceso al modo administrador";
             respuesta["administrar"]=false;
             respuesta["hayError"]=true;
        }
    }else
    {
        respuesta["tipoRespuesta"]="notificacion";
        respuesta["mensaje"]="Tarjeta no valida";
        respuesta["hayError"]=true;
    }
    return respuesta;
}
//Mensaje JSON que solicita añadir un nuevo Usuario a la base de datos
JSON Server::nuevo(JSON receivedObject)
{
    JSON respuesta;
    respuesta["idServidor"]=dameIdMensaje();
    respuesta["idCliente"]=receivedObject["id"];
    respuesta["hayError"]=false;
    respuesta["creado"]=false;
    int userid=receivedObject["idTarjeta"];
    if(!Usuarios::existe(userid,db))//Comprueba previamente si ese numero de Id ya existe
    {
         std::string nom=receivedObject["nombre"];
         QString nombre=QString::fromUtf8(nom.c_str());
         std::string ape=receivedObject["apellidos"];
         QString apellidos=QString::fromUtf8(ape.c_str());
        int admin=receivedObject["admin"];
        Usuarios u(userid,nombre,apellidos,admin);
        u.crearUsuario(db);
        respuesta["tipoRespuesta"]="notificacion";
        respuesta["mensaje"]="Creado con Exito.";
        respuesta["creado"]=true;
    }else
    {
        respuesta["tipoRespuesta"]="notificacion";
        respuesta["hayError"]=true;
        respuesta["mensaje"]="Ese usuario ya existe";
    }   
    return respuesta;
}
//Mensaje JSON que solicita listar todos los registros de un usuario en concreto mediante su ID
JSON Server::reguser(JSON receivedObject)
{
    JSON respuesta;
    respuesta["idServidor"]=dameIdMensaje();
    respuesta["idCliente"]=receivedObject["id"];
    respuesta["hayError"]=false;
    int userid=receivedObject["idTarjeta"];
    if(Usuarios::existe(userid,db))//Comprueba previamente si ese numero de Id existe
    {

        respuesta["tipoRespuesta"]="lista";
        respuesta["tipoLista"]="userIdLista";
        respuesta= Registro::listar(respuesta,userid,db);
    }else
    {
        respuesta["tipoRespuesta"]="notificacion";
        respuesta["mensaje"]="Usuario no existente";
        respuesta["hayError"]=true;
    }
    return respuesta;
}
//Se inicializa el servidor
int Server::iniciarServer(){

    db=conectar();


    ix::WebSocketServer server(9990, "0.0.0.0");
    //No pude hacer que esto funcionase
    //
    //
   /*ix::SocketTLSOptions tlsOptions;
    tlsOptions.tls=true;
    tlsOptions.certFile ="/home/usuario/Escritorio/localhost.crt";
            tlsOptions.keyFile="/home/usuario/Escritorio/localhost.key";
            tlsOptions.caFile="NONE";
            if(tlsOptions.isValid())
            {
                std::cerr <<"SSL VALID" << std::endl;
            }
            server.setTLSOptions(tlsOptions);*/
    //
    //

server.setOnConnectionCallback(
    [&server,this](std::shared_ptr<ix::WebSocket> webSocket,
    std::shared_ptr<ix::ConnectionState> connectionState)
    {
        webSocket->setOnMessageCallback(
            [webSocket, connectionState, &server,this](const ix::WebSocketMessagePtr msg)
            {
                if (msg->type == ix::WebSocketMessageType::Open)
                {
                    qDebug() << QObject::tr("Nueva conexión establecida");


                }
                else if (msg->type == ix::WebSocketMessageType::Close)
                {
                    qDebug() << QObject::tr("Conexión finalizada");
                }
                else if (msg->type == ix::WebSocketMessageType::Message)
                {
                    if (!msg->binary)
                    {
                      qDebug() << QObject::tr("Mensaje recibido:");
                      std::cout << msg->str << std::endl;
                    }
                    auto receivedObject =JSON::parse(msg->str);

                    if(receivedObject.is_discarded())
                    {
                        qDebug() << QObject::tr("Error:");
                    }else
                    {   //Comprueba si el JSON recibido tiene el campo "tipo"
                        if(exists(receivedObject,"tipo"))
                        {   //En caso afirmativo comprueba que tipo de respuesta para realizar una funcion u otra.
                            qDebug() << QObject::tr("Mensaje enviado: ");
                            if(receivedObject["tipo"]=="acceso")
                            {
                                auto respuesta=Server::acceso(receivedObject).dump();
                                webSocket->send(respuesta);
                                std::cout  <<respuesta<< std::endl;
                            }else if (receivedObject["tipo"]=="admin")
                            {
                                auto respuesta=Server::admin(receivedObject).dump();
                                webSocket->send(respuesta);
                                std::cout  <<respuesta<< std::endl;
                            }else if (receivedObject["tipo"]=="lista")
                            {
                                auto respuesta=Server::lista(receivedObject).dump();
                                webSocket->send(respuesta);
                                std::cout  <<respuesta<< std::endl;
                            }else if (receivedObject["tipo"]=="listareg")
                            {
                                auto respuesta=Server::listareg(receivedObject).dump();
                                webSocket->send(respuesta);
                                std::cout <<respuesta<< std::endl;
                            }else if (receivedObject["tipo"]=="nuevo")
                            {
                                auto respuesta=Server::nuevo(receivedObject).dump();
                                webSocket->send(respuesta);
                                std::cout  <<respuesta<< std::endl;
                            }else if (receivedObject["tipo"]=="reguser")
                            {
                                auto respuesta=Server::reguser(receivedObject).dump();
                                webSocket->send(respuesta);
                                std::cout <<respuesta<< std::endl;
                            }else if (receivedObject["tipo"]=="listadentro")
                            {
                                auto respuesta=Server::listaDentro(receivedObject).dump();
                                webSocket->send(respuesta);
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
