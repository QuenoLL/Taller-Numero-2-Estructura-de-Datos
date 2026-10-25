#pragma once 
#include "Nodo.hpp"
#include <string>

using namespace std;
template<typename T>

class Queue{
    private:
        Nodo<T>* primero;
        Nodo<T>* ultimo;
        int tamaño;

    public:
        Queue(){
            this -> primero = nullptr;
            this -> ultimo = nullptr;
            this -> tamaño = 0;
        }
        
        bool empty(){
            return this-> tamaño == 0;
        }

        void push(T valor){
            Nodo<T>* nuevo = new Nodo<T> (valor);
            if(this -> ultimo == nullptr){
                this -> primero = nuevo;
                this -> ultimo = nuevo;
            }else{
                this -> ultimo -> setSiguiente(nuevo);
                this -> ultimo = nuevo;
                }
            
            this -> tamaño++;
        }

        void pop(){
            if( this -> primero == nullptr){
                return;
            }
            Nodo<T>* eliminar = this -> primero;
            this -> primero = eliminar -> getSiguiente();
            if(this -> primero == nullptr){
                this -> ultimo = nullptr; 
            }
            delete eliminar;
            this -> tamaño--;
        }

        Nodo<T>* front(){
            return this-> primero;
        }
        void clear(){
            while(this -> primero != nullptr){
                Nodo<T>* siguiente = this -> primero -> getSiguiente();
                delete this -> primero;
                this -> primero = siguiente;
            }
            this -> ultimo = nullptr;
            this -> tamaño = 0;
        }

        int size(){
            return this -> tamaño;
        }

        ~Queue(){
            this -> clear();
        }
};