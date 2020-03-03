#ifndef REGISTRO_H
#define REGISTRO_H
#include "json.hpp"
#include <QSqlDatabase>

using JSON= nlohmann::json;
/**
 * @brief Clase Registro
 *
 * Es la clase encargada de interactuar entre el servidor y la tabla Registros de la Base de Datos
 */
class Registro
{
public:
    Registro();

    /**
     * @brief entrar
     *
     * Metodo para registrar la entrada de un Usuario
     * @param userid
     * @param db
     */
    static void entrar(int userid,QSqlDatabase db);
    /**
     * @brief salir
     *
     * Metodo que agrega la fecha y horas actuales al campo Salida de un registro de la Base de datos
     * @param id
     * @param db
     */
    static void salir(int id,QSqlDatabase db);
    /**
     * @brief estaDentro
     *
     * Metodo que comprueba si un Usuario está dentro mediante la comprobacion del campo Salida. Si es el campo está vacio significa que ese Usuario aun no ha salido
     * @param userid
     * @param db
     * @return
     */
    static int estaDentro(int userid,QSqlDatabase db);
    /**
     * @brief listar
     *
     * Devuelve una lista de todos los registros
     * @param respuesta
     * @param db
     * @return
     */
    static JSON listar(JSON respuesta,QSqlDatabase db);
    /**
     * @brief listar
     *
     * Devuelve una lista de todos los registros de un usuario concreto
     * @param respuesta
     * @param userid
     * @param db
     * @return
     */
    static JSON listar(JSON respuesta,int userid,QSqlDatabase db);
    /**
     * @brief listardentro
     *
     * Devuelve una lista de todos los usuarios que están dentro
     * @param respuesta
     * @param db
     * @return
     */
    static JSON listardentro(JSON respuesta,QSqlDatabase db);
};

#endif // REGISTRO_H
