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
//Devuelve los datos de un usuario en concreto mediante su ID
JSON Usuarios::cargar(int id,QSqlDatabase db){
    QSqlQuery query(db);
    query.prepare("select * from usuarios where numid=:numid");
    query.bindValue(":numid", id);
    query.exec();
    query.next();
        JSON entradaUsuario;
        entradaUsuario["numid"]=query.value("numid").toString().toStdString();
        entradaUsuario["nombre"]=query.value("nombre").toString().toStdString();
        entradaUsuario["apellidos"]=query.value("apellidos").toString().toStdString();
        entradaUsuario["admin"]=query.value("admin").toString().toStdString();
        return entradaUsuario;
}
//Metodo para añadir un nuevo Usuario en la base de datos
void Usuarios::crearUsuario(QSqlDatabase db)
{
    QSqlQuery query(db);
    query.prepare("INSERT into usuarios (numid,nombre,apellidos,admin) VALUES (:numid,:nombre,:apellidos,:admin)");
    query.bindValue(":numid", m_usuarioId);
    query.bindValue(":nombre", m_nombre);
    query.bindValue(":apellidos", m_apellidos);
    query.bindValue(":admin", m_admin);
    query.exec();

}
//Metodo para eliminar un Usuario de la base de datos
void Usuarios::eliminarUsuario(int id,QSqlDatabase db)
{
    QSqlQuery query(db);
    query.prepare("DELETE from usuarios where numid=:numid");
    query.bindValue(":numid", id);
    query.exec();
}
//Metodo para modificar un Usuario
void Usuarios::modificarUsuario(int id,QString nombre,QString apellidos,int admin,QSqlDatabase db)
{
    QSqlQuery query(db);
    query.prepare("UPDATE usuarios SET nombre = :nombre,apellidos = :apellidos,admin = :admin WHERE numid=:numid");
    query.bindValue(":numid", id);
    query.bindValue(":nombre", nombre);
    query.bindValue(":apellidos", apellidos);
    query.bindValue(":admin", admin);
    query.exec();

}
//Metodo que comprueba si la ID corresponde a algun Usuario de la base de datos
bool Usuarios::existe(int id, QSqlDatabase db)
{
    bool result =false;
    QSqlQuery query(db);
    query.prepare("SELECT numid from usuarios where numid = :numid");
    query.bindValue(":numid", id);

    if (query.exec()){
        if (query.size()>0) result =true;
    }
        qDebug() << query.lastError().text();
    return result;

}
//Metodo que comprueba si el Usuario especificado tiene permisos de administracion
bool Usuarios::esAdmin(int id,QSqlDatabase db)
{
    QSqlQuery query(db);
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
//Devuelve una lista de todos los Usuarios
JSON Usuarios::listar(JSON respuesta,QSqlDatabase db){
    QSqlQuery query(db);
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
