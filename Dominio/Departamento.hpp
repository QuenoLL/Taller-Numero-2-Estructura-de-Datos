#pragma once
#include <string>
#include "../Estructuras/ArbolAvl.hpp"
#include "Persona.hpp"

using namespace std;

class Departamento{

    private:
        string name;
        ArbolAvl* arbol;

    public:
        Departamento(string name);
        string getName();
         ArbolAvl* getArbol();

        ~Departamento();
};