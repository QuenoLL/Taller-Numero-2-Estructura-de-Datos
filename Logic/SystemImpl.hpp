#pragma once
#include "Interface.hpp"
#include "../Estructuras/Lista.hpp"
#include "../Estructuras/Queue.hpp"
#include "../Dominio/Departamento.hpp"

class SystemImpl: public Interface{

    private:
        Lista<Departamento*>* listaDepartamentos;
        Queue<Persona> colaPacientes; 

        Departamento* buscarDepartamento(string nombre);
        bool estaDuplicada(Persona& nueva);

    public:
        SystemImpl();
        
        void crearPersonas(vector<string> partes);
        void crearDepartamentos();
        void asignarPacientes(Persona*);
        void atenderPaciente();
        void listarDepartamentos();
        int cantidadDepartamentos();
        void verDepartamento(int);
        void verHistorial();

        Lista<Departamento*>* getLista();

        ~SystemImpl();

};