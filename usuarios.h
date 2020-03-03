#ifndef USUARIOS_H
#define USUARIOS_H
#include <QString>
#include "json.hpp"
#include <QSqlDatabase>

using JSON= nlohmann::json;
/**
 * @brief Clase Usuarios
 *
 * Es la clase encargada de interactuar entre el servidor y la tabla Usuarios de la Base de Datos
 */
class Usuarios
{
public:
    /**
     * @brief Usuarios
     *
     * Constructor
     * @param usuarioId
     * @param nombre
     * @param apellidos
     * @param admin 0=False  1=True
     */
    Usuarios(int usuarioId,QString nombre,QString apellidos,int admin);
    /**
     * @brief crearUsuario
     *
     * Metodo para añadir un nuevo Usuario en la base de datos
     * @param db
     */
    void crearUsuario(QSqlDatabase db);
    /**
     * @brief eliminarUsuario
     *
     * Metodo para eliminar un Usuario de la base de datos
     * @param id
     * @param db
     */
    static void eliminarUsuario(int id,QSqlDatabase db);
    /**
     * @brief modificarUsuario
     *
     * Metodo para modificar un Usuario de la base de datos
     * @param id
     * @param nombre
     * @param apellidos
     * @param admin 0=False  1=True
     * @param db
     */
    static void modificarUsuario(int id,QString nombre,QString apellidos,int admin,QSqlDatabase db);
    /**
     * @brief esAdmin
     *
     * Metodo que devuelve True o False dependiendo si el usuario indicado tiene o no permisos de Administrador
     * @param id
     * @param db
     * @return
     */
    static bool esAdmin(int id,QSqlDatabase db);
    /**
     * @brief existe
     *
     * Metodo que comprueba si un Id de usuario ya existe en la base de datos
     * @param id
     * @param db
     * @return
     */
    static bool existe(int id, QSqlDatabase db);
    /**
     * @brief listar
     *
     * Devuelve una lista de todos los usuarios
     * @param respuesta
     * @param db
     * @return
     */
    static JSON listar(JSON respuesta,QSqlDatabase db);
    /**
      * @brief cargar
      *
      * Carga en un JSON los datos de un usuario en concreto
      * @param id
      * @param db
      * @return
      */
     static JSON cargar(int id,QSqlDatabase db);

private:
    int m_usuarioId;
    QString m_nombre;
    QString m_apellidos;
    int m_admin;
};
#endif // USUARIOS_H
