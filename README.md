# Sistema de Gestión de Telecomunicaciones (C++)

Este repositorio contiene el código fuente de un sistema completo de facturación y gestión de clientes diseñado para una empresa de telefonía móvil. El proyecto está desarrollado íntegramente en C++, con su versión equivalente en java y tiene como objetivo demostrar el dominio de la Programación Orientada a Objetos (POO), la gestión eficiente de la memoria y el diseño de arquitecturas modulares.

## 🚀 Características Técnicas Destacadas

Este proyecto no utiliza frameworks externos, basando toda su lógica en las capacidades estándar de C++ y aplicando buenas prácticas de ingeniería de software:

*   **Gestión Dinámica de Memoria:** El motor principal de la aplicación (`Empresa`) maneja un volumen ilimitado de contratos mediante la implementación manual de arrays dinámicos. El sistema detecta cuándo se agota la capacidad y redimensiona automáticamente la memoria reservada (duplicando el tamaño: 10, 20, 40...) para optimizar el rendimiento y evitar fugas de memoria.
*   **Arquitectura Modular:** Código estrictamente dividido en ficheros de cabecera (`.h`) y de implementación (`.cpp`) para facilitar la escalabilidad, la mantenibilidad y la compilación separada.
*   **Polimorfismo y Clases Abstractas:** Diseño basado en una jerarquía de herencia donde `Contrato` actúa como una clase base abstracta. Las llamadas a los métodos de facturación se resuelven dinámicamente en tiempo de ejecución.
*   **RTTI (Run-Time Type Information):** Uso de conversiones seguras e identificación de tipos en tiempo de ejecución mediante `dynamic_cast<>` y `typeid` para aplicar reglas de negocio específicas (ej. descuentos) sin romper el encapsulamiento de la clase base.
*   **Manejo de Punteros y Cadenas a Bajo Nivel:** Gestión manual de la información de los clientes mediante punteros a caracteres (`char *`), evitando el uso de la clase `std::string` estándar para demostrar un control estricto sobre las asignaciones de memoria.

## 🏗️ Estructura del Sistema

La arquitectura de la aplicación se divide en las siguientes entidades principales:

*   **`Empresa`**: La clase gestora central. Administra el alta/baja de clientes (array estático controlado) y la creación/cancelación de contratos (array dinámico auto-escalable).
*   **`Cliente` y `Fecha`**: Entidades base que encapsulan la identidad de los usuarios (DNI, Nombre) y el control temporal de las operaciones del sistema.
*   **`Contrato`**: Clase abstracta que define la interfaz común y garantiza la generación automática de IDs únicos en el sistema para evitar colisiones de datos.
*   **`ContratoTP` (Tarifa Plana)**: Hereda de `Contrato`. Implementa la lógica de facturación con límite de minutos y penalizaciones por exceso. Está diseñado para reflejar actualizaciones de tarifas a todos los clientes de forma global.
*   **`ContratoMovil` (Pago por uso)**: Hereda de `Contrato`. Calcula el coste en función del consumo exacto, soportando tarifas personalizadas por cliente.

## 💻 Entorno y Compilación

El proyecto está preparado para ser compilado mediante `g++` o cualquier compilador estándar de C++. 

Para compilar el proyecto de forma manual desde la terminal:
```bash
g++ -o gestion_telecom Empresa.cpp Cliente.cpp Fecha.cpp Contrato.cpp ContratoTP.cpp ContratoMovil.cpp main.cpp
./gestion_telecom
