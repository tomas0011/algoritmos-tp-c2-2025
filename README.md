# algoritmos-tp-c2-2025

## Descripción

Este proyecto es una implementación en C++ de un sistema de gestión de envíos y logística. Forma parte del trabajo práctico C2 para la materia de Algoritmos en la Universidad Nacional de Hurlingham (UNAHUR).

El programa demuestra el uso de estructuras de datos personalizadas (como la clase `List` implementada por nosotros) y patrones de diseño para modelar entidades del dominio de logística. Incluye un sistema de almacenamiento centralizado, servicios CRUD para operaciones de negocio, y una interfaz de menú interactivo para la visualización de datos.

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
- **Estructuras de Datos Personalizadas**: 
  - `List`: Lista enlazada con `std::any` para almacenamiento genérico
  - `HashTable`: Tabla hash con función Folding + División y sondeo lineal
  - `Tree`: Árbol binario genérico
- **Almacenamiento Centralizado**: Módulo `storage/` con listas globales para todas las entidades
- **Capa de Servicios**: Servicios CRUD para operaciones de negocio (PackageService, ShipmentService)
- **Inicialización Centralizada**: Módulo `initializeServices/` para configuración de servicios
- **Interfaz de Usuario**: Menú interactivo en consola para visualización de datos

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
│   ├── bash.h                        # Declaración de la interfaz de menú
│   └── bash.cpp                      # Implementación del menú interactivo
├── storage/
│   ├── storage.h                     # Declaración de listas globales para todas las entidades
│   ├── storage.cpp                   # Instanciación de listas globales
│   ├── mockData.h                    # Declaración de funciones de datos de prueba
│   └── mockData.cpp                  # Implementación de datos mock y funciones de display
├── services/
│   ├── initializeServices.h          # Declaración de inicialización de servicios
│   ├── initializeServices.cpp        # Inicialización centralizada de servicios
│   ├── package/
│   │   ├── packageService.h          # Servicio CRUD para paquetes
│   │   └── packageService.cpp        # Implementación de operaciones de paquete
│   └── shipment/
│       ├── shipmentService.h         # Servicio CRUD para envíos
│       └── shipmentService.cpp       # Implementación de operaciones de envío
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
│   │   └── sort/
│   │       ├── mergeSort.cpp         # Algoritmo de ordenamiento
│   │       └── mergeSortTest.cpp     # Tests del algoritmo
│   └── dataStructures/
│       ├── hashtable/
│       │   ├── HashTable.h           # Implementación propia de tabla hash
│       │   └── hashTableTest.cpp     # Tests de la tabla hash
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
- **packageService.h/cpp**: Operaciones CRUD para paquetes (crear, leer, actualizar, eliminar)
- **shipmentService.h/cpp**: Operaciones CRUD para envíos

#### `entities/`
- Definición de clases que representan las entidades del dominio de logística
- Cada entidad tiene su propio directorio con archivos `.h` y `.cpp`

#### `bash/`
- Interfaz de usuario basada en consola
- Menú interactivo que consume servicios para mostrar datos

#### `utils/`
- **dataStructures/**: Estructuras de datos personalizadas
  - `HashTable` - Tabla hash con función Folding + División y sondeo lineal
  - `List` - Lista enlazada genérica con `std::any`
  - `Tree` - Árbol binario genérico
- **algorithms/**: Algoritmos reutilizables (`mergeSort`)

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

El programa presenta un menú interactivo en consola que permite visualizar datos de prueba de todas las entidades del sistema.

**Opciones disponibles:**
1. **Listar Paquetes** - Muestra todos los paquetes usando `PackageService`
2. **Listar Envíos** - Muestra todos los envíos usando `ShipmentService`
3. **Listar Gestores de Envíos** - Visualización básica de gestores
4. **Listar Transportes** - Visualización básica de transportes
5. **Listar Clientes** - Visualización básica de clientes
6. **Listar Conexiones** - Visualización básica de conexiones
7. **Listar Centros de Distribución** - Visualización básica de centros
8. **Listar Empleados** - Visualización básica de empleados
9. **Listar Gestores de Centros** - Visualización básica de gestores de centros
0. **Salir** - Termina la ejecución

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

Los servicios usan la estructura de datos `List` personalizada para almacenamiento y operaciones CRUD.

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

- **Servicios CRUD** para todas las entidades (ClientService, TransportService, etc.)
- **Validación de datos** en servicios
- **Persistencia** (archivos, base de datos)
- **Algoritmos de optimización** para rutas de envío
- **Interfaz gráfica** (Qt, GTK)
- **Tests unitarios** más completos
- **Documentación API** con Doxygen

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
