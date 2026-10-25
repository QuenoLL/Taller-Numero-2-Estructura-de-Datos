#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "../Dominio/Persona.hpp"

using namespace std;

class Interface{
    
    public:
        virtual void crearPersonas(vector<string> partes) = 0;
        virtual void crearDepartamentos() = 0;
        virtual void atenderPaciente() = 0;
        virtual void verDepartamento() = 0;
        virtual void listarDepartamentos() = 0;
        virtual int cantidadDepartamentos() = 0;
        virtual void verRecorrido(int indice, int tipo) = 0;
        virtual void buscarPaciente(string clave) = 0;
        virtual void eliminarPaciente(int id) = 0;
        virtual void verArbolDecision(int tipo) = 0;    

        virtual ~Interface(){};
};