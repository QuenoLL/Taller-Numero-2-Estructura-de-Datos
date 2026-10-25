#pragma once
#include <iostream>
#include "../Dominio/Persona.hpp"
#include "NodoAvl.hpp"
#include "NodoDecision.hpp"

using namespace std;

class ArbolDecision{
    private:
        NodoDecision* root;

        static bool comparar(double actual, string operador, double ref){
            if(operador == "<") return actual < ref;
            if(operador == "<=") return actual <= ref;
            if(operador == ">") return actual > ref;
            if(operador == ">=") return actual >= ref;
            if(operador == "==") return actual == ref;
            if (operador == "!=") return actual != ref;
            throw invalid_argument("Operador desconocido: " + operador);
        }

        /** Evalúa la condición de un nodo pregunta */
        bool cumple(NodoDecision* n, Persona& p){
            string atributo = n -> getAtributo();
            string operador = n-> getOperador();

            if(atributo == "TipoDolor"){
                if(operador == "==") return p.getTipoDolor() == n-> getValor();
                if(operador == "!=") return p.getTipoDolor() != n -> getValor();
                throw invalid_argument("Operador inválido para TipoDolor");
            }

            double actual = 0;
            if(atributo == "Edad") actual = p.getEdad();
            else if(atributo == "Temperatura") actual = p.getTempCorporal();
            else if(atributo == "PresionArterial") actual = p.getPresionArterial();
            else if(atributo == "Dolor") actual = p.getDolor();
            else if(atributo == "SintomasNeu") actual = p.getSintomasNeu();
            else if(atributo == "RequiereCirugia") actual = p.getRequiereC();
            else if(atributo == "DiasHospital") actual = p.getDiasHospital();
            else throw invalid_argument("Atributo desconocido: " + atributo);

            return comparar(actual, operador, stod(n->getValor()));
        }

        void preorden(NodoDecision* n, int profundidad){
            if(n == nullptr) return;
            for(int i = 0; i < profundidad; i++) cout <<"   ";
            cout <<n -> describir() << "\n";
            preorden(n->getSi(), profundidad + 1);
            preorden(n -> getNo(), profundidad + 1);
        }

        void inorden(NodoDecision* n, int profundidad){
            if(n == nullptr) return;
            inorden(n -> getSi(), profundidad+1);
            for(int i = 0; i < profundidad; i++) cout << "   ";
            cout << n -> describir() << "\n";
            inorden(n -> getNo(), profundidad +1); 
        }

        void postorden(NodoDecision* n, int profundidad){
            if(n == nullptr) return;
            postorden( n -> getSi(), profundidad + 1);
            postorden(n -> getNo(), profundidad + 1);
            for(int i = 0; i < profundidad; i++) cout << "   ";
            cout << n -> describir() << "\n";
        }

        public:
            ArbolDecision(const ArbolDecision&)=delete;
            ArbolDecision& operator = (const ArbolDecision&) = delete;


        public:
            /**
            * Retorna un arbol de decision con sus respectivos caminos, Nodos pregunta y Nodos hoja.
            */
            ArbolDecision(){
                // 1 Edad < 14? Si, pediatra
                root = new NodoDecision("Edad", "<", "14");
                root->setSi(new NodoDecision("Pediatra"));

                // 2 Trauma == 1 -> RequiereCirugia= Cirugia : Traumatología)
                NodoDecision* trauma = new NodoDecision("Trauma", "==", "1");
                root -> setNo(trauma);

                NodoDecision* cirugiaTrauma = new NodoDecision("RequiereCirugia", "==", "1");
                cirugiaTrauma -> setSi(new NodoDecision("Cirugia"));
                cirugiaTrauma -> setNo(new NodoDecision("traumatologia"));
                trauma -> setSi(cirugiaTrauma);
        
                // 3 SuntomasNeu == 1 -> Neurología

                NodoDecision* neuro = new NodoDecision("SintomasNeu", "==", "1");
                neuro -> setSi(new NodoDecision("Neurologia"));
                trauma -> setNo(neuro);

                //4 TipoDolor == pecho -> cardiologia 
                NodoDecision* pecho = new NodoDecision("TipoDOlor", "==", "pecho");
                pecho -> setSi(new NodoDecision("Cardiologia"));
                neuro -> setNo(pecho);

                //5 urgencias: temperatuar >38,5 o Dolor >= 8 o presionarterial >= 180
                NodoDecision* fiebre = new NodoDecision("Temperatura", ">", "38,5");
                fiebre -> setSi(new NodoDecision("Urgencias"));
                pecho -> setNo(fiebre);

                NodoDecision* dolor = new NodoDecision("Dolor", ">=", "8");
                dolor -> setSi(new NodoDecision("Urgencias"));
                fiebre -> setNo(dolor);

                NodoDecision* presion = new NodoDecision("PresionArterial", ">=", "180");
                presion -> setSi( new NodoDecision("Urgencias"));
                dolor -> setNo(presion);

                //6 Cirugia programada sin trauma: RequiereCirugia ==1 -> Cirugia
                NodoDecision* cirugiaPro = new NodoDecision("RequiereCirugia", "==", "1");
                cirugiaPro -> setSi(new NodoDecision("Cirugia"));
                presion -> setNo(cirugiaPro);

                //7 DiasHospital >= 2 -> Hospitalizacion, si no medicina general
                NodoDecision* hosp = new NodoDecision ("DiasHospital", ">=", "2");
                hosp -> setSi(new NodoDecision("Hospitalizacion"));
                hosp -> setNo(new NodoDecision("Medicina General"));
                cirugiaPro -> setNo(hosp);

                string clasificar(Persona& p, string& ruta){
                    ruta = "";
                    NodoDecision* cursor = root;
                    while(!cursor -> getEsHoja()){
                        bool resultado = cumple(cursor, p);
                        if(!ruta.empty()) ruta += " -> ";
                        ruta += resultado ? cursor->describir( ): cursor-> describirNegada();
                        cursor = resuñtado ? cursor -> getSi() : cursor->getNo();
                    }
                    return cursor -> getServicio();
                }

                void preorden(){ preorden(root,0);}
                void inorden(){ inorden(root, 0);}
                void postorden(){ postorden(root,0);}




            }
};  