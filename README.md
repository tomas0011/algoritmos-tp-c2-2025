# algoritmos-tp-c2-2025

## Descripción

Este proyecto es una implementación en C++ de un sistema de gestión de envíos y logística. Forma parte del trabajo práctico C2 para la materia de Algoritmos en la Universidad Nacional de Hurlingham (UNAHUR).

El programa demuestra el uso de clases en C++ para modelar entidades como paquetes, envíos, empleados, centros de distribución, transportes, clientes, conexiones y gestores de envíos, con funcionalidades de visualización de datos mock a través de un menú interactivo.

<img width="1198" height="762" alt="image" src="https://github.com/user-attachments/assets/80745e64-49a1-42aa-b1f7-abc35e0d320f" />


## Características

- **Clase Package**: Representa un paquete con ID, precio, prioridad y peso.
- **Clase Shipment**: Representa un envío con ID, origen, destino, fecha y estado.
- **Clase ShipmentManager**: Representa un gestor de envíos con ID, nombre y especialidad.
- **Clase Transport**: Representa un transporte con ID, tipo, capacidad y estado.
- **Clase Client**: Representa un cliente con ID, nombre, dirección y teléfono.
- **Clase Connection**: Representa una conexión entre centros con ID, origen, destino y distancia.
- **Clase DistributionCenter**: Representa un centro de distribución con ID, nombre, ciudad, capacidad y paquetes diarios.
- **Clase Employee**: Representa a un empleado con ID, nombre y DNI.
- Menú interactivo para visualizar datos mock de todas las entidades.
- Funcionalidad de visualización para todas las clases.

## Estructura del Proyecto

```
algoritmos-tp-c2-2025/
├── main.cpp                          # Punto de entrada del programa
├── Makefile                          # Archivo de construcción
├── bash/
│   ├── bash.h                        # Declaración del menú interactivo
│   └── bash.cpp                      # Implementación del menú interactivo
├── mocks/
│   ├── mockData.h                    # Declaración de datos mock
│   └── mockData.cpp                  # Implementación de datos mock
├── entities/
│   ├── client/
│   │   ├── Client.h                  # Declaración de la clase Client
│   │   └── Client.cpp                # Implementación de la clase Client
│   ├── connection/
│   │   ├── Connection.h              # Declaración de la clase Connection
│   │   └── Connection.cpp            # Implementación de la clase Connection
│   ├── distributionCenter/
│   │   ├── DistributionCenter.h      # Declaración de la clase DistributionCenter
│   │   └── DistributionCenter.cpp    # Implementación de la clase DistributionCenter
│   ├── employee/
│   │   ├── Employee.h                # Declaración de la clase Employee
│   │   └── Employee.cpp              # Implementación de la clase Employee
│   ├── package/
│   │   ├── Package.h                 # Declaración de la clase Package
│   │   └── Package.cpp               # Implementación de la clase Package
│   ├── shipment/
│   │   ├── Shipment.h                # Declaración de la clase Shipment
│   │   └── Shipment.cpp              # Implementación de la clase Shipment
│   ├── shipmentManager/
│   │   ├── ShipmentManager.h         # Declaración de la clase ShipmentManager
│   │   └── ShipmentManager.cpp       # Implementación de la clase ShipmentManager
│   └── transport/
│       ├── Transport.h               # Declaración de la clase Transport
│       └── Transport.cpp             # Implementación de la clase Transport
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

El programa presenta un menú interactivo que permite al usuario seleccionar y visualizar datos mock de diferentes entidades del sistema de logística.

Opciones del menú:
1. Listar Paquetes
2. Listar Envíos
3. Listar Gestores de Envíos
4. Listar Transportes
5. Listar Clientes
6. Listar Conexiones
7. Listar Centros de Distribución
8. Listar Empleados
0. Salir

Ejemplo de salida para un paquete:
```
ID: 1, Price: 25.50, Priority: 1, Weight: 2.5
```

## Autor

Proyecto desarrollado como parte del curso de Algoritmos en UNAHUR.

## Licencia

Este proyecto es de uso educativo y no tiene una licencia específica.
