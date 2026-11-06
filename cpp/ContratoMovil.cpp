#include <iostream>
#include <cstdlib>
#include <cstring> //strlen, strcpy
#include <iomanip> //std::setprecision
#include "Contrato.h"
#include "ContratoMovil.h"

ContratoMovil::ContratoMovil(long int dni, Fecha f, float p, int m, const char *nac): Contrato(dni, f) {//ponemos el const aquí también
  this->precioMinuto=p;
  this->minutosHablados=m;
  //this->nacionalidad=nac;  //MAL!!!!
  this->nacionalidad=new char [strlen(nac)+1];
  strcpy(this->nacionalidad, nac);
}

ContratoMovil::~ContratoMovil() {
    // Libera la memoria del puntero
    delete [] this->nacionalidad;
}

//ContratoMovil::ContratoMovil(const ContratoMovil& c):Contrato(c) { //IMPORTANTE: SI PONGO ESTA CABECERA y no implemento un constructor de copia en CONTRATO
                                                                     //NO DA ERROR AL COMPILAR PORQUE EL COMPILADOR GENERA UN CONSTRUCTOR COPIA POR SU CUENTA...
                                                                     //...EL PROBLEMA ES QUE EL QUE GENERA EL COMPILADOR NO INCREMENTA contador
                                                                     //Y ASIGNARIA EL MISMO CODIGO A AMBOS CONTRATOS
                                                                     //solucion: implementar constructor copia en CONTRATO y usar esta cabecera...
ContratoMovil::ContratoMovil(const ContratoMovil& c):Contrato(c.getDniContrato(), c.getFechaContrato()) { //... o usar esta otra cabecera
  this->precioMinuto=c.precioMinuto;
  //terminar de implementarlo...
  this->minutosHablados = c.minutosHablados;

  // Copia profunda para el puntero
  this->nacionalidad = new char[strlen(c.nacionalidad) + 1];
  strcpy(this->nacionalidad, c.nacionalidad);
}

void ContratoMovil::ver() const {
  Contrato::ver(); //IMPORTANTE: llamamos al ver que heredo de mi padre PARA QUE MUESTRE LO DEL PADRE
                   //... y a continuacion solo "me preocupo" de mostrar lo que es exclusivo del hijo
  cout << " " << this->minutosHablados << "m, " << this->nacionalidad << " " << this->precioMinuto;
}

float ContratoMovil::factura() const {
  //implementarlo...
  return this->precioMinuto * this->minutosHablados;
}


void ContratoMovil::setNacionalidad(const char* nac) {//añadimos el const
    // 1. Libera la memoria antigua
    delete [] this->nacionalidad;

    // 2. Reserva memoria nueva
    this->nacionalidad = new char[strlen(nac) + 1];
    // 3. Copia la nueva nacionalidad
    strcpy(this->nacionalidad, nac);

}
// --- DEFINICIÓN DEL MÉTODO REDEFINIDO ---
void ContratoMovil::imprimir(ostream& s) const {
    // 1. Llama al método base para imprimir DNI, ID, Fecha
    Contrato::imprimir(s);

    // 2. Imprime los datos específicos de Movil
    // Formato: ... 110m, DANES 0.12 - 13.20€
    s << " " << this->minutosHablados << "m, " << this->nacionalidad << " ";
    s << fixed << setprecision(2) << this->precioMinuto;
    s << " - " << this->factura() << "€";
}

/*ostream& operator<<(ostream &s, const ContratoMovil &c) {
  s << (Contrato &)c; //IMPORTANTE: convierto el objeto c (ContratoMovil &) a objeto Contrato &
                      // de esta forma se cree que es un objeto Contrato y muestra lo que indica el operator<< de Contrato
                      //... y a continuacion solo "me preocupo" de mostrar lo que es exclusivo del hijo
  s << " " << c.getMinutosHablados() << "m, " << c.getNacionalidad() << " " << c.getPrecioMinuto() << " - ";
  s << c.factura() << "€";
  return s;
}
*/
