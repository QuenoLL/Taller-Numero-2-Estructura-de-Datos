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

        static string negar(string operador){
            if(operador == "<")  return ">=";
            if(operador == "<=") return ">";
            if(operador == ">")  return "<=";
            if(operador == ">=") return "<";
            if(operador == "==") return "!=";
            if(operador == "!=") return "==";
            return operador;
        }        
    
    public:
        /**
         * Retorna una instancia de Nodo pregunta.
         */
        NodoDecision(string atributo, string operador, string valor){
            this->atributo = atributo;
            this->operador = operador;
            this->valor = valor;
            this -> servicio = "";
            this->esHoja = false;
            this->no = nullptr;
            this->si = nullptr;
        }

        /**
         * Retorna una instancia para un Nodo hoja del Decision Tree.
         */
        NodoDecision(string servicio){
            this -> atributo = "";
            this -> operador = "";
            this -> valor = "";
            this->servicio = servicio;  
            this->esHoja = true;
            this->no = nullptr;
            this->si = nullptr;
        }

        bool getEsHoja(){
            return esHoja;
        }
        string getAtributo(){
            return atributo;
        }
        string getOperador(){
            return operador;
        }
        string getValor(){
            return valor;
        }
        string getServicio(){
            return servicio;
        }

        NodoDecision* getSi(){
            return si;
        }

        NodoDecision* getNo(){
            return no;
        }

        void setSi(NodoDecision* p){
            this->si = p;
        }

        void setNo(NodoDecision* p){
            this->no = p;
        }

        string describir(){
            if(esHoja) return "Servicio: " + servicio;
            return atributo + " " + operador + " " + valor;
        }
        
        string describirNegada(){
            return atributo + " " + negar(operador) + " " + valor;
        }

        ~NodoDecision(){
            delete si;
            delete no;
        }

};