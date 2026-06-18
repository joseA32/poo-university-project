#include "Fecha.h"

Fecha::Fecha(const int &dia, const int &m, const int &anio) {
    this->setFecha(dia, m, anio); //el cogido es el mismo que el del metodo setFecha
}

void Fecha::setFecha(const int &dia, const int &mes, const int &a) {
    int dmax, diaMes[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};


    this->anio=a; //VIP debo asignar año para que al llamar a bisiesto() tenga el año bien
    if (this->bisiesto())
        diaMes[2]=29;

    if (mes<1)  //si el mes es incorrecto
      this->mes=1;
    else if (mes>12) //si el mes es incorrecto
      this->mes=12;
    else
      this->mes=mes;
    dmax=diaMes[this->mes]; //una vez fijado el mes veo cuantos dias tiene ese mes como maximo

    if (dia>dmax) //si dia es superior al numero de dias de dicho mes
      this->dia=dmax;
    else if (dia<1) //si dia es inferior a 1
      this->dia=1;
    else
      this->dia=dia;
}


bool Fecha::bisiesto() const {
    // Un año es bisiesto si es divisible por 4,
    // excepto si es divisible por 100, a menos que
    // también sea divisible por 400.
    //
    // 1900 es divisible por 4 y 100, pero NO por 400 -> NO es bisiesto.
    // 2000 es divisible por 4, 100 y 400 -> SÍ es bisiesto.
    // 2004 es divisible por 4, pero NO por 100 -> SÍ es bisiesto.
    // 2001 NO es divisible por 4 -> NO es bisiesto.

    return (this->anio % 4 == 0 && this->anio % 100 != 0) || (this->anio % 400 == 0);
}

void Fecha::ver() const {
  if (this->dia < 10)
    cout << "0";
  cout << this->dia << "/";
  if (this->mes < 10)
    cout << "0";
  cout << this->mes << "/" << this->anio;
}

//++f
Fecha Fecha::operator++() {
    // 1. Incrementa el objeto actual
    int dmax, diaMes[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if (this->bisiesto()) //si el año es bisiesto febrero tiene 29 dias
      diaMes[2]=29;
    dmax=diaMes[this->mes];
    this->dia++;
    if (this->dia>dmax) { //si al incrementar dia superamos el numero de dias de dicho mes
        this->dia=1;      //pasamos a 1
        this->mes++;      //del mes siguiente
        if (this->mes>12) { //si al incrementar mes pasamos de 12 meses
            this->mes=1;    //pasamos al mes 1
            this->anio++;   //del año siguiente
        }
    }
    return *this; //devolvemos el objeto fecha ya incrementado
}

//RESTO DE METODOS Y FUNCIONES IMPLEMENTADOS:

// Post-incremento (f++)
Fecha Fecha::operator++(int i) {
    // 1. Guarda una copia del estado actual del objeto
    Fecha f_ant = *this;

    // 2. Incrementa el objeto actual (llama al operator++() que ya tenías)
    //    Esto modifica 'f4'
    ++(*this);

    // 3. Devuelve la copia antigua que guardaste.
    //    Esto es lo que se asignará a 'f3'
    return f_ant;
}


// Suma (f + 5)
Fecha Fecha::operator+(const int &i) const {
    // 1. Creamos una copia de la fecha actual
    //    Es 'const', por lo que NO PODEMOS modificar 'this'.
    Fecha fecha_resultado = *this;
    for (int j = 0; j < i; ++j) {
        // 3. Llamamos al operador de pre-incremento (++f) que
        //    ya tenía hecho sobre la COPIA.
        ++fecha_resultado;
    }

    // 4. Devolvemos la copia ya modificada. La fecha original (f2) no ha cambiado.
    return fecha_resultado;
}

// Suma (5 + f)
Fecha operator+(const int &i, const Fecha &f) {
    // No reinventamos la rueda.
    // Como 2 + f2 es lo mismo que f2 + 2,
    // simplemente llamamos al operador miembro que ya programamos.
    return f + i; // Esto llama a f.operator+(i)

}

// Operador de inserción (cout << f) para formato "07 oct 2015"
ostream& operator<<(ostream &s, const Fecha &f) {
    // Array de nombres de meses
    const char* meses[] = {"ene", "feb", "mar", "abr", "may", "jun",
                           "jul", "ago", "sep", "oct", "nov", "dic"};

    // Imprime el día
    if (f.dia < 10) s << "0";
    s << f.dia << " ";

    // Imprime el mes (en texto)
    s << meses[f.mes - 1] << " "; // f.mes-1 porque el array empieza en 0

    // Imprime el año
    s << f.anio;

    return s; // Devuelve el 'stream' para poder encadenar más "<<"
}




