#include<iostream>
#include "Persona.hpp"

using namespace std;

/**
 * Retorna una instancia de la clase @Persona.hpp
 */
Persona::Persona(int id, string name, int edad, float tempCorporal, float presionArterial, int dolor, string tipoDolor, int trauma,
int sintomasNeu, int requiereC, int diasHospital){
    this->id = id;
    this->name = name;
    this->edad = edad;
    this->tempCorporal = tempCorporal;
    this->presionArterial = presionArterial;
    this->dolor = dolor;
    this->tipoDolor = tipoDolor;
    this->trauma = trauma;
    this->sintomasNeu = sintomasNeu;
    this->requiereC = requiereC;
    this->diasHospital = diasHospital;
    this -> servicio = "";
}

int Persona::getId(){
    return this->id;
}
string Persona::getIdFormateado(){
    string s = to_string(this -> id);
    while(s.size() <3){
        s = "0" + s;
    }
    return s;
}

int Persona::getEdad(){
    return this->edad;
}

string Persona::getName(){
    return this->name;
}

float Persona::getTempCorporal(){
    return this->tempCorporal;
}

float Persona::getPresionArterial(){
    return presionArterial;
}

int Persona::getDolor(){
    return dolor;
}

string Persona::getTipoDolor(){
    return tipoDolor;
}

int Persona::getTrauma(){
    return trauma;
}

int Persona::getSintomasNeu(){
    return sintomasNeu;
}

int Persona::getRequiereC(){
    return requiereC;
}

int Persona::getDiasHospital(){
    return diasHospital;
}


Persona::~Persona(){
}