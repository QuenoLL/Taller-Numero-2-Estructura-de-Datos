#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>
#include "SystemImpl.hpp"
#include "Interface.hpp"
 
using namespace std;
 
void lecturaArch(Interface* sistema){
    ifstream arch("../txts/Pacientes Marmaja.txt");   // si se ejecuta desde Logic/
    if(!arch.is_open()){
        arch.open("txts/Pacientes Marmaja.txt");      // si se ejecuta desde la raiz del proyecto
    }
    if(!arch.is_open()){
        cout << "ERROR. Archivo no se pudo abrir." << "\n";
        return;
    }
 
    string linea;
    while(getline(arch, linea)){ // lector linea por linea
        stringstream ss(linea);
        string token;
        vector<string> partes;
 
        while(getline(ss, token, ';')){
            partes.push_back(token);
        }
        sistema->crearPersonas(partes);
    }
    arch.close();
}

int leerEntero(string mensaje, int minimo, int maximo){
    int resp = 0;
    while(true){
        cout << mensaje;
        if(cin >> resp){
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if(resp >= minimo && resp <= maximo){
                return resp;
            }
        }else{
            if(cin.eof()) return maximo; // sin mas entrada: evita bucle infinito
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "ERROR, Ingrese respuesta válida" << "\n";
    }
}
 
int leerOpcion(int minimo, int maximo){
    return leerEntero("Seleccionar opción: ", minimo, maximo);
}

void menu(Interface* sistema){
    int resp = 0;
 
    while(resp != 6){
        cout << "\n=== HOSPITAL MARMAJA ===" << "\n";
        cout << "1. Atender pacientes" << "\n" << "2. Ver departamentos" << "\n" << "3. Buscar paciente" << "\n"
             << "4. Eliminar paciente" << "\n" << "5. Ver árbol de decisión" << "\n" << "6. Salir" << "\n";
 
        resp = leerOpcion(1, 6);
        switch(resp){
            case 1:
                sistema->atenderPaciente();
                break;
            case 2:{
                sistema->verDepartamentos();
                cout << "Ver recorridos de un departamento (0 = volver):" << "\n";
                sistema->listarDepartamentos();
                int depto = leerOpcion(0, sistema->cantidadDepartamentos());
                if(depto != 0){
                    cout << "1. Inorden\n2. Preorden\n3. Postorden\n4. Altura\n5. Factor de balance" << "\n";
                    int tipo = leerOpcion(1, 5);
                    sistema->verRecorrido(depto - 1, tipo);
                }
                break;
            }
            case 3:{
                cout << "=== BUSCAR PACIENTE ===" << "\n";
                cout << "Indique el ID o Nombre del paciente: ";
                string clave;
                getline(cin, clave);
                sistema->buscarPaciente(clave);
                break;
            }
            case 4:{
                int id = leerEntero("Indique el ID del paciente a eliminar: ", 1, 999999999);
                sistema->eliminarPaciente(id);
                break;
            }
            case 5:{
                cout << "1. Preorden\n2. Inorden\n3. Postorden" << "\n";
                int tipo = leerOpcion(1, 3);
                sistema->verArbolDecision(tipo);
                break;
            }
            case 6:
                cout << "Saliendo..." << "\n";
                break;
        }
    }
}

void ejecutar(Interface* sistema){
    sistema->crearDepartamentos();
    lecturaArch(sistema);
    menu(sistema);
}
 
int main(){
    Interface* sistema = new SystemImpl();
 
    ejecutar(sistema);
 
    delete sistema;
    return 0;
}