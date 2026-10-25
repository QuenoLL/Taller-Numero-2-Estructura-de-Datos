#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>
#include "SystemImpl.hpp"
#include "../Estructuras/Nodo.hpp"

using namespace std;

static string trim(string s){
    size_t i = 0;
    while(i < s.size() && isspace((unsigned char)s[i])) i++;
    size_t j = s.size();
    while(j > i && isspace((unsigned char)s[j - 1])) j--;
    return s.substr(i, j - i);
}

static string aMinus(string s){
    for(size_t i = 0; i < s.size(); i++) s[i] = tolower((unsigned char)s[i]);
    return s;
}

static bool aEntero(string s, int& out){
    if(s.empty()) return false;
    try{
        size_t pos = 0;
        int v = stoi(s, &pos);
        if(pos != s.size()) return false;
        out = v;
        return true;
    }catch(...){
        return false;
    }
}

static bool aDecimal(string s, float& out){
    if(s.empty()) return false;
    for(size_t i = 0; i < s.size(); i++){
        if(s[i] == ',') s[i] = '.';
    }
    try{
        size_t pos = 0;
        float v = stof(s, &pos);
        if(pos != s.size()) return false;
        out = v;
        return true;
    }catch(...){
        return false;
    }
}

static string unDecimal(float f){
    ostringstream o;
    o << fixed << setprecision(1) << f;
    return o.str();
}

static string siNo(int v){ return v == 1 ? "Si" : "No"; }
static string diasTexto(int d){ return d == 0 ? "Ninguno" : to_string(d); }
 
static bool tipoDolorValido(string t){
    return t == "pecho" || t == "cabeza";
    t == "abdomen" || t == "extremidad" || t == "otro";
}

static void imprimirAtencion(Persona& p){
    cout << "ID: " << p.getIdFormateado() << "\n";
    cout << "Nombre: " << p.getName() << "\n";
    cout << "Edad: " << p.getEdad() << "\n";
    cout << "Temperatura: " << unDecimal(p.getTempCorporal()) << "\n";
    cout << "Presion Arterial: " << unDecimal(p.getPresionArterial()) << "\n";
    cout << "Dolor: " << p.getDolor() << "\n";
    cout << "TipoDolor: " << p.getTipoDolor() << "\n";
    cout << "Trauma: " << p.getTrauma() << "\n";
    cout << "Sintomas Neurologicos: " << p.getSintomasNeu() << "\n";
    cout << "Requiere Cirugia: " << p.getRequiereC() << "\n";
    cout << "DiasHospitalizacion: " << p.getDiasHospital() << "\n";
}

static void imprimirFicha(Persona& p, string departamento){
    cout << "ID: " << p.getIdFormateado() << "\n";
    cout << "Nombre: " << p.getName() << "\n";
    cout << "Edad: " << p.getEdad() << "\n";
    cout << "Departamento: " << departamento << "\n";
    cout << "T: " << unDecimal(p.getTempCorporal()) << "° | D: " << p.getDolor()
         << " | TD: " << p.getTipoDolor() << " | T: " << siNo(p.getTrauma())
         << " | SN: " << siNo(p.getSintomasNeu()) << " | RC: " << siNo(p.getRequiereC())
         << " | DH: " << diasTexto(p.getDiasHospital()) << "\n";
}

SystemImpl::SystemImpl(){
    this->listaDepartamentos = new Lista<Departamento*>();
}

