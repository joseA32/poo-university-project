#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream> //cin, cout
#include "Fecha.h"

using namespace std;
//SI FALTA ALGUN METODO O FUNCION AÑADIRLO...
class Cliente {
  long int dni;
  char *nombre;//Este puntero obliga a crear una regla de 3
  Fecha fechaAlta;
public:
    /*Constructor por defecto Necesario para crear el array 'Cliente clientes[100]' en Empresa.
    */
    Cliente(); // <-- Constructor por defecto para poder poner arrays estáticos
  Cliente(long int d, const char *nom, Fecha f);//añado el const para pasar el const* char del main

   /*"La Regla de 3"
   * Si tienes un puntero (char*), NECESITAS definir:
   * 1. Destructor (~Cliente)
   * 2. Constructor de Copia (Cliente(const Cliente& c))
   * 3. Operador de Asignación (operator=)
   * (Cliente.cpp tiene el constructor de copia de oficio comentado,
   * pero aquí lo hemos implementado en el operator=)
   */
  virtual ~Cliente();
  Cliente& operator=(const Cliente& c);

  long int getDni() const { return this->dni; }
  const char* getNombre() const { return nombre; } //VIP devolver un puntero constante para evitar que desde el main() se puede modificar el nombre
  Fecha getFecha() const { return fechaAlta; }

  void setNombre(const char *nom);//Aquí también añado el const para pasar const* char del main
  void setFecha(Fecha f);
 /*
   Paso por Referencia (&) vs Valor
   El código base tenía 'Cliente c' (por valor).
   ERROR: Al llamar 'if (j == c)', creaba una copia,
   y el destructor de la copia borraba la memoria de 'c' original.
   SOLUCIÓN: Pasar por referencia 'Cliente& c' (o 'const Cliente& c')
   para que no se cree ninguna copia.
   */
  bool operator==(Cliente& c) const; // if (c1 ===c2). El & es vital para que el nombre no se destruya

};

ostream& operator<<(ostream &s, const Cliente &c); //funcion no amiga de la clase

#endif // CLIENTE_H
