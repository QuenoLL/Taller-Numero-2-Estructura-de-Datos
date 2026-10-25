#pragma once
#include "../Dominio/Persona.hpp"

class NodoAvl{
    public:
        Persona* dato;
        NodoAvl* izq;
        NodoAvl* der;
        int altura;

        NodoAvl(Persona* p){
            this -> dato = p;
            this -> izq = nullptr;
            this -> der = nullptr;
            this -> altura = 1;
        }
};