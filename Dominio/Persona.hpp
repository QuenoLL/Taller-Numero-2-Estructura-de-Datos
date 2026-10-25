#pragma once
#include <string>

using namespace std;

class Persona{

    private:

        int id;
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
        string servicio;

    public:
        Persona(int id, string name, int edad, float tempCorporal, float presionArterial, int dolor, string tipoDolor, int trauma,
        int sintomasNeu, int requiereC, int diasHospital);

        int getId();
        string getIdFormateado();
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
        string getServicio();
        void setServicio(string servicio);

        ~Persona();

};