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
void Registro::entrar(int userid)
{
    QSqlQuery query;
    query.prepare("INSERT into registro (usuarioid,entrada) VALUES (:userid,CURRENT_TIMESTAMP(0))");
    query.bindValue(":userid", userid);
    query.exec();

}
int Registro::estaDentro(int userid)
{
    int resultid =0;
    QSqlQuery query;
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
void Registro::salir(int id)
{
    QSqlQuery query;
    query.prepare("UPDATE registro SET salida= CURRENT_TIMESTAMP(0) where id =:id");
    query.bindValue(":id", id);
    query.exec();

}
JSON Registro::listar(JSON respuesta){
    QSqlQuery query;
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
