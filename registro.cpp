#include "registro.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>
#include <string>
#include <QVariant>
#include <QString>
Registro::Registro()
{
}
//Metodo para registrar la entrada de un Usuario
void Registro::entrar(int userid,QSqlDatabase db)
{
    QSqlQuery query(db);
    query.prepare("INSERT into registro (usuarioid,entrada) VALUES (:userid,CURRENT_TIMESTAMP(0))");
    query.bindValue(":userid", userid);
    query.exec();


}
//Metodo que comprueba si un Usuario está dentro mediante la comprobacion del campo Salida
//Si es el campo está vacio significa que ese Usuario aun no ha salido
int Registro::estaDentro(int userid,QSqlDatabase db)
{
    int resultid =0;
    QSqlQuery query(db);
    query.prepare("SELECT id from registro where usuarioid = :numid and salida is null order by entrada desc limit 1");
    query.bindValue(":numid", userid);
    if (query.exec()){
        if (query.size()>0)
        {
            query.next();
            resultid = query.value("id").toInt();
        }
    }
    return resultid;

}
//Metodo que agrega la fecha y horas actuales al campo Salida de un registro de la Base de datos
void Registro::salir(int id,QSqlDatabase db)
{
    QSqlQuery query(db);
    query.prepare("UPDATE registro SET salida= CURRENT_TIMESTAMP(0) where id =:id");
    query.bindValue(":id", id);
    query.exec();

}
//Devuelve una lista de todos los registros
JSON Registro::listar(JSON respuesta,QSqlDatabase db){
    QSqlQuery query(db);
    query.prepare("SELECT id,usuarioid,nombre,apellidos,entrada,salida FROM public.registro, public.usuarios where usuarioid=numid order by id desc");
    query.exec();
    respuesta["resultados"]=query.size();
    while(query.next())
    {
        JSON entradaRegistro;
        entradaRegistro["id"]=query.value("id").toString().toStdString();
        entradaRegistro["usuarioid"]=query.value("usuarioid").toString().toStdString();
        entradaRegistro["nombre"]=query.value("nombre").toString().toStdString();
        entradaRegistro["apellidos"]=query.value("apellidos").toString().toStdString();
        entradaRegistro["entrada"]=query.value("entrada").toString().toStdString();
        entradaRegistro["salida"]=query.value("salida").toString().toStdString();
        respuesta["lista"].push_back(entradaRegistro);
    }
    return respuesta;

}
//Devuelve una lista de registros de un Usuario concreto mediante su ID
JSON Registro::listar(JSON respuesta, int userid,QSqlDatabase db){
    QSqlQuery query(db);
    query.prepare("SELECT id,entrada,salida FROM public.registro, public.usuarios where usuarioid=numid and numid=:numid order by id desc");
    query.bindValue(":numid", userid);
    query.exec();
    respuesta["resultados"]=query.size();
    while(query.next())
    {
        JSON entradaRegistro;
        entradaRegistro["id"]=query.value("id").toString().toStdString();
        entradaRegistro["entrada"]=query.value("entrada").toString().toStdString();
        entradaRegistro["salida"]=query.value("salida").toString().toStdString();
        respuesta["lista"].push_back(entradaRegistro);
    }
    return respuesta;

}
//Devuelve una lista de todos los usuarios que están dentro
JSON Registro::listardentro(JSON respuesta,QSqlDatabase db){
    QSqlQuery query(db);
    query.prepare("SELECT distinct(usuarioid),nombre,apellidos,entrada from registro, usuarios where usuarioid = numid and salida is null order by entrada desc");
    query.exec();
    respuesta["resultados"]=query.size();
    while(query.next())
    {
        JSON entradaRegistro;
        entradaRegistro["usuarioid"]=query.value("usuarioid").toString().toStdString();
        entradaRegistro["nombre"]=query.value("nombre").toString().toStdString();
        entradaRegistro["apellidos"]=query.value("apellidos").toString().toStdString();
        entradaRegistro["entrada"]=query.value("entrada").toString().toStdString();
        respuesta["lista"].push_back(entradaRegistro);
    }
    return respuesta;

}
