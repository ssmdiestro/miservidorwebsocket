#ifndef REGISTRO_H
#define REGISTRO_H
#include <QString>
#include "json.hpp"

using JSON= nlohmann::json;

class Registro
{
public:
    Registro();
    static void entrar(int userid);
    static void salir(int id);
    static int estaDentro(int userid);
    static JSON listar(JSON respuesta);
};

#endif // REGISTRO_H
