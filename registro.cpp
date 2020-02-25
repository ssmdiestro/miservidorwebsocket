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
void Registro::salir(int userid)
{
    QSqlQuery query;
    query.prepare("UPDATE registro SET salida= CURRENT_TIMESTAMP(0) where id in (SELECT id from registro where usuarioid=:userid and salida is null order by entrada desc limit 1)");
    query.bindValue(":userid", userid);
    query.exec();

}
