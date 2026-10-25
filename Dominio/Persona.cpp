#include <iostream>
#include "Persona.hpp"

using namespace std;

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
    this->servicio = "";
}

int Persona::getId(){ return this->id; }

string Persona::getIdFormateado(){
    string s = to_string(this->id);
    while(s.size() < 3){
        s = "0" + s;
    }
    return s;
}

string Persona::getName(){ return this->name; }
int Persona::getEdad(){ return this->edad; }
float Persona::getTempCorporal(){ return this->tempCorporal; }
float Persona::getPresionArterial(){ return this->presionArterial; }
int Persona::getDolor(){ return this->dolor; }
string Persona::getTipoDolor(){ return this->tipoDolor; }
int Persona::getTrauma(){ return this->trauma; }
int Persona::getSintomasNeu(){ return this->sintomasNeu; }
int Persona::getRequiereC(){ return this->requiereC; }
int Persona::getDiasHospital(){ return this->diasHospital; }
string Persona::getServicio(){ return this->servicio; }
void Persona::setServicio(string servicio){ this->servicio = servicio; }

Persona::~Persona(){
}