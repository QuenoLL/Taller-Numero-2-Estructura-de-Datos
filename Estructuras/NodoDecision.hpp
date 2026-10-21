#pragma once
#include <string>

using namespace std;

class NodoDecision{
    private:
        string varibleCondicionar;
        int umbral;
        NodoDecision* derecha; //Si es no.
        NodoDecision* izquierda; //Si es si.
    public:
        NodoDecision(string variableCondicionar, int umbral){
            this->varibleCondicionar = variableCondicionar;
            this->umbral = umbral;
            this->derecha = nullptr;
            this->izquierda = nullptr;
        }

        



        ~NodoDecision();



};