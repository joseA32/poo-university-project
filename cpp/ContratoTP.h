#ifndef CONTRATOTP_H
#define CONTRATOTP_H

#include <iostream> //cin, cout
#include "Fecha.h"
#include "Contrato.h"

using namespace std;

class ContratoTP: public Contrato {//Herencia pública
  static int minutosTP;
  static float precioTP;
  int minutosHablados;
  static const float precioExcesoMinutos;

public:
  ContratoTP(long int dni, Fecha f, int m);
  //virtual ~ContratoTP(); //¿es necesario? pensar y reflexionad
  //ContratoTP(const ContratoTP& c);  //¿es necesario? pensar y reflexionad
  //ContratoTP& operator=(const ContratoTP& c); //¿es necesario? pensar y reflexionad

  // Getters y Setters estáticos (se llaman con ContratoTP::)
  static int getLimiteMinutos() { return ContratoTP::minutosTP; }
  static float getPrecio() { return ContratoTP::precioTP; }
  static void setTarifaPlana(int m, float p); //el el .cpp se pone la cabecera sin la palabra static

  //Metodos anadidos 
  // Constructor de copia (usado en ContratoTP ct3 (ct1)
  ContratoTP(const ContratoTP& c);

// Getters y Setters para los minutos (usados en ct1.setMinutosHablados, ...)
int getMinutosHablados() const;
void setMinutosHablados(int m);

// Métodos de cálculo y visualización
float factura() const; // (Usado en "ct1.factura()")
virtual void ver() const; // (Redefine el 'ver' de Contrato)

//-----------------Redefino el nuevo método de la clase base---------------------
virtual void imprimir(ostream& s) const;

};
//Quitamos el operator<< de aquí
//ostream& operator<<(ostream &s, const ContratoTP &c);

#endif // CONTRATOTP_H
