#pragma once
#include "../Dominio/Persona.hpp"
#include "Nodo.hpp"
#include "NodoDecision.hpp"

class ArbolDecision{
    private:
        NodoDecision* root;
    public:

        /**
         * Retorna un arbol de decision con sus respectivos caminos, Nodos pregunta y Nodos hoja.
         */
        ArbolDecision(){
            //Edad <= 14? Si, pediatra
            root = new NodoDecision("Edad", "<=", "14");
            root->setSi(new NodoDecision("Pediatra"));

            //Edad <= 14? No, Trauma == 1?
            NodoDecision* trauma = new NodoDecision("Trauma", "==", "1");
            root->setNo(trauma);

            //Trauma == 1=? Si,  Cirugia == 1?
            NodoDecision* cirugua = new NodoDecision("Cirugua","==", "1");
            trauma->setSi(cirugua);

            //Cirugia == 1? Cirugua.

            




        }

        void asignarPersona(NodoDecision* head){
            if(head == nullptr) return;

            NodoDecision* cursor = head;

            if(cursor->getEsHoja()){

            }

        }
};  