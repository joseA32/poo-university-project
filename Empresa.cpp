#include "Empresa.h"
#include <iostream>
#include <iomanip>  // Para setprecision
#include <typeinfo> // Para el Paso 4 (typeid)


using namespace std;





// CONSTRUCTOR
Empresa::Empresa() {
    this->nClientes = 0;
    this->nContratos = 0;

    // Inicializa el array dinámico con tamaño 10
    this->capContratos = 10;
    this->contratos = new Contrato*[this->capContratos];
}

//DESTRUCTOR
Empresa::~Empresa() {
    // 1. Libera la memoria de CADA objeto Contrato
    for (int i = 0; i < this->nContratos; i++) {
        delete this->contratos[i]; // Borra el ContratoTP o ContratoMovil
        this->contratos[i] = NULL; // Buena práctica
    }

    // 2. Libera la memoria del array de punteros
    delete [] this->contratos; // El array 'clientes[100]' se destruye solo (memoria estática)
}


Empresa::Empresa(const Empresa& otra)
{
    for (int i=0; i<otra.nClientes; i++)
    {
        this->clientes[i]=otra.clientes[i];
    }
    this->nClientes=otra.nClientes;
    this->nContratos=otra.nContratos;
    this->capContratos=otra.capContratos;

    this->contratos=new Contrato* [this->capContratos];

    for (int i=0; i<this->nContratos; i++)
    {
        ContratoMovil* cm = dynamic_cast<ContratoMovil*>(otra.contratos[i]);

        if (cm !=NULL)
        {
            this->contratos[i]=new ContratoMovil(*cm);
        }
        else
        {
            ContratoTP* cTP = dynamic_cast <ContratoTP*> (otra.contratos[i]);
            if (cTP!=NULL)
            {
                this->contratos[i]=new ContratoTP (*cTP);
            }

        }



    }











}

// Métodos privados

void Empresa::redimensionar() {
    // 1. Duplica la capacidad
    int nuevaCapacidad = this->capContratos * 2;

    // 2. Crea un nuevo array con el doble de capacidad
    Contrato** nuevoArr = new Contrato*[nuevaCapacidad];

    // 3. Copia los punteros antiguos al array nuevo
    for (int i = 0; i < this->nContratos; i++) {
        nuevoArr[i] = this->contratos[i];
    }

    // 4. Borra el array antiguo (SOLO el array, no los 'delete' de los objetos contrato)
    delete [] this->contratos;

    // 5. Apunta al nuevo array
    this->contratos = nuevoArr;

    // 6. Actualiza la capacidad
    this->capContratos = nuevaCapacidad;
}

int Empresa::buscarCliente(long int dni) {//Buscar un cliente por dni
    for (int i = 0; i < this->nClientes; i++) {
        // Usamos . (punto) porque clientes[i] es un OBJETO
        if (this->clientes[i].getDni() == dni) {
            return i; // Devuelve la posición si lo encuentra
        }
    }
    return -1; // No se encontró
}

int Empresa::buscarContrato(int id) {//Buscar un contrato por ID en el array de punteros
    for (int i = 0; i < this->nContratos; i++) {
        // Usamos -> (flecha) porque contratos[i] es un PUNTERO
        if (this->contratos[i]->getIdContrato() == id) {
            return i; // Devuelve la posición si lo encuentra
        }
    }
    return -1; // No se encontró
}


//MÉTODOS PÚBLICOS


void Empresa::cargarDatos() {
    // --- Clientes de prueba ---
    // (Usamos el operador '=' que nos da C++ por defecto para la clase Cliente,
    // que funciona bien porque Cliente gestiona su memoria con su constructor de copia y operador=)

    clientes[0] = Cliente(75547001, "Peter Lee", Fecha(28, 2, 2001));
    clientes[1] = Cliente(45999000, "Juan Perez", Fecha(29, 2, 2000));
    clientes[2] = Cliente(37000017, "Luis Bono", Fecha(31, 1, 2002));
    this->nClientes = 3;

    // --- Contratos de prueba ---
    // (Asegúrate de que la capacidad 'capContratos' es al menos 10)
    contratos[0] = new ContratoMovil(75547001, Fecha(28, 2, 2001), 0.12, 110, "DANES");
    contratos[1] = new ContratoMovil(75547001, Fecha(31, 1, 2002), 0.09, 170, "DANES");
    contratos[2] = new ContratoTP(37000017, Fecha(1, 2, 2002), 250);
    contratos[3] = new ContratoTP(75547001, Fecha(28, 2, 2001), 312);
    contratos[4] = new ContratoMovil(45999000, Fecha(31, 1, 2002), 0.10, 202, "ESPAÑOL");
    contratos[5] = new ContratoMovil(75547001, Fecha(31, 1, 2002), 0.15, 80, "DANES");
    contratos[6] = new ContratoTP(45999000, Fecha(1, 2, 2002), 400);
    this->nContratos = 7;
}

