#pragma once
#include "Interface.hpp"
#include "../Estructuras/Lista.hpp"
#include "../Estructuras/Queue.hpp"
#include "../Dominio/Departamento.hpp"
#include "../Estructuras/ArbolDecision.hpp"

class SystemImpl: public Interface{

    private:
        Lista<Departamento*>* listaDepartamentos;
        Queue<Persona> colaPacientes; 
        ArbolDecision arbolDecision;

        Departamento* buscarDepartamento(string nombre);
        bool estaDuplicada(int id);
        void procesarSiguiente();

    public:
        SystemImpl();
        
        void crearPersonas(vector<string> partes);
        void crearDepartamentos();
        void atenderPaciente();
        void verDepartamento();
        void listarDepartamentos();
        int cantidadDepartamentos();
        void verRecorrido(int indice, int tipo);
        void buscarPaciente(string clave);
        void eliminarPaciente(int id);
        void verArbolDecision(int tipo);


        ~SystemImpl();

};