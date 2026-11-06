#include "Contrato.h"

int Contrato::contador=1;

Contrato::Contrato(long int dni, Fecha f): idContrato(contador), fechaContrato(f) {
  //idContrato=contador; //ERROR es constante y debe ir en zona inicializadores
  Contrato::contador++;
  this->dniContrato=dni;
  //this->fechaContrato=f; //ERROR es tipo no primitivo y debe ir en zona inicializadores
}

Contrato::~Contrato() {
    //dtor
}


void Contrato::ver() const {
  cout << this->dniContrato << " (" << this->idContrato << " - ";
  this->fechaContrato.ver(); //llamo al ver del objeto fecha
  cout << ")";
}

// --- DEFINICIÓN DEL NUEVO MÉTODO VIRTUAL ---
void Contrato::imprimir(ostream& s) const {
    // Imprime solo la parte base
    // (Usa los getters porque es 'const' y para respetar el encapsulamiento)
    s << this->getDniContrato() << " (" << this->getIdContrato() << "-" << this->getFechaContrato() << ")";
}
// --- MODIFICACIÓN DEL OPERATOR<< ---
ostream& operator<<(ostream &s, const Contrato &c) {
    // 1. Llama al método VIRTUAL.
    // 2. C++ elegirá la versión correcta (TP o Movil) en tiempo de ejecución.
    c.imprimir(s);
    return s;
}
/*

El operator << usado antes
ostream& operator<<(ostream &s, const Contrato &c) {
  s << c.getDniContrato() << " (" << c.getIdContrato() << " - " << c.getFechaContrato() << " )";
  return s;
}


*/