void Empresa::ver() const {
    cout << "--- Clientes: " << this->nClientes << endl;
    cout << "--- Contratos: " << this->nContratos << endl;
    // 1. Imprimir "La Empresa tiene X clientes y Y contratos"
    cout << "La Empresa tiene " << this->nClientes << " clientes y " << this->nContratos << " contratos" << endl;

    // 2. Imprimir "Clientes:" y un bucle 'for' que llama a 'cout << clientes[i]'
    cout << "Clientes:" << endl;
    for (int i = 0; i < this->nClientes; i++) {
        cout << this->clientes[i] << endl;
    }

    // 3. Imprimir "Contratos:" y un bucle 'for' que llama a 'cout << *contratos[i]'
    cout << "Contratos:" << endl;
    for (int i = 0; i < this->nContratos; i++) {
        // Llama al operator<<(Contrato) -> que llama a c.imprimir() (VIRTUAL)
        cout << *(this->contratos[i]) << endl;
    }
}

void Empresa::crearContrato() {
    long int dni;
    int dia, mes, anio;

    cout << "Introduzca dni: ";
    cin >> dni;

    int posCliente = this->buscarCliente(dni);

    // 3. Si no existe (-1)
    if (posCliente == -1) {
        // a. Comprobar si 'nClientes < 100'
        if (this->nClientes >= 100) {
            cout << "Error: Límite de clientes alcanzado." << endl;
            return;
        }

        // b. Pedir Nombre y Fecha
        char nombre[100];
        cout << "Nombre del cliente: ";
        cin.ignore(); // Limpia el buffer del 'cin' anterior
        cin.getline(nombre, 100);

        cout << "Fecha de alta (dd mm aaaa): ";
        cin >> dia >> mes >> anio;

        // c. Crear Cliente nuevo en 'clientes[nClientes]' y hacer nClientes++
        this->clientes[this->nClientes] = Cliente(dni, nombre, Fecha(dia, mes, anio));
        posCliente = this->nClientes; // La posición del nuevo cliente es la última
        this->nClientes++;

    }

    // 4. Si existe (o se acaba de crear)

    // a. Comprobar si 'nContratos == capContratos' y llamar a redimensionar() (si el array dinámico está lleno)
    if (this->nContratos == this->capContratos) {
        this->redimensionar();
    }

    // b. Pedir tipo (1-TP, 2-Movil)
    int tipo;
    cout << "Tipo de Contrato a abrir (1-Tarifa Plana, 2-Movil): ";
    cin >> tipo;

    // c. Pedir datos comunes (fecha)
    cout << "Fecha del contrato" << endl;
    cout << "dia: "; cin >> dia;
    cout << "mes: "; cin >> mes;
    cout << "anio: "; cin >> anio;
    Fecha fContrato(dia, mes, anio);

    // Crea el objeto Contrato (TP o Movil) con 'new''
    if (tipo == 1) {
        int min;
        cout << "minutos hablados: ";
        cin >> min;
        this->contratos[this->nContratos] = new ContratoTP(dni, fContrato, min);

    } else if (tipo == 2) {
        int min;
        float precio;
        char nac[100];
        cout << "minutos hablados: ";
        cin >> min;
        cout << "Precio minuto: ";
        cin >> precio;
        cout << "Nacionalidad: ";
        cin >> nac;
        this->contratos[this->nContratos] = new ContratoMovil(dni, fContrato, precio, min, nac);
    }

    // e. nContratos++
    this->nContratos++;
}

bool Empresa::cancelarContrato(int idContrato) {
    // 1. Llamar a buscarContrato(idContrato)
    int pos = this->buscarContrato(idContrato);

    // 2. Si no existe (-1)
    if (pos == -1) {
        // cout << "El Contrato ... no existe" (lo hace el main)
        return false;
    }

    // 3. Si existe (en la pos 'pos'):
    // a. 'delete contratos[pos];' (¡Libera la memoria!)
    delete this->contratos[pos];

    // b. Mover todos los punteros desde 'pos+1' para tapar el hueco
    for (int i = pos; i < this->nContratos - 1; i++) {
        this->contratos[i] = this->contratos[i + 1];
    }

    // c. 'nContratos--'
    this->nContratos--;

    // d. 'return true'
    return true;
}


