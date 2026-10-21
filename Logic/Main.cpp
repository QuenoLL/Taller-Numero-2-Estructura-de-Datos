#include<iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "SystemImpl.hpp"
#include "Interface.hpp"

using namespace std;

void lecturaArch(Interface* sistema){
    ifstream arch("../txts/Pacientes Marmaja.txt");

    if(!arch.is_open()){
        cout << "ERROR. Archivo no se pudo abrir." << "\n";
        return;
    }

    string linea;

    while(getline(arch, linea)){//Leo el archivo a travez de un lector linea por linea, que es "linea";
        stringstream ss(linea);
        string token;
        vector<string> partes;

        while(getline(ss,token,';')){
            partes.push_back(token);
        }

        sistema->crearPersonas(partes);
    }

    
};

int leerOpcion( int minimo, int maximo){
    int resp = minimo -1;
    do{
        try{
            cout << "Seleccionar opción: ";
            cin >> resp;
            if(resp < minimo || resp > maximo){
                cout << "ERROR, Ingrese respuesta válida" << "\n";
            }
        }catch(...){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "ERROR, Ingrese respuesta válida" << "\n";
            resp = minimo -1;
        }

    } while ( resp < minimo || resp > maximo);
    return resp;
    }



void menu(Interface* sistema){
    int resp = 0;
    cin.exceptions(ios::failbit);

    while(resp != 4){
        cout << "=== HOSPITAL MARMAJA ===" << "\n";
        cout << "1. Atender Pacientes" << "\n" << "2. Ver Departamento" << "\n" << "3. Revisar Hisotrial de Atencion" << "\n" << "4. Salir" << "\n";
        
        resp = leerOpcion(1,4);
        switch(resp){
            case 1:
            sistema -> atenderPaciente();
            break;
            case 2:{
                sistema -> listarDepartamentos();
                int depto = leerOpcion(1, sistema -> cantidadDepartamentos());
                sistema  -> verDepartamento( depto-1);
                break;
            }
            case 3: 
            sistema -> verHistorial();
            break;
            case 4: 
            cout << "Saliendo..." << "\n";
            break;
        }
    }
}


void ejecutar(Interface*  sistema){
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