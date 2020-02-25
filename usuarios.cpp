#include "usuarios.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>
#include <string>
#include <QVariant>
#include <QString>


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

void Usuarios::eliminarUsuario()
{

}

