#pragma once 
#include "Nodo.hpp"
#include <string>

using namespace std;
template<typename T>

class Queue{
    private:
        Nodo<T>* primero;
        int tamaño;

    public:
        Queue(){
            this -> primero = nullptr;
            this -> tamaño = 0;
        }
        
        bool empty(){
            return this-> tamaño == 0;
        }

        void push(T valor){
            Nodo<T>* nuevo = new Nodo<T> (valor);
            if(this -> primero == nullptr){
                this -> primero = nuevo;
            }else{
                Nodo<T>* puntero = this -> primero;
                while(puntero -> getSiguiente() != nullptr){
                    puntero = puntero -> getSiguiente();
                }
                puntero -> setSiguiente(nuevo);
            }
            this -> tamaño++;
        }

        void pop(){
            if( this -> primero == nullptr){
                return;
            }
            Nodo<T>* eliminar = this -> primero;
            this -> primero = eliminar -> getSiguiente();
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
            this -> tamaño = 0;
        }

        int size(){
            return this -> tamaño;
        }

        ~Queue(){
            this -> clear();
        }
};