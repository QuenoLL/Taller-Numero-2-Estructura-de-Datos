#pragma once
#include "../Dominio/Persona.hpp"


class NodoAvl{
    public:
        Persona* dato;
        NodoAvl* izq;
        NodoAvl* der;
        int altura;

        NodoAvl(Persona p){
            this -> dato = p;
            this -> izq = izq;
            this -> der = der;
            this -> altura = 1;
        }
};