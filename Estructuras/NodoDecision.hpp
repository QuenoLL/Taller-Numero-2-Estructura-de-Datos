#pragma once
#include <string>

using namespace std;

class NodoDecision{
    private:
        string atributo;
        string operador;
        string valor;
        string servicio;
        bool esHoja; //Identificador si es respuesta final o pregunta
        NodoDecision* no; //Si es no.
        NodoDecision* si; //Si es si.
    public:
        /**
         * Retorna una instancia de Nodo pregunta.
         */
        NodoDecision(string atributo, string operador, string valor){
            this->atributo = atributo;
            this->operador = operador;
            this->valor = valor;
            this->esHoja = false;
            this->no = nullptr;
            this->si = nullptr;
        }

        /**
         * Retorna una instancia para un Nodo hoja del Decision Tree.
         */
        NodoDecision(string servicio){
            this->servicio = servicio;
            this->esHoja = true;
            this->no = nullptr;
            this->si = nullptr;
        }

        bool getEsHoja(){
            return esHoja;
        }

        NodoDecision* getIzquierda(){
            return si;
        }

        NodoDecision* getDerecha(){
            return no;
        }

        void setSi(NodoDecision* p){
            this->si = p;
        }

        void setNo(NodoDecision* p){
            this->no = p;
        }


        ~NodoDecision();

};