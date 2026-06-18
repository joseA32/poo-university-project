#include "ContratoTP.h"
#include <iomanip> // <-- VIP: Añade esto para setprecision

// ... (Las inicializaciones estáticas y setTarifaPlana que ya tengo) ...
// === INICIALIZACIÓN DE ATRIBUTOS ESTÁTICOS ===

int ContratoTP::minutosTP = 300;
float ContratoTP::precioTP = 10;
const float ContratoTP::precioExcesoMinutos = 0.15;

void ContratoTP::setTarifaPlana(int m, float p) {
    ContratoTP::minutosTP = m; //puedo poner minutosTP=m ...pongo ContratoTP::minutosTP para recordar que es estatico
    ContratoTP::precioTP = p;  //puedo poner precioTP=p  ...pongo ContratoTP::precioTP para recordar que es estatico
}


// === CONSTRUCTOR ===
// Llama al constructor de la clase base 'Contrato' y luego inicializa 'minutosHablados'
/*Es un Constructor de Copia (Genera nuevo ID)
 Llamamos al constructor NO-copia de la base.
 Esto es un "truco" de la práctica para que una copia
 (ej. ct3(ct1)) tenga un ID nuevo (ID 5) en vez de
 copiar el ID antiguo (ID 3).
 */
ContratoTP::ContratoTP(long int dni, Fecha f, int m) : Contrato(dni, f) {
    this->minutosHablados = m;
}

// === CONSTRUCTOR DE COPIA ===
// Llama al constructor de copia de 'Contrato' y copia los atributos propios de esta clase
ContratoTP::ContratoTP(const ContratoTP& c) : Contrato(c.getDniContrato(), c.getFechaContrato()) {
    this->minutosHablados = c.minutosHablados;
}

// === GETTERS Y SETTERS ===
int ContratoTP::getMinutosHablados() const {
    return this->minutosHablados;
}

void ContratoTP::setMinutosHablados(int m) {
    this->minutosHablados = m;
}

// === MÉTODOS DE CÁLCULO Y VISUALIZACIÓN ===
// Implementación de 'factura' (obligatoria)
float ContratoTP::factura() const {
    float exceso = 0;
    // Comprueba si se ha pasado del límite
    if (this->minutosHablados > ContratoTP::minutosTP) {
            exceso = this->minutosHablados - ContratoTP::minutosTP;
    }

    // Calcula la factura según la fórmula
    // factura = precio tarifa plana + (exceso limite minutos x 0.15)
    return ContratoTP::precioTP + (exceso * ContratoTP::precioExcesoMinutos);
}
// Redefinición de 'ver' (Polimorfismo)
void ContratoTP::ver() const {
    // 1. Llama al 'ver()' de la clase base (Contrato)
    Contrato::ver();

    // 2. Añade la información propia de ContratoTP
    // Formato de salida: ... 250m, 300 (10)
    cout << " " << this->minutosHablados << "m, ";
    cout << ContratoTP::minutosTP << " (" << ContratoTP::precioTP << ")";
}
// Redefinición de 'imprimir' (Polimorfismo)
void ContratoTP::imprimir(ostream& s) const {
    // 1. Llama al método base para imprimir DNI, ID, Fecha
    Contrato::imprimir(s);

    // 2. Imprime los datos específicos de TP
    // Formato: ... 250m, 300(10.00) - 10.00€
    s << " " << this->minutosHablados << "m, ";
    s << ContratoTP::getLimiteMinutos() << "(";
    s << fixed << setprecision(2) << ContratoTP::getPrecio() << ")";
    s << " - " << this->factura() << "€";
}
// === OPERADOR << antiguo, lo quitamos ===

/*
ostream& operator<<(ostream &s, const ContratoTP &c) {
    // 1. Llama al 'operator<<' de la clase base (Contrato)
    // Hacemos un "cast" a Contrato para que sepa cuál usar
    s << static_cast<const Contrato&>(c);

    // 2. Añade la información de ContratoTP y la factura
    // Formato: ... 360m, 350(12.00) 13.50€
    s << " " << c.getMinutosHablados() << "m, " << ContratoTP::getLimiteMinutos();
    s << "(" << fixed << setprecision(2) << ContratoTP::getPrecio() << ") ";
    s << c.factura() << "€"; // Llama a factura()

    return s;
}
*/
