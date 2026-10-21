#pragma once
#include <string>

using namespace std;

class Persona{

    private:
        int posAtencion;
        string name;
        int edad;
        float tempCorporal;
        float presionArterial;
        int dolor;
        string tipoDolor;
        int trauma;
        int sintomasNeu;
        int requiereC;
        int diasHospital;

    public:
        Persona(int posAtencion, string name, int edad, float tempCorporal, float presionArterial, int dolor, string tipoDolor, int trauma,
int sintomasNeu, int requiereC, int diasHospital);
        int getAtencion();
        string getName();
        int getEdad();
        float getTempCorporal();
        float getPresionArterial();
        int getDolor();
        string getTipoDolor();
        int getTrauma();
        int getSintomasNeu();
        int getRequiereC();
        int getDiasHospital();


        ~Persona();

};