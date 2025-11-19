# algoritmos-tp-c2-2025

## Descripción

Este proyecto es una implementación completa en C++ de un sistema de gestión de envíos y logística para la Universidad Nacional de Hurlingham (UNAHUR). Forma parte del trabajo práctico C2 de la materia Algoritmos y cumple con todos los requisitos del enunciado.

El sistema implementa un modelo completo de dominio logístico con entidades interconectadas, utilizando estructuras de datos personalizadas desarrolladas desde cero. Incluye servicios CRUD completos, algoritmos avanzados de optimización (Dijkstra, Knapsack), y una interfaz de usuario interactiva que permite tanto la gestión operativa como la resolución de ejercicios específicos del TP.

**Características destacadas:**
- Arquitectura modular en capas con separación clara de responsabilidades
- Implementación de algoritmos de grafos para rutas óptimas
- Sistema de optimización de carga usando backtracking
- Análisis de sobrecarga de centros de distribución
- Interfaz de menú jerárquica para navegación intuitiva

<img width="1198" height="762" alt="image" src="https://github.com/user-attachments/assets/80745e64-49a1-42aa-b1f7-abc35e0d320f" />


## Características

### Entidades del Dominio
- **Package**: Representa un paquete con ID, precio, prioridad y peso
- **Shipment**: Representa un envío con ID, estado, costo, prioridad, fechas y lista de paquetes
- **ShipmentManager**: Gestiona envíos con ID, transporte asignado y ruta
- **Transport**: Representa medios de transporte con ID, tipo y capacidad máxima
- **Client**: Representa clientes con ID y nombre
- **Connection**: Representa conexiones entre centros de distribución con distancia
- **DistributionCenter**: Centros de distribución con empleados, conexiones y warehouse
- **Employee**: Empleados asignados a centros de distribución
- **DistributionCenterManager**: Gestiona múltiples centros de distribución

### Arquitectura del Sistema
- **Estructuras de Datos Personalizadas**: Implementación propia de clases `List`, `Graph`, `HashTable`, `Tree` usando `std::any` para almacenamiento genérico
- **Almacenamiento Centralizado**: Módulo `storage/` con listas globales para todas las entidades
- **Capa de Servicios**: Servicios CRUD completos para todas las entidades (PackageService, ShipmentService, ClientService, etc.)
- **Algoritmos Avanzados**: Dijkstra para rutas óptimas, Knapsack para optimización de carga, MergeSort para ordenamiento
- **Inicialización Centralizada**: Módulo `initializeServices/` para configuración de servicios
- **Interfaz de Usuario**: Menú interactivo en consola con submenús para gestión y ejercicios del TP

## Arquitectura y Estructura del Proyecto

### Capas de la Arquitectura

El proyecto sigue una arquitectura en capas clara y modular:

1. **Capa de Dominio** (`entities/`): Clases que representan las entidades del negocio
2. **Capa de Datos** (`storage/`): Almacenamiento centralizado usando estructuras de datos personalizadas
3. **Capa de Servicios** (`services/`): Lógica de negocio y operaciones CRUD
4. **Capa de Presentación** (`bash/`): Interfaz de usuario y menú interactivo
5. **Capa de Utilidades** (`utils/`): Estructuras de datos y algoritmos reutilizables

### Estructura Detallada del Proyecto

