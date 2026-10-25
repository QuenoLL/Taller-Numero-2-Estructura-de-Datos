#include <iostream>
#include "Departamento.hpp"

Departamento::Departamento(string name){
    this->name = name;
    this->arbol = new ArbolAvl();
}

string Departamento:: getName(){
    return this -> name;
}

ArbolAvl* Departamento::getArbol() {
    return this->arbol;
}


Departamento::~Departamento(){
    delete this->arbol;
}