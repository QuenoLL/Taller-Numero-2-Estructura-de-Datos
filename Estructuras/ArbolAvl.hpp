#pragma once
#include <iostream>
#include <string>
#include "../Dominio/Persona.hpp"
#include "NodoAvl.hpp"
using namespace std;

class ArbolAvl{
    private:
    NodoAvl* raiz;
    int tamaño;

    static string aMinus(string s){
        for(size_t i = 0; i < s.size(); i++) s[i]= tolower((unsigned char) s[i]);
        return s;
    }

    static int mayor(int a, int b){
        return a > b ? a:b;
    }

    int altura(NodoAvl* n){
        return n == nullptr ? 0 : n -> altura;
    }
    void actualizarAltura (NodoAvl* n) {
        n -> altura = 1 + mayor(altura(n -> izq), altura(n -> der));
    }
    int factorBalance(NodoAvl* n){
        return n == nullptr ? 0 : altura(n -> izq) - altura(n -> der);
    }

    //Aqui empiezan las rotaciones

    NodoAvl* rotacionDerecha(NodoAvl* y){
    }

    NodoAvl* rotacionIzquierda(NodoAvl* x){

    }

    NodoAvl* rotacionIzquierdaDerecha(NodoAvl* n){
    }

    NodoAvl* rotacionDerechaIzquierda(NodoAvl* n){

    }

    NodoAvl* balancear(NodoAvl* n){

    }

    //Mas metodos

    NodoAvl* insertar(NodoAvl* n, Persona* p, bool& ok){

    }

    NodoAvl* eliminar(NodoAvl* n, int id, bool& ok, bool borrarPersona){

    }

    //luego metodos de recorrido y impresion



    //metodo busqueda
    Persona* buscarNombre(NodoAvl* n, const string& nombre, string& ruta){
        
    }

};