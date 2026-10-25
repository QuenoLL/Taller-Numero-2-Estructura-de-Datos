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
        NodoAvl* x = y->izq;
        y->izq = x->der;
        x->der = y;
        actualizarAltura(y);
        actualizarAltura(x);
        return x;
    }

    NodoAvl* rotacionIzquierda(NodoAvl* x){
        NodoAvl* y = x->der;
        x->der = y->izq;
        y->izq = x;
        actualizarAltura(x);
        actualizarAltura(y);
        return y;
    }

    NodoAvl* rotacionIzquierdaDerecha(NodoAvl* n){
        n->izq = rotacionIzquierda(n->izq);
        return rotacionDerecha(n);
    }

    NodoAvl* rotacionDerechaIzquierda(NodoAvl* n){
        n->der = rotacionDerecha(n->der);
        return rotacionIzquierda(n);

    }

    NodoAvl* balancear(NodoAvl* n){
        actualizarAltura(n);
        int fb = factorBalance(n);

        if(fb > 1){                                   
            if(factorBalance(n->izq) >= 0) return rotacionDerecha(n);        
            return rotacionIzquierdaDerecha(n);                              
        }
        if(fb < -1){                                  
            if(factorBalance(n->der) <= 0) return rotacionIzquierda(n);      
            return rotacionDerechaIzquierda(n);                                
        }
        return n;
    }

    //Metodos Genericos.
    NodoAvl* insertar(NodoAvl* n, Persona* p, bool& ok){
        if(n == nullptr){
            ok = true;
            return new NodoAvl(p);
        }
        if(p->getId() < n->dato->getId()){
            n->izq = insertar(n->izq, p, ok);
        }else if(p->getId() > n->dato->getId()){
            n->der = insertar(n->der, p, ok);
        }else{
            ok = false; 
            return n;
        }
        return balancear(n);
    }

    NodoAvl* minimo(NodoAvl* n){
        while(n->izq != nullptr) n = n->izq;
        return n;
    }

    NodoAvl* eliminar(NodoAvl* n, int id, bool& ok, bool borrarPersona){
        if(n == nullptr) return nullptr;
 
        if(id < n->dato->getId()){
            n->izq = eliminar(n->izq, id, ok, borrarPersona);
        }else if(id > n->dato->getId()){
            n->der = eliminar(n->der, id, ok, borrarPersona);
        }else{
            ok = true;
            if(n->izq == nullptr || n->der == nullptr){ // 0 o 1 hijo
                NodoAvl* hijo = (n->izq != nullptr) ? n->izq : n->der;
                if(borrarPersona) delete n->dato;
                delete n;
                return hijo;
            }

            NodoAvl* sucesor = minimo(n->der);
            Persona* original = n->dato;
            n->dato = sucesor->dato;
            bool aux = false;
            n->der = eliminar(n->der, sucesor->dato->getId(), aux, false);
            if(borrarPersona) delete original;
        }
            return balancear(n);
    }

    //luego metodos de recorrido y impresion
    void imprimirNodo(NodoAvl* n){
            cout << "[" << n->dato->getIdFormateado() << "] " << n->dato->getName() << "  ";
    }

    void inorden(NodoAvl* n){
        if(n == nullptr) return;
        inorden(n->izq); imprimirNodo(n); inorden(n->der);
    }

    void preorden(NodoAvl* n){
            if(n == nullptr) return;
            imprimirNodo(n); preorden(n->izq); preorden(n->der);
    }

     void postorden(NodoAvl* n){
            if(n == nullptr) return;
            postorden(n->izq); postorden(n->der); imprimirNodo(n);
    }

    void balanceInorden(NodoAvl* n){
        if(n == nullptr) return;
        balanceInorden(n->izq);
        cout << "  ID " << n->dato->getIdFormateado() << " | altura nodo: " << n->altura
                << " | factor de balance: " << factorBalance(n) << "\n";
        balanceInorden(n->der);
    }

    void recopilar(NodoAvl* n, string& salida){
        if(n == nullptr) return;
        recopilar(n->izq, salida);
        if(!salida.empty()) salida += ", ";
        salida += n->dato->getName() + " (" + n->dato->getIdFormateado() + ")";
        recopilar(n->der, salida);
    }


    //metodo busqueda
    Persona* buscarNombre(NodoAvl* n, const string& nombre, string& ruta){
        if(n == nullptr) return nullptr;
            if(!ruta.empty()) ruta += " -> ";
            ruta += n->dato->getIdFormateado();
            if(aMinus(n->dato->getName()) == nombre) return n->dato;
            Persona* r = buscarNombre(n->izq, nombre, ruta);
            if(r != nullptr) return r;
            return buscarNombre(n->der, nombre, ruta);
    }

    //Verificacion
    bool verificar(NodoAvl* n, int& h, long long min, long long max){
            if(n == nullptr){ h = 0; return true; }
            long long id = n->dato->getId();
            if(id <= min || id >= max) return false;         
            int hi = 0, hd = 0;
            if(!verificar(n->izq, hi, min, id)) return false;
            if(!verificar(n->der, hd, id, max)) return false;
            h = 1 + mayor(hi, hd);
            int fb = hi - hd;
            if(fb < -1 || fb > 1) return false;              
            return h == n->altura;                            
    }

    void destruir(NodoAvl* n){
        if(n == nullptr) return;
        destruir(n->izq);
        destruir(n->der);
        delete n->dato;
        delete n;
    }

    public:
        ArbolAvl(){
            this->raiz = nullptr;
            this->tamaño = 0;
        }
 
        ArbolAvl(const ArbolAvl&) = delete;
        ArbolAvl& operator=(const ArbolAvl&) = delete;
 
        bool insertar(Persona* p){
            bool ok = false;
            this->raiz = insertar(this->raiz, p, ok);
            if(ok) this->tamaño++;
            return ok;
        }
 
        bool eliminar(int id){
            bool ok = false;
            this->raiz = eliminar(this->raiz, id, ok, true);
            if(ok) this->tamaño--;
            return ok;
        }
 
        Persona* buscarPorId(int id, string& ruta){
            ruta = "";
            NodoAvl* cursor = this->raiz;
            while(cursor != nullptr){
                if(!ruta.empty()) ruta += " -> ";
                ruta += cursor->dato->getIdFormateado();
                int actual = cursor->dato->getId();
                if(id == actual) return cursor->dato;
                cursor = (id < actual) ? cursor->izq : cursor->der;
            }
            return nullptr;
        }

        Persona* buscarPorNombre(string nombre, string& ruta){
            ruta = "";
            return buscarNombre(this->raiz, aMinus(nombre), ruta);
        }

        void inorden(){
            inorden(this->raiz); cout << "\n"; 
        }
        void preorden(){
            preorden(this->raiz); cout << "\n"; 
        }
        void postorden(){
            postorden(this->raiz); cout << "\n";   
        }
        void mostrarBalance(){
            balanceInorden(this->raiz); 
        }

        int getAltura(){
            return altura(this->raiz); 
        }
        int size(){ 
            return this->tamaño; 
        }
        bool empty(){ 
            return this->tamaño == 0; 
        }

        string resumen(){
            string salida = "";
            recopilar(this->raiz, salida);
            return salida;
        }

        bool verificar(){
            int h = 0;
            return verificar(this->raiz, h, -1, 2147483648LL);
        }
        
        ~ArbolAvl(){
            destruir(this->raiz);
        }
    

};