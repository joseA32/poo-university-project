#ifndef EMPRESA_H
#define EMPRESA_H

#include "Fecha.h"
#include "Cliente.h"
#include "Contrato.h"
#include "ContratoTP.h"      // Los incluimos porque los crearemos en el .cpp
#include "ContratoMovil.h" // (Aunque bastaría con incluirlos en el .cpp)
#include <iostream>
#include <typeinfo> // Para typeid y dynamic_cast

using namespace std;

class Empresa {
private:
    // --- Array estático de Clientes ---
    Cliente clientes[100]; // Array de tamaño fijo
    int nClientes;         // Contador de cuántos clientes tenemos

    // --- Array dinámico de Contratos ---
    Contrato** contratos;  // Puntero a un array de punteros
    int nContratos;        // Contador de cuántos contratos tenemos
    int capContratos;      // Capacidad actual del array de contratos

    // --- Métodos privados (ayudantes) ---
    void redimensionar();             // Para duplicar el array de contratos
    int buscarCliente(long int dni);  // Devuelve la posición del cliente, o -1
    int buscarContrato(int id);       // Devuelve la posición del contrato, o -1

public:
    // === Constructores y Destructor ===
    Empresa();  // Constructor (lo llama "Empresa Yoigo;")

    Empresa(const Empresa& otra); //ctor copia
    ~Empresa(); // Destructor (necesario para borrar los new de contratos)



    // (La práctica dice que no implementemos el de copia ni el = )

    // Métodos principales
    void cargarDatos(); //usado en el main
    void ver() const;   //usado en el main

    int nContratosTP() const; // (Paso 4, usa typeid)
    void descuento(float porcentaje); // (Paso 4, usa dynamic_cast)

    void crearContrato(); // (Paso 3)
    bool cancelarContrato(int idContrato); // (Paso 3)
    bool bajaCliente(long int dni); // (Paso 3)
    void mejorClienteContratoTP() const;
    void mejorClienteDeLaEmpresaMejorTotalDeFacturas ();
};

#endif // EMPRESA_H
