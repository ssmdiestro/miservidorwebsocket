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
