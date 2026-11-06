#ifndef CONTRATO_H
#define CONTRATO_H

#include <iostream> //cin, cout
#include "Fecha.h"

//Para hacer contrato abstracta, tiene que tener un método viertual puro, poniéndole un =0 en el .h
using namespace std;

class Contrato {
  static int contador;
  const int idContrato;
  long int dniContrato;
  Fecha fechaContrato;
public:
  Contrato(long int dni, Fecha f);
  virtual ~Contrato();
//Contrato(const Contrato& c); //¿es necesario? pensar y reflexionad

//Contrato& operator=(const Contrato& c); //no es necesario y ademas no puede ser usado porque Contrato tiene un
                                          //atributo constante idContrato que no puede modificarse
                                          //no se puede usar el = en el main con objetos Contrato

  int getIdContrato() const { return this->idContrato; }
  long int getDniContrato() const { return this->dniContrato; }
  Fecha getFechaContrato() const { return this->fechaContrato; }
  void setFechaContrato(Fecha f) { this->fechaContrato=f; }
  void setDniContrato(long int dni) { this->dniContrato=dni; }
  virtual void ver() const;

  //añadido en parte 3:

  virtual float factura() const=0;//ContratoTP y ContratoMovil ya sabían calcular factura, luego este método es perfecto
  // --- ESTO ES LO NUEVO ---
    // Método virtual auxiliar para que operator<< sea polimórfico
    virtual void imprimir(ostream& s) const;

    // Este es el ÚNICO operator<< que debe existir como 'friend'
    friend ostream& operator<<(ostream &s, const Contrato &c);
    // --- FIN DE LO NUEVO ---
};

ostream& operator<<(ostream &s, const Contrato &c);

#endif // CONTRATO_H