void SystemImpl::crearPersonas(vector<string> partes){
    if(partes.empty()){
        return;
    }
    if(partes.size() != 11){
        cout << "Línea omitida (datos insuficientes o campos de más: " << partes.size() << " de 11)." << "\n";
        return;
    }
    for(size_t i = 0; i < partes.size(); i++){
        partes[i] = trim(partes[i]);
}

int id = 0, edad = 0, dolor = 0, trauma = 0, sn = 0, rc = 0, dias = 0;
float temp = 0, pres = 0;
string tipoDolor = aMinus(partes[6]);
string error = "";

if(!aEntero(partes[0], id) || id <= 0) error = "ID inválido";
else if(partes[1].empty()) error = "nombre vacío";
else if(!aEntero(partes[2], edad) || edad < 0 || edad > 120) error = "edad inválida";
else if(!aDecimal(partes[3], temp) || temp < 30 || temp > 45) error = "temperatura inválida";
else if(!aDecimal(partes[4], pres) || pres < 40 || pres > 300) error = "presión arterial inválida";
else if(!aEntero(partes[5], dolor) || dolor < 0  || dolor > 10) error = "dolor fuera de 0-10";
else if(!tipoDolorValido(tipoDolor)) error = "tipo de dolor inválido";
else if(!aEntero(partes[7], trauma) || (trauma != 0 && trauma != 1)) error = "trauma debe ser 0 o 1";
else if(!aEntero(partes[8], sn) || (sn != 0 && sn != 1)) error = "síntomas neurológicos deben ser 0 o 1";
else if(!aEntero(partes[9], rc) || (rc != 0 && rc != 1)) error = "requiere cirugía debe ser 0 o 1";
else if(!aEntero(partes[10], dias) || dias < 0 || dias > 365) error = "días de hospitalización inválidos";
else if(estaDuplicada(id)) error = "paciente duplicado";

if(!error.empty()){
    cout << "Línea omitida (" << error << "): ID '" << partes[0] << "'" << "\n";
    return;
}   
 
    Persona p(id, partes[1], edad, temp, pres, dolor, tipoDolor, trauma, sn, rc, dias);
    this->colaPacientes.push(p);
}

void SystemImpl::crearDepartamentos(){
    vector<string> deptos = {"Urgencias", "Medicina General", "Cardiologia", "Neurologia", "Traumatologia", "Cirugia", "Pediatria", "Hospitalizacion"};
 
    for(string nombre : deptos){
        Departamento* dep = new Departamento(nombre);
        this->listaDepartamentos->agregar(dep);
    }
}

Departamento* SystemImpl::buscarDepartamento(string nombre){
    for(int i = 0; i < this->listaDepartamentos->size(); i++){
        Departamento* dep = this->listaDepartamentos->obtener(i);
        if(dep->getName() == nombre){
            return dep;
        }
    }
    return nullptr;
}

bool SystemImpl::estaDuplicada(int id){
    for(Nodo<Persona>* n = this->colaPacientes.front(); n != nullptr; n = n->getSiguiente()){
        if(n->getValor().getId() == id) return true;
    }
    // En los AVL
    string ruta;
    for(int i = 0; i < this->listaDepartamentos->size(); i++){
        if(this->listaDepartamentos->obtener(i)->getArbol()->buscarPorId(id, ruta) != nullptr) return true;
    }
    return false;
}

void SystemImpl::procesarSiguiente(){
    Persona p = this->colaPacientes.front()->getValor();
    this->colaPacientes.pop();
 
    string ruta;
    string servicio = this->arbolDecision.clasificar(p, ruta);
    p.setServicio(servicio);
 
    imprimirAtencion(p);
    cout << "\n" << "Ruta: " << ruta << "\n";
    cout << "Servicio asignado: " << servicio << "\n";
 
    Departamento* dep = this->buscarDepartamento(servicio);
    if(dep == nullptr){
        cout << "ERROR: el servicio '" << servicio << "' no existe. Paciente no insertado." << "\n\n";
        return;
    }
 
    Persona* nuevo = new Persona(p); // el AVL queda como dueño de esta copia
    if(dep->getArbol()->insertar(nuevo)){
        cout << "Paciente insertado en el AVL de " << servicio << "." << "\n\n";
    }else{
        delete nuevo;
        cout << "Paciente duplicado en " << servicio << ", no fue insertado." << "\n\n";
    }
}

void SystemImpl::atenderPaciente(){
    if(this->colaPacientes.empty()){
        cout << "No hay pacientes en espera." << "\n";
        return;
    }
    cout << "=== ATENDIENDO PACIENTES ===" << "\n";
    while(!this->colaPacientes.empty()){
        this->procesarSiguiente();
    }
}
 