```
algoritmos-tp-c2-2025/
├── main.cpp                          # Punto de entrada - inicializa servicios y lanza menú
├── Makefile                          # Sistema de construcción (compilación C++17)
├── bash/
│   ├── bash.h                        # Declaración de la interfaz de menú principal
│   ├── bash.cpp                      # Implementación del menú interactivo con submenús
│   ├── client.bash.h                 # Menú para gestión de clientes
│   ├── client.bash.cpp
│   ├── connection.bash.h             # Menú para gestión de conexiones
│   ├── connection.bash.cpp
│   ├── distributionCenter.bash.h     # Menú para gestión de centros de distribución
│   ├── distributionCenter.bash.cpp
│   ├── employee.bash.h               # Menú para gestión de empleados
│   ├── employee.bash.cpp
│   ├── package.bash.h                # Menú para gestión de paquetes
│   ├── package.bash.cpp
│   ├── shipment.bash.h               # Menú para gestión de envíos
│   ├── shipment.bash.cpp
│   └── transport.bash.h              # Menú para gestión de transportes
│   └── transport.bash.cpp
├── storage/
│   ├── storage.h                     # Declaración de listas globales para todas las entidades
│   ├── storage.cpp                   # Instanciación de listas globales
│   ├── mockData.h                    # Declaración de funciones de datos de prueba
│   └── mockData.cpp                  # Implementación de datos mock y funciones de display
├── services/
│   ├── initializeServices.h          # Declaración de inicialización de servicios
│   ├── initializeServices.cpp        # Inicialización centralizada de servicios
│   ├── client/
│   │   ├── clientService.h           # Servicio CRUD para clientes
│   │   └── clientService.cpp
│   ├── Connection/
│   │   ├── ConnectionService.h       # Servicio CRUD para conexiones
│   │   └── ConnectionService.cpp
│   ├── distributionCenter/
│   │   ├── distributionCenterService.h # Servicio CRUD para centros de distribución
│   │   └── distributionCenterService.cpp
│   ├── employee/
│   │   ├── employeeService.h         # Servicio CRUD para empleados
│   │   └── employeeService.cpp
│   ├── package/
│   │   ├── packageService.h          # Servicio CRUD para paquetes
│   │   └── packageService.cpp
│   ├── shipment/
│   │   ├── shipmentService.h         # Servicio CRUD para envíos
│   │   └── shipmentService.cpp
│   └── transport/
│       ├── transportService.h        # Servicio CRUD para transportes
│       └── transportService.cpp
├── entities/                         # Capa de dominio - entidades del negocio
│   ├── client/
│   │   ├── Client.h                  # Cliente (ID, nombre)
│   │   └── Client.cpp
│   ├── connection/
│   │   ├── Connection.h              # Conexión entre centros (ID, origen, destino, distancia)
│   │   └── Connection.cpp
│   ├── distributionCenter/
│   │   ├── DistributionCenter.h      # Centro de distribución (ID, nombre, ciudad, empleados, conexiones, warehouse)
│   │   └── DistributionCenter.cpp
│   ├── distributionCenterManager/
│   │   ├── DistributionCenterManager.h # Gestor de centros de distribución
│   │   └── DistributionCenterManager.cpp
│   ├── employee/
│   │   ├── Employee.h                # Empleado (ID, nombre, centro asignado)
│   │   └── Employee.cpp
│   ├── package/
│   │   ├── Package.h                 # Paquete (ID, precio, prioridad, peso)
│   │   └── Package.cpp
│   ├── shipment/
│   │   ├── Shipment.h                # Envío (ID, estado, costo, paquetes, fechas)
│   │   └── Shipment.cpp
│   ├── shipmentManager/
│   │   ├── ShipmentManager.h         # Gestor de envíos (ID, transporte, ruta)
│   │   └── ShipmentManager.cpp
│   └── transport/
│       ├── Transport.h               # Transporte (ID, tipo, capacidad máxima)
│       └── Transport.cpp
├── utils/
│   ├── algorithms/
│   │   ├── dijkstra/
│   │   │   ├── dijkstra.h            # Algoritmo de Dijkstra para rutas óptimas
│   │   │   ├── dijkstra.cpp
│   │   │   └── dijkstraTest.cpp      # Tests del algoritmo
│   │   ├── knapsackProblem/
│   │   │   ├── knapsack.h            # Problema de la mochila para optimización
│   │   │   ├── knapsack.cpp
│   │   │   └── knapsackTest.cpp      # Tests del algoritmo
│   │   ├── parseDate/
│   │   │   ├── parseDate.h           # Utilidades para parsing de fechas
│   │   │   └── parseDate.cpp
│   │   └── sort/
│   │       ├── mergeSort.h           # Algoritmo de ordenamiento MergeSort
│   │       ├── mergeSort.cpp
│   │       └── mergeSortTest.cpp     # Tests del algoritmo
│   └── dataStructures/
│       ├── graph/
│       │   ├── Graph.h               # Implementación de grafo para redes
│       │   └── GraphHashTable.h      # Tabla hash para grafos
│       ├── hashtable/
│       │   ├── HashTable.h           # Implementación de tabla hash
│       │   └── hashTableTest.cpp     # Tests de la estructura
│       ├── list/
│       │   ├── List.h                # Implementación propia de lista enlazada con std::any
│       │   └── listTest.cpp          # Tests de la estructura de datos
│       └── tree/
│           ├── Tree.h                # Implementación de árbol
│           └── treeTest.cpp          # Tests del árbol
├── .gitignore                        # Archivos ignorados por Git
└── README.md                         # Documentación del proyecto
```

