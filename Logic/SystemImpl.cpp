#include <iostream>
#include <vector>
#include <string>
#include "SystemImpl.hpp"
#include "../Dominio/Persona.hpp"

static void mostrarPersona(Persona& p){
    cout << " [" << p.getAtencion() << "] " <<p.getName() << " | Edad: " << p.getEdad() 
    << " | Departamento: " <<p.getDepartamento() << "\n";
}

SystemImpl::SystemImpl(){
    this->listaDepartamentos = new Lista<Departamento*>();
}

void SystemImpl::crearPersonas(vector<string> partes){

    if(partes.empty()){
        return;
    }
    if(partes.size() < 4){
        cout << "Linea invalida, se omite. " << "\n";
        return;
    }
    string departamento = partes[3];
    if (!departamento.empty() && departamento.back() == '\r'){
        departamento.pop_back();
    }
    try{
        int posAtencion = stoi(partes[0]);
        string nombre = partes[1];
        int edad = stoi(partes[2]);
        Persona p (posAtencion, nombre, edad, departamento);
        this -> colaPacientes.push(p);
    }catch(...){
        cout << "Linea con datos inválidos, se omite." << "\n";
    }
}

void SystemImpl::crearDepartamentos(){
    vector<string> deptos = {"Urgencias", "Medicina General", "Cardiologia", "Neurologia", "Traumatologia", "Cirugia", "Pediatria", "Hospitalizacion"};

    for(string nombre : deptos){
        Departamento* dep = new Departamento(nombre);
        this->listaDepartamentos->agregar(dep);
    }
    
}

void SystemImpl::asignarPacientes(Persona* persona){
    for (int i = 0; i < this -> listaDepartamentos -> size(); i++){
        Departamento* dep = this -> listaDepartamentos -> obtener (i);
        if ( dep -> getName() == persona -> getDepartamento()){
            dep -> getListaPacientes() -> agregar(*persona);
            return;
        }
    }
    cout << "Departamento  " << persona -> getDepartamento() << " no existe. El paciente no será derivado." << "\n";
}

void SystemImpl::atenderPaciente(){
    if (this -> colaPacientes.empty()){
        cout << "No hay pacientes en espera." << "\n";
        return;
    }
    Persona p = this -> colaPacientes.front() -> getValor();
    this -> colaPacientes.pop();
    this -> asignarPacientes(&p);
    this -> historial.push(p); 
    cout << " Paciente atendido y derivado: " << "\n";
    mostrarPersona(p);
    cout << " Pacientes en espera: " << this -> colaPacientes.size() << "\n";
}

void SystemImpl::listarDepartamentos(){
    for (int i = 0; i < this -> listaDepartamentos -> size(); i++){
        cout << ( i + 1) << ".-" << this -> listaDepartamentos -> obtener(i) -> getName() << "\n";
    }
}

int SystemImpl::cantidadDepartamentos(){
    return this -> listaDepartamentos -> size();
}

void SystemImpl::verDepartamento(int indice){
    if(indice < 0 || indice >= this -> listaDepartamentos -> size()){
        cout << "Departamento inválido" << "\n";
        return;
    }

    Departamento* dep = this -> listaDepartamentos -> obtener(indice);
    Lista <Persona>* pacientes = dep -> getListaPacientes();
    
    cout <<"--- " << dep-> getName() <<" (" << pacientes -> size() << " pacientes) ---" << "\n";
    if(pacientes -> empty()){
        cout << " Sin pacientes. " << "\n";
        return;
    }
    for (int i = 0; i< pacientes -> size(); i++){
        Persona p = pacientes -> obtener(i);
        mostrarPersona(p);
    }
}

void SystemImpl::verHistorial(){
    if(this -> historial.empty()){
        cout << " Historial vacío" << "\n";
        return;
    }
    Stack<Persona> copia(this -> historial);
    cout << "--- Historial de atención (más reciente primero) ---" << "\n";
    while (!copia.empty()){
        Persona p = copia.top() -> getValor();
        mostrarPersona(p);
        copia.pop();
    }
}

Lista<Departamento*>* SystemImpl::getLista(){
    return this->listaDepartamentos;
}

SystemImpl::~SystemImpl(){
    for (int i = 0; i < this -> listaDepartamentos -> size(); i++) {
        delete this -> listaDepartamentos -> obtener(i);
    }
    delete this->listaDepartamentos;
}


