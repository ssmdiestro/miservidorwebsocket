#ifndef REGISTRO_H
#define REGISTRO_H
#include <QString>
#include "json.hpp"

class Registro
{
public:
    Registro();
    static void entrar(int userid);
    static void salir(int id);
    static int estaDentro(int userid);
};

#endif // REGISTRO_H