bool Empresa::bajaCliente(long int dni) {
    // 1. Llamar a buscarCliente(dni)
    int posCliente = this->buscarCliente(dni);

    // 2. Si no existe (-1)
    if (posCliente == -1) {
        // cout << "El cliente ... no existe" (lo hace el main)
        return false;
    }

    // 3. Si existe (en la pos 'posCliente'):

    // a. Recorrer 'contratos' y eliminar los suyos
    // b. ¡OJO! Al borrar, el array se encoge. Hay que reajustar el 'for' (i--)
    for (int i = 0; i < this->nContratos; i++) {
        if (this->contratos[i]->getDniContrato() == dni) {
            cancelarContrato(this->contratos[i]->getIdContrato());
            i--; // Decrementa 'i' para volver a comprobar la posición actual
        }
    }
    /*
     Borrar de un array mientras se itera
      Recorremos el array y, si borramos un contrato,
      llamamos a cancelarContrato().
      cancelarContrato() encoge el array, así que tenemos
      que decrementar 'i' (i--) para volver a comprobar
      la posición actual (que ahora contiene un nuevo contrato).
     */

    // c. Borra al cliente del array 'clientes' (tapando el hueco)
    //    (Recuerda: aquí asignamos objetos, no punteros)
    for (int i = posCliente; i < this->nClientes - 1; i++) {
        this->clientes[i] = this->clientes[i + 1];
    }

    // d. 'nClientes--'
    this->nClientes--;

    // e. 'return true'
    return true;
}

/*'typeid'
  Comprobación de tipo EXACTA.
  Se usa para contar.
  Necesita <typeinfo>
  Se usa typeid(*puntero), con el asterisco.
 */
int Empresa::nContratosTP() const {
    int contador = 0;

    // 2. Bucle 'for' de 0 a 'nContratos'
    for (int i = 0; i < this->nContratos; i++) {
        // 3. 'if (typeid(*contratos[i]) == typeid(ContratoTP)) { contador++; }'
        if (typeid(*(this->contratos[i])) == typeid(ContratoTP)) {
            contador++;
        }
    }

    // 4. 'return contador;'
    return contador;
}

void Empresa::descuento(float porcentaje) {//Función implementada para el apartado 4

    // 1. Bucle 'for' de 0 a 'nContratos'
    for (int i = 0; i < this->nContratos; i++) {

        // 2. 'ContratoMovil* cm = dynamic_cast<ContratoMovil*>(contratos[i]);'
        // Intenta convertir Contrato* -> ContratoMovil*
        ContratoMovil* cm = dynamic_cast<ContratoMovil*>(this->contratos[i]);

        // 3. 'if (cm != NULL) { ... }' // Comprueba si la conversión tuvo éxito
        if (cm != NULL) {
            // a. 'float precioActual = cm->getPrecioMinuto();'
            float precioActual = cm->getPrecioMinuto();

            // b. 'cm->setPrecioMinuto(...)'
            cm->setPrecioMinuto(precioActual * (1.0 - (porcentaje / 100.0)));
        }
    }
}


void Empresa::mejorClienteContratoTP() const
{
    long int dni_maxtp=-1;
    int n_tp_max=0;


    for (int i=0; i<nClientes; i++)
    {

        long int dni_actual= clientes[i].getDni();

        int n_tp_actual= 0;
        for (int j=0; j<nContratos; j++)
        {

            if (dni_actual==contratos[j]->getDniContrato())
            {
                ContratoTP* ctp = dynamic_cast<ContratoTP*> (contratos[j]);
                if (ctp != NULL)
                    {
                        n_tp_actual++;

                    }
            }

        }
        if (n_tp_actual>=n_tp_max)
        {
            dni_maxtp=dni_actual;
            n_tp_max=n_tp_actual;
        }







    }

    cout<<"Dni del ganador: "<<dni_maxtp<<endl<<"Numero de contratos: "<<n_tp_max<<endl;


}




void Empresa::mejorClienteDeLaEmpresaMejorTotalDeFacturas()
{
    long int dni_max=-1;
    float max_total=0;


    for (int i=0; i<nClientes; i++)
    {
        float total_actual=0;

        long int dni_actual= clientes[i].getDni();

        for (int j=0; j<nContratos; j++)
        {

            if (dni_actual==contratos[j]->getDniContrato())
            {
                ContratoTP* ctp = dynamic_cast<ContratoTP*> (contratos[j]);
                if (ctp != NULL)
                    {
                        total_actual=total_actual+ctp->factura();


                    }
                else
                    {
                        ContratoMovil* cm =dynamic_cast <ContratoMovil*> (contratos[j]);
                        if (cm !=NULL)
                        {
                            total_actual=total_actual+cm->factura();

                        }
                    }

            }

        }
        if (max_total<=total_actual)
        {
            dni_max=dni_actual;
            max_total=total_actual;
        }








    }
    cout<<"Dni del ganador: "<<dni_max<<endl<<"Total gastado: "<<max_total<<endl;


}