### Responsabilidades por Módulo

#### `main.cpp`
- Punto de entrada del programa
- Inicialización de servicios a través de `initializeServices()`
- Lanzamiento del menú interactivo

#### `storage/`
- **storage.h/cpp**: Declaración e instanciación de listas globales para todas las entidades
- **mockData.h/cpp**: Datos de prueba y funciones de visualización básicas

#### `services/`
- **initializeServices.h/cpp**: Inicialización centralizada de todos los servicios
- **clientService.h/cpp**: Operaciones CRUD para clientes
- **ConnectionService.h/cpp**: Operaciones CRUD para conexiones entre centros
- **distributionCenterService.h/cpp**: Operaciones CRUD para centros de distribución
- **employeeService.h/cpp**: Operaciones CRUD para empleados
- **packageService.h/cpp**: Operaciones CRUD para paquetes
- **shipmentService.h/cpp**: Operaciones CRUD para envíos
- **transportService.h/cpp**: Operaciones CRUD para transportes

#### `entities/`
- Definición de clases que representan las entidades del dominio de logística
- Cada entidad tiene su propio directorio con archivos `.h` y `.cpp`

#### `bash/`
- Interfaz de usuario basada en consola
- Menú interactivo que consume servicios para mostrar datos

#### `utils/`
- **dataStructures/**: Estructuras de datos personalizadas (`List`, `Graph`, `HashTable`, `Tree`)
- **algorithms/**: Algoritmos avanzados (`Dijkstra`, `Knapsack`, `MergeSort`, `parseDate`)

## Requisitos del Sistema

- **Compilador**: C++ compatible con C++17 (g++ recomendado)
- **Sistema Operativo**: Linux
- **Dependencias**: Ninguna externa (usa solo STL de C++)

## Construcción y Ejecución

### Compilación y Ejecución Rápida

```bash
make clean && make && ./tp_c2_2025
```

### Comandos de Makefile

- `make`: Compila el proyecto completo generando el ejecutable `tp_c2_2025`
- `make clean`: Elimina el ejecutable y archivos objeto generados

### Proceso de Compilación

El proyecto se compila con flags C++17 para soporte de `std::any` usado en la clase `List`. El Makefile incluye todos los archivos fuente necesarios organizados por módulos.

## Uso del Programa

### Menú Interactivo

El programa presenta un menú interactivo en consola con dos secciones principales: Sistema de Gestión y Ejercicios del TP.

#### Menú Principal
1. **Sistema de Gestión** - Acceso a CRUD de todas las entidades
2. **Ejercicios del TP** - Funcionalidades específicas del trabajo práctico
0. **Salir**

#### Menú Sistema de Gestión
1. **Paquetes** - Gestión completa de paquetes
2. **Envíos** - Gestión completa de envíos
3. **Transportes** - Gestión completa de transportes
4. **Clientes** - Gestión completa de clientes
5. **Conexiones** - Gestión completa de conexiones
6. **Centros de Distribución** - Gestión completa de centros
7. **Empleados** - Gestión completa de empleados
0. **Salir**

#### Menú Ejercicios del TP
1. **Gestión de Centros (Ejercicio A)** - Operaciones específicas de centros
2. **Análisis de Envíos (Ejercicio B)** - Análisis y estadísticas de envíos
3. **Optimización con Backtracking (Ejercicio C)** - Algoritmos de optimización
0. **Salir**

### Ejemplo de Salida

```
=== Menu de Entidades ===
1. Listar Paquetes
2. Listar Envios
...
Seleccione una opcion: 1

All Packages:
ID: 1, Price: 10.5, Priority: 1, Weight: 2.0
ID: 2, Price: 15.0, Priority: 2, Weight: 3.5
...
```

## Servicios Disponibles

Todos los servicios implementan operaciones CRUD completas y utilizan la estructura de datos `List` personalizada para almacenamiento.

### PackageService
- `createPackage(id, price, priority, weight)`: Crear nuevo paquete
- `getPackageById(id)`: Obtener paquete por ID
- `updatePackage(id, price, priority, weight)`: Actualizar paquete existente
- `deletePackage(id)`: Eliminar paquete
- `displayAllPackages()`: Mostrar todos los paquetes

### ShipmentService
- `createShipment(...)`: Crear nuevo envío con todos sus parámetros
- `getShipmentById(id)`: Obtener envío por ID
- `updateShipment(...)`: Actualizar envío existente
- `deleteShipment(id)`: Eliminar envío
- `displayAllShipments()`: Mostrar todos los envíos
- `overloadedCenters()`: Identificar centros sobrecargados
- `findShipmentsByClient(clientId)`: Buscar envíos por cliente
- `generateOptimalCargoForTransport(...)`: Optimización de carga (Ejercicio C)

### ClientService
- Operaciones CRUD completas para gestión de clientes

### TransportService
- Operaciones CRUD completas para gestión de transportes

### ConnectionService
- Operaciones CRUD completas para gestión de conexiones entre centros

### DistributionCenterService
- Operaciones CRUD completas para gestión de centros de distribución
- `getCenter(code)`: Obtener centro por código
- `addConnection(...)`: Agregar conexiones entre centros
- `calculateShortestPath(...)`: Calcular rutas óptimas usando Dijkstra
- `displayCentersSortedByCapacity()`: Ordenar centros por capacidad

### EmployeeService
- Operaciones CRUD completas para gestión de empleados

## Desarrollo y Contribución

### Estándares de Código

- **Lenguaje**: C++17 con STL moderna
- **Estilo**: Código limpio, bien documentado con comentarios
- **Convenciones**: Nombres descriptivos, funciones cohesivas
- **Compilación**: Estricto cumplimiento de estándares C++17

### Arquitectura y Patrones

- **Separación de Responsabilidades**: Cada módulo tiene una responsabilidad clara
- **Inyección de Dependencias**: Servicios reciben referencias a almacenamiento
- **Almacenamiento Centralizado**: Listas globales para evitar duplicación
- **Interfaz Consistente**: Servicios siguen patrón CRUD uniforme

### Guía para Contribuidores

#### Agregar una Nueva Entidad

1. **Crear la clase entidad** en `entities/nuevaEntidad/`
   - `NuevaEntidad.h`: Declaración con getters y display()
   - `NuevaEntidad.cpp`: Implementación de métodos

2. **Agregar al almacenamiento**:
   - Declarar lista en `storage/storage.h`
   - Instanciar en `storage/storage.cpp`

3. **Crear datos mock**:
   - Agregar instancias en `storage/mockData.cpp`
   - Implementar función display en `storage/mockData.cpp`

4. **Crear servicio (opcional)**:
   - `services/nuevaEntidad/nuevaEntidadService.h`
   - `services/nuevaEntidad/nuevaEntidadService.cpp`
   - Agregar al `initializeServices.h/cpp`

5. **Actualizar interfaz**:
   - Agregar opción al menú en `bash/bash.cpp`
   - Actualizar `Makefile` con nuevos archivos

#### Extensiones Sugeridas

- **Validación de datos** en servicios
- **Persistencia** (archivos, base de datos)
- **Interfaz gráfica** (Qt, GTK)
- **Tests unitarios** más completos
- **Documentación API** con Doxygen
- **API REST** para acceso remoto
- **Base de datos** para almacenamiento persistente

### Estructura de Commits

```
feat: add PackageService with CRUD operations
refactor: migrate storage from vectors to custom List
docs: update README with architecture details
```

## Autor

Proyecto desarrollado como parte del curso de Algoritmos en la Universidad Nacional de Hurlingham (UNAHUR).

## Licencia

Este proyecto es de uso educativo y no tiene una licencia específica.
