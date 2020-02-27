#include "usuarios.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>
#include <string>
#include <QVariant>
#include <QString>
#include "json.hpp"

using JSON = nlohmann::json;

Usuarios::Usuarios(int usuarioId,QString nombre,QString apellidos,int admin)
{
    this->m_usuarioId=usuarioId;
    this->m_nombre =nombre;
    this->m_apellidos =apellidos;
    this->m_admin =admin;

}

void Usuarios::crearUsuario()
{
    QSqlQuery query;
    query.prepare("INSERT into usuarios (numid,nombre,apellidos,admin) VALUES (:numid,:nombre,:apellidos,:admin)");
    query.bindValue(":numid", m_usuarioId);
    query.bindValue(":nombre", m_nombre);
    query.bindValue(":apellidos", m_apellidos);
    query.bindValue(":admin", m_admin);
    query.exec();

}

void Usuarios::eliminarUsuario(int id)
{
    QSqlQuery query;
    query.prepare("DELETE from usuarios where numid=:numid");
    query.bindValue(":numid", id);
    query.exec();
}


void Usuarios::modificarUsuario(int id,QString nombre,QString apellidos,int admin)
{
    QSqlQuery query;
    query.prepare("UPDATE usuarios SET nombre = :nombre,apellidos = :apellidos,admin = :admin WHERE numid=:numid");
    query.bindValue(":numid", id);
    query.bindValue(":nombre", nombre);
    query.bindValue(":apellidos", apellidos);
    query.bindValue(":admin", admin);
    query.exec();

}
bool Usuarios::existe(int id)
{
    bool result =false;
    QSqlQuery query;
    query.prepare("SELECT numid from usuarios where numid = :numid");
    query.bindValue(":numid", id);

    if (query.exec()){
        if (query.size()>0) result =true;
    }
    return result;
}
bool Usuarios::esAdmin(int id)
{
    QSqlQuery query;
    query.prepare("SELECT admin from usuarios where numid = :numid");
    query.bindValue(":numid", id);
    query.exec();
    query.next();
    int adminCode = query.value("admin").toInt();
    if (adminCode==1){
        return true;
    }else{
        return false;
    }

}
JSON Usuarios::listar(JSON respuesta){
    QSqlQuery query;
    query.prepare("select * from usuarios");
    query.exec();
    respuesta["resultados"]=query.size();
    while(query.next())
    {
        JSON entradaUsuario;
        entradaUsuario["numid"]=query.value("numid").toString().toStdString();
        entradaUsuario["nombre"]=query.value("nombre").toString().toStdString();
        entradaUsuario["apellidos"]=query.value("apellidos").toString().toStdString();
        entradaUsuario["admin"]=query.value("admin").toString().toStdString();
        respuesta["lista"].push_back(entradaUsuario);
    }
    return respuesta;

}
