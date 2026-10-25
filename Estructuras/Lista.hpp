#pragma once
#include <iostream>
#include <string>
#include "NodoAvl.hpp"

template <class T>
class Lista{

    private:
        Nodo<T>* head;
        int tamaño;
    public:
        Lista(){
            this -> head = nullptr;
            this -> tamaño = 0;
        }

        void agregar(T valor){
            Nodo<T>* nuevo = new Nodo<T>(valor); 

            if (this -> head == nullptr){
                this -> head = nuevo;
            }else{
                Nodo<T>* cursor = this -> head;
                while(cursor -> getSiguiente() != nullptr){
                    cursor = cursor -> getSiguiente();
                }
                cursor -> setSiguiente(nuevo);
            }
            this -> tamaño++;
        }

        T obtener(int indice){
            if(indice < 0 || indice >= this -> tamaño){
                throw std::out_of_range("Lista: indice fuera de rango");
            }
            Nodo<T>* cursor = this -> head;
            for(int i = 0; i < indice; i++){
                cursor = cursor -> getSiguiente();
            }
            return cursor -> getValor();
        }
        int size(){
            return this -> tamaño;
        }

        bool empty(){
            return this -> tamaño ==0;
        }

        ~Lista(){
            Nodo<T>* cursor = this -> head;
            while(cursor != nullptr){
                Nodo<T>* siguiente = cursor -> getSiguiente();
                delete cursor;
                cursor = siguiente;
            }

        }
        

};