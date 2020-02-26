#ifndef USUARIOS_H
#define USUARIOS_H
#include <QString>
#include "json.hpp"

using json= nlohmann::json;

class Usuarios
{
public:
    //Metodos
    Usuarios(int usuarioId,QString nombre,QString apellidos,int admin);
    void crearUsuario();
    static void eliminarUsuario(int id);
    static void modificarUsuario(int id,QString nombre,QString apellidos,int admin);
    static bool esAdmin(int id);
    static bool existe(int id);
    //json toJSON();
private:
    int m_usuarioId;
    QString m_nombre;
    QString m_apellidos;
    int m_admin;
};
#endif // USUARIOS_H
