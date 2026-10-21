#include <iostream>
#include "Departamento.hpp"

Departamento::Departamento(string name){
    this->name = name;
    this->listaPacientes = new Lista<Persona>();
}

string Departamento:: getName(){
    return this -> name;
}

Lista<Persona>* Departamento::getListaPacientes() {
    return this->listaPacientes;
}


Departamento::~Departamento(){
    delete this->listaPacientes;
}