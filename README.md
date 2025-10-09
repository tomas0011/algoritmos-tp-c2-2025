# algoritmos-tp-c2-2025

## Descripción

Este proyecto es una implementación en C++ de un sistema básico de gestión de empleados y centros de distribución. Forma parte del trabajo práctico C2 para la materia de Algoritmos en la Universidad Nacional de Hurlingham (UNAHUR).

El programa demuestra el uso de clases en C++ para modelar entidades como empleados y centros de distribución, con funcionalidades básicas de creación y visualización de objetos.

## Características

- **Clase Employee**: Representa a un empleado con ID, nombre y DNI.
- **Clase DistributionCenter**: Representa un centro de distribución con ID, nombre, ciudad, capacidad y paquetes diarios.
- Funcionalidad de visualización para ambas clases.

## Estructura del Proyecto

```
algoritmos-tp-c2-2025/
├── main.cpp                          # Punto de entrada del programa
├── Makefile                          # Archivo de construcción
├── entities/
│   ├── employee/
│   │   ├── Employee.h                # Declaración de la clase Employee
│   │   └── Employee.cpp              # Implementación de la clase Employee
│   └── distributionCenter/
│       ├── DistributionCenter.h      # Declaración de la clase DistributionCenter
│       └── DistributionCenter.cpp    # Implementación de la clase DistributionCenter
├── .gitignore                        # Archivos ignorados por Git
└── README.md                         # Este archivo
```

## Requisitos

- Compilador C++ compatible con C++11 (ej. g++)
- Sistema operativo Linux

## Construcción y Ejecución

### Para probar el programa

```bash
make clean && make && ./tp_c2_2025
```

### Comandos de Makefile

- `make`: Compila el proyecto y genera el ejecutable `tp_c2_2025`
- `make clean`: Elimina el ejecutable generado

## Uso

El programa principal crea instancias de Employee y DistributionCenter, y muestra sus detalles en la consola.

Ejemplo de salida:
```
ID: 1, Name: Tomas Vasquez, DNI: 123456
ID: 1, Name: Correo Argentino - Pedro diaz, City: Tesei, Capacity: 100, DalyPackages: 5
```

## Autor

Proyecto desarrollado como parte del curso de Algoritmos en UNAHUR.

## Licencia

Este proyecto es de uso educativo y no tiene una licencia específica.
AA