#include <cstdlib>
#include <cstring> //strlen, strcpy
#include <iomanip> //std::setprecision
#include <sstream> //stringstream
#include "Cliente.h"

// === Constructor por Defecto (NUEVO para poder implementar empresa) ===
Cliente::Cliente() : fechaAlta(1, 1, 2000) { // Inicializa la fecha a algo válido
    this->dni = 0;
    this->nombre = new char[1]; // Reserva 1 byte
    this->nombre[0] = '\0';   // Lo deja como cadena vacía ""
}

//Cliente::Cliente(long int d, char *nom, Fecha f):fechaAlta(f.getDia(), f.getMes(), f.getAnio()) {
Cliente::Cliente(long int d, const char *nom, Fecha f):fechaAlta(f) { //esta cabecera es mas corta (invoco
  this->dni=d;                                                  //constructor copia de fecha
                                                                //en vez de constructor de 3 parametros)
  //this->nombre=nombre;  //MAL!!!!
  this->nombre=new char[strlen(nom)+1];
  strcpy(this->nombre, nom);

  //this->fechaAlta=f;//MAL!!!! los tipos no primitivos debe ir en zona inicializadores
}

Cliente::~Cliente() {
  delete [] this->nombre; //si en el constructor uso new [] en el destructor uso delete []
}

Cliente& Cliente::operator=(const Cliente& c) {
  if (this != &c) { //si no es x=x
    this->dni=c.dni;
    delete [] this->nombre;
    //this->nombre=c.nombre;  //MAL!!!!
    this->nombre=new char[strlen(c.nombre)+1];
    strcpy(this->nombre, c.nombre);
    this->fechaAlta=c.fechaAlta;
  }
  return *this;
}

bool Cliente::operator==(Cliente &c) const {
  if (this->dni!=c.dni) return false;
  if (strcmp(this->nombre, c.nombre)!=0) return false;
  if (this->fechaAlta.getDia()!=c.fechaAlta.getDia() ||
      this->fechaAlta.getMes()!=c.fechaAlta.getMes() ||
      this->fechaAlta.getAnio()!=c.fechaAlta.getAnio()) return false;
  return true;
}

void Cliente::setNombre(const char *nom) {
    // Esto es vital para la robustez  y evitar fugas de memoria

    // 1. Libera la memoria que 'this->nombre' estaba usando antes
    delete [] this->nombre;

    // 2. Reserva memoria nueva para el nombre que nos pasan
    this->nombre = new char[strlen(nom) + 1];

    // 3. Copia el nuevo nombre en la memoria recién reservada
    strcpy(this->nombre, nom);
}

void Cliente::setFecha(Fecha f) {
    // Como 'fechaAlta' no es un puntero, una simple asignación es suficiente.
    this->fechaAlta = f;
}

// Operador de inserción (cout << c)
// Nota: Esta función NO es un método de Cliente, por eso no lleva 'Cliente::'
ostream& operator<<(ostream &s, const Cliente &c) {
    // 1. Imprime el nombre y el DNI
    s << c.getNombre() << " (" << c.getDni() << "-";

    // 2. Aquí está la clave:
    //    Llama al 'operator<<' de la clase Fecha que creaste antes
    s << c.getFecha();

    // 3. Cierra el paréntesis
    s << ")";

    // 4. Devuelve el stream para poder encadenar
    return s;
}
//RESTO DE METODOS Y FUNCIONES A RELLENAR POR EL ALUMNO...