void SystemImpl::verDepartamento(){
    cout << "=== ESTADO DE LOS DEPARTAMENTOS ===" << "\n";
    for(int i = 0; i < this->listaDepartamentos->size(); i++){
        Departamento* dep = this->listaDepartamentos->obtener(i);
        cout << dep->getName() << "\n";
        if(dep->getArbol()->empty()){
            cout << "Sin pacientes" << "\n\n";
        }else{
            cout << "Pacientes: " << dep->getArbol()->resumen() << "\n\n";
        }
    }
}

void SystemImpl::listarDepartamentos(){
    for(int i = 0; i < this->listaDepartamentos->size(); i++){
        cout << (i + 1) << ".- " << this->listaDepartamentos->obtener(i)->getName() << "\n";
    }
}
 
int SystemImpl::cantidadDepartamentos(){
    return this->listaDepartamentos->size();
}

void SystemImpl::verRecorrido(int indice, int tipo){
    if(indice < 0 || indice >= this->listaDepartamentos->size()){
        cout << "Departamento inválido" << "\n";
        return;
    }
    Departamento* dep = this->listaDepartamentos->obtener(indice);
    ArbolAvl* arbol = dep->getArbol();
 
    cout << "--- " << dep->getName() << " (" << arbol->size() << " pacientes) ---" << "\n";
    if(arbol->empty()){
        cout << "Sin pacientes" << "\n";
        return;
    }

    switch(tipo){
            case 1: cout << "Inorden:   "; arbol->inorden(); break;
            case 2: cout << "Preorden:  "; arbol->preorden(); break;
            case 3: cout << "Postorden: "; arbol->postorden(); break;
            case 4: cout << "Altura del árbol: " << arbol->getAltura() << "\n"; break;
            case 5:
                cout << "Altura del árbol: " << arbol->getAltura() << "\n";
                cout << "Factor de balance por nodo (altura izq - altura der):" << "\n";
                arbol->mostrarBalance();
                break;
            default: cout << "Opción inválida" << "\n";
    }
}

void SystemImpl::buscarPaciente(string clave){
    clave = trim(clave);
    if(clave.empty()){
        cout << "Debe ingresar un ID o un nombre." << "\n";
        return;
    }
    int id = 0;
    bool porId = aEntero(clave, id);
 
    cout << "Buscando en AVL..." << "\n";
    for(int i = 0; i < this->listaDepartamentos->size(); i++){
        Departamento* dep = this->listaDepartamentos->obtener(i);
        string ruta;
        Persona* p = porId ? dep->getArbol()->buscarPorId(id, ruta)
                           : dep->getArbol()->buscarPorNombre(clave, ruta);
        if(p != nullptr){
            cout << "Paciente encontrado:" << "\n";
            imprimirFicha(*p, dep->getName());
            cout << "\n" << "Ruta de búsqueda:" << "\n" << ruta << "\n";
            return;
        }
    }
    cout << "Paciente no encontrado." << "\n";
}

void SystemImpl::eliminarPaciente(int id){
    for(int i = 0; i < this->listaDepartamentos->size(); i++){
        Departamento* dep = this->listaDepartamentos->obtener(i);
        string ruta;
        Persona* p = dep->getArbol()->buscarPorId(id, ruta);
        if(p != nullptr){
            string nombre = p->getName();
            dep->getArbol()->eliminar(id);
            cout << "Paciente " << nombre << " (" << id << ") eliminado del AVL de " << dep->getName()
                 << ". Altura actual: " << dep->getArbol()->getAltura() << "\n";
            return;
        }
    }
    cout << "No existe un paciente con ID " << id << "." << "\n";
}

void SystemImpl::verArbolDecision(int tipo){
    switch(tipo){
        case 1: cout << "--- Árbol de decisión: PREORDEN ---" << "\n"; this->arbolDecision.preorden(); break;
        case 2: cout << "--- Árbol de decisión: INORDEN (si - nodo - no) ---" << "\n"; this->arbolDecision.inorden(); break;
        case 3: cout << "--- Árbol de decisión: POSTORDEN ---" << "\n"; this->arbolDecision.postorden(); break;
        default: cout << "Opción inválida" << "\n";
    }
}
 
SystemImpl::~SystemImpl(){
    for(int i = 0; i < this->listaDepartamentos->size(); i++){
        delete this->listaDepartamentos->obtener(i);
    }
    delete this->listaDepartamentos;
}

