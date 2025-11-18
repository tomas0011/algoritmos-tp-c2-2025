#include <iostream>
#include "HashTable.h"
#include "../list/List.h"

using namespace std;

// =======================================================
// Estructuras de Datos del Dominio
// =======================================================

struct DistributionCenter {
    string code;
    string name;
    string city;
    int capacity;
    int dailyPackages;
    int employees;
    
    DistributionCenter(string c, string n, string ci, int cap, int dp, int emp)
        : code(c), name(n), city(ci), capacity(cap), dailyPackages(dp), employees(emp) {}
    
    string toString() const {
        return code + " | " + name + " | " + city + 
               " | Cap:" + to_string(capacity) + 
               " | Paq:" + to_string(dailyPackages) + 
               " | Emp:" + to_string(employees);
    }
};

struct Shipment {
    string centerCode;
    int packageId;
    int clientId;
    string date;
    double weight;
    
    Shipment(string cc, int pid, int cid, string d, double w)
        : centerCode(cc), packageId(pid), clientId(cid), date(d), weight(w) {}
    
    string toString() const {
        return "Paquete #" + to_string(packageId) + 
               " | Cliente:" + to_string(clientId) + 
               " | Fecha:" + date + 
               " | Peso:" + to_string(weight) + "kg" +
               " | Centro:" + centerCode;
    }
};

struct Connection {
    string origin;
    string destination;
    int distance;
    
    Connection(string o, string d, int dist)
        : origin(o), destination(d), distance(dist) {}
    
    string toString() const {
        return origin + " -> " + destination + " (" + to_string(distance) + " km)";
    }
};

// =======================================================
// Tests del Sistema de Distribucion
// =======================================================

void testDistributionCenters() {
    cout << "\n=== Test 1: Gestion de Centros de Distribucion ===" << endl;
    cout << "Simulando archivo centros.txt" << endl;
    
    // HashTable para almacenar centros por codigo (búsqueda O(1))
    HashTable centers(23);  // Número primo para mejor distribucion
    
    // Crear centros de distribucion
    DistributionCenter* cba = new DistributionCenter("CBA", "CentroCordoba", "Cordoba", 5000, 2000, 120);
    DistributionCenter* mza = new DistributionCenter("MZA", "CentroMendoza", "Mendoza", 3000, 1200, 80);
    DistributionCenter* bue = new DistributionCenter("BUE", "CentroBuenosAires", "Buenos Aires", 8000, 5000, 200);
    DistributionCenter* ros = new DistributionCenter("ROS", "CentroRosario", "Rosario", 4000, 1800, 100);
    DistributionCenter* tuc = new DistributionCenter("TUC", "CentroTucuman", "Tucuman", 2500, 900, 60);
    
    // Insertar en la HashTable usando codigo como clave
    centers.insert("CBA", cba);
    centers.insert("MZA", mza);
    centers.insert("BUE", bue);
    centers.insert("ROS", ros);
    centers.insert("TUC", tuc);
    
    cout << "\n Centros cargados: " << centers.getSize() << endl;
    
    // Búsqueda rapida O(1) por codigo
    cout << "\n--- Búsqueda de Centro por Codigo ---" << endl;
    string searchCode = "CBA";
    if (centers.contains(searchCode)) {
        DistributionCenter* found = any_cast<DistributionCenter*>(centers.search(searchCode));
        cout << "Centro encontrado: " << found->toString() << endl;
    }
    
    // Mostrar todos los centros
    cout << "\n--- Todos los Centros ---" << endl;
    List allCodes = centers.getKeys();
    Node* current = allCodes.getHead();
    while (current != nullptr) {
        string code = any_cast<string>(current->getData());
        DistributionCenter* center = any_cast<DistributionCenter*>(centers.search(code));
        cout << center->toString() << endl;
        current = current->getNext();
    }
    
    cout << "\n Ventaja de HashTable: Búsqueda O(1) vs O(n) en lista" << endl;
    
    // Limpiar memoria
    delete cba;
    delete mza;
    delete bue;
    delete ros;
    delete tuc;
}

void testShipmentManagement() {
    cout << "\n=== Test 2: Gestion de Envios por Centro ===" << endl;
    cout << "Simulando archivo envios.txt" << endl;
    
    // HashTable: codigo_centro -> Lista de envios
    HashTable shipmentsByCenter(23);
    
    // Crear listas de envios para cada centro
    List* shipmentsCBA = new List();
    List* shipmentsMZA = new List();
    List* shipmentsBUE = new List();
    
    // Agregar envios a CBA
    shipmentsCBA->push(new Shipment("CBA", 1245, 302, "20250412", 3.5));
    shipmentsCBA->push(new Shipment("CBA", 1246, 305, "20250412", 2.1));
    shipmentsCBA->push(new Shipment("CBA", 1247, 310, "20250413", 5.0));
    
    // Agregar envios a MZA
    shipmentsMZA->push(new Shipment("MZA", 1250, 411, "20250215", 2.0));
    shipmentsMZA->push(new Shipment("MZA", 1251, 415, "20250215", 1.5));
    
    // Agregar envios a BUE
    shipmentsBUE->push(new Shipment("BUE", 2001, 501, "20250410", 4.2));
    shipmentsBUE->push(new Shipment("BUE", 2002, 502, "20250410", 3.8));
    shipmentsBUE->push(new Shipment("BUE", 2003, 503, "20250411", 2.9));
    shipmentsBUE->push(new Shipment("BUE", 2004, 504, "20250411", 6.1));
    
    // Almacenar en HashTable
    shipmentsByCenter.insert("CBA", shipmentsCBA);
    shipmentsByCenter.insert("MZA", shipmentsMZA);
    shipmentsByCenter.insert("BUE", shipmentsBUE);
    
    cout << "\n Envios organizados por centro" << endl;
    
    // Consultar envios de un centro especifico
    cout << "\n--- Envios del Centro CBA ---" << endl;
    if (shipmentsByCenter.contains("CBA")) {
        List* shipments = any_cast<List*>(shipmentsByCenter.search("CBA"));
        Node* current = shipments->getHead();
        int count = 0;
        while (current != nullptr) {
            Shipment* s = any_cast<Shipment*>(current->getData());
            cout << "  " << s->toString() << endl;
            current = current->getNext();
            count++;
        }
        cout << "Total: " << count << " envios" << endl;
    }
    
    // Consultar envios de BUE
    cout << "\n--- Envios del Centro BUE ---" << endl;
    if (shipmentsByCenter.contains("BUE")) {
        List* shipments = any_cast<List*>(shipmentsByCenter.search("BUE"));
        cout << "Total: " << shipments->getSize() << " envios" << endl;
    }
    
    cout << "\n Acceso O(1) a envios por centro usando HashTable" << endl;
    
    // Limpiar memoria
    Node* current = shipmentsCBA->getHead();
    while (current != nullptr) {
        delete any_cast<Shipment*>(current->getData());
        current = current->getNext();
    }
    delete shipmentsCBA;
    
    current = shipmentsMZA->getHead();
    while (current != nullptr) {
        delete any_cast<Shipment*>(current->getData());
        current = current->getNext();
    }
    delete shipmentsMZA;
    
    current = shipmentsBUE->getHead();
    while (current != nullptr) {
        delete any_cast<Shipment*>(current->getData());
        current = current->getNext();
    }
    delete shipmentsBUE;
}

void testConnectionNetwork() {
    cout << "\n=== Test 3: Red de Conexiones entre Centros ===" << endl;
    cout << "Simulando archivo conexiones.txt" << endl;
    
    // HashTable: codigo_centro -> Lista de conexiones salientes
    HashTable connections(23);
    
    // Crear listas de conexiones para cada centro
    List* connCBA = new List();
    connCBA->push(new Connection("CBA", "MZA", 900));
    connCBA->push(new Connection("CBA", "BUE", 700));
    connCBA->push(new Connection("CBA", "ROS", 400));
    
    List* connMZA = new List();
    connMZA->push(new Connection("MZA", "BUE", 1100));
    connMZA->push(new Connection("MZA", "CBA", 900));
    
    List* connBUE = new List();
    connBUE->push(new Connection("BUE", "CBA", 700));
    connBUE->push(new Connection("BUE", "MZA", 1100));
    connBUE->push(new Connection("BUE", "ROS", 300));
    
    List* connROS = new List();
    connROS->push(new Connection("ROS", "BUE", 300));
    connROS->push(new Connection("ROS", "CBA", 400));
    
    // Almacenar en HashTable
    connections.insert("CBA", connCBA);
    connections.insert("MZA", connMZA);
    connections.insert("BUE", connBUE);
    connections.insert("ROS", connROS);
    
    cout << "\n Red de conexiones cargada" << endl;
    
    // Mostrar conexiones desde un centro
    cout << "\n--- Conexiones desde CBA ---" << endl;
    if (connections.contains("CBA")) {
        List* conns = any_cast<List*>(connections.search("CBA"));
        Node* current = conns->getHead();
        while (current != nullptr) {
            Connection* c = any_cast<Connection*>(current->getData());
            cout << "  " << c->toString() << endl;
            current = current->getNext();
        }
    }
    
    // Mostrar todas las conexiones
    cout << "\n--- Todas las Conexiones ---" << endl;
    List allCenters = connections.getKeys();
    Node* centerNode = allCenters.getHead();
    while (centerNode != nullptr) {
        string centerCode = any_cast<string>(centerNode->getData());
        List* conns = any_cast<List*>(connections.search(centerCode));
        
        Node* connNode = conns->getHead();
        while (connNode != nullptr) {
            Connection* c = any_cast<Connection*>(connNode->getData());
            cout << "  " << c->toString() << endl;
            connNode = connNode->getNext();
        }
        
        centerNode = centerNode->getNext();
    }
    
    cout << "\n Base para implementar algoritmo de camino minimo (Dijkstra)" << endl;
    cout << " HashTable permite acceso O(1) a vecinos de cada nodo" << endl;
    
    // Limpiar memoria
    Node* current = connCBA->getHead();
    while (current != nullptr) {
        delete any_cast<Connection*>(current->getData());
        current = current->getNext();
    }
    delete connCBA;
    
    current = connMZA->getHead();
    while (current != nullptr) {
        delete any_cast<Connection*>(current->getData());
        current = current->getNext();
    }
    delete connMZA;
    
    current = connBUE->getHead();
    while (current != nullptr) {
        delete any_cast<Connection*>(current->getData());
        current = current->getNext();
    }
    delete connBUE;
    
    current = connROS->getHead();
    while (current != nullptr) {
        delete any_cast<Connection*>(current->getData());
        current = current->getNext();
    }
    delete connROS;
}

void testCenterOperations() {
    cout << "\n=== Test 4: Operaciones CRUD de Centros ===" << endl;
    
    HashTable centers(23);
    
    // Agregar centros
    cout << "\n--- Agregando Centros ---" << endl;
    centers.insert("CBA", new DistributionCenter("CBA", "CentroCordoba", "Cordoba", 5000, 2000, 120));
    centers.insert("MZA", new DistributionCenter("MZA", "CentroMendoza", "Mendoza", 3000, 1200, 80));
    centers.insert("BUE", new DistributionCenter("BUE", "CentroBuenosAires", "Buenos Aires", 8000, 5000, 200));
    cout << " Centros agregados: " << centers.getSize() << endl;
    
    // Buscar centro especifico
    cout << "\n--- Buscar Centro MZA ---" << endl;
    if (centers.contains("MZA")) {
        DistributionCenter* mza = any_cast<DistributionCenter*>(centers.search("MZA"));
        cout << " Encontrado: " << mza->toString() << endl;
    }
    
    // Actualizar informacion de un centro
    cout << "\n--- Actualizar Centro CBA ---" << endl;
    if (centers.contains("CBA")) {
        DistributionCenter* oldCBA = any_cast<DistributionCenter*>(centers.search("CBA"));
        delete oldCBA;
        
        // Actualizar con nuevos valores
        DistributionCenter* newCBA = new DistributionCenter("CBA", "CentroCordoba", "Cordoba", 6000, 2500, 150);
        centers.insert("CBA", newCBA);
        cout << " Actualizado: " << newCBA->toString() << endl;
    }
    
    // Eliminar un centro
    cout << "\n--- Eliminar Centro MZA ---" << endl;
    if (centers.contains("MZA")) {
        DistributionCenter* mza = any_cast<DistributionCenter*>(centers.search("MZA"));
        delete mza;
        centers.remove("MZA");
        cout << " Centro eliminado" << endl;
    }
    
    cout << "\n--- Centros Restantes ---" << endl;
    List remainingCodes = centers.getKeys();
    Node* current = remainingCodes.getHead();
    while (current != nullptr) {
        string code = any_cast<string>(current->getData());
        DistributionCenter* center = any_cast<DistributionCenter*>(centers.search(code));
        cout << "  " << center->toString() << endl;
        current = current->getNext();
    }
    
    cout << "\n Total de centros: " << centers.getSize() << endl;
    
    // Limpiar memoria
    current = remainingCodes.getHead();
    while (current != nullptr) {
        string code = any_cast<string>(current->getData());
        DistributionCenter* center = any_cast<DistributionCenter*>(centers.search(code));
        delete center;
        current = current->getNext();
    }
}

void testHashFunctionPerformance() {
    cout << "\n=== Test 5: Rendimiento de Funcion Hash ===" << endl;
    cout << "Justificacion: Division + Folding" << endl;
    
    HashTable centers(23);  // Número primo para mejor distribucion
    
    // Codigos de centros reales (3 letras)
    string codes[] = {"CBA", "MZA", "BUE", "ROS", "TUC", "SLA", "JUJ", 
                      "COR", "MDP", "NEU", "CHU", "SFE", "FOR", "RES"};
    
    cout << "\n--- Insertando 14 centros ---" << endl;
    for (int i = 0; i < 14; i++) {
        DistributionCenter* center = new DistributionCenter(
            codes[i], "Centro" + codes[i], "Ciudad" + to_string(i),
            3000 + i * 500, 1000 + i * 200, 50 + i * 10
        );
        centers.insert(codes[i], center);
    }
    
    cout << "\n--- Estadisticas de Distribucion ---" << endl;
    centers.displayStatistics();
    
    cout << "\n--- Analisis de la Funcion Hash ---" << endl;
    cout << " Division: Usa modulo con tamaño primo (23) para distribucion uniforme" << endl;
    cout << " Folding: Divide claves en segmentos de 4 chars y suma valores ASCII" << endl;
    cout << " Ventaja: Codigos de 3 letras (CBA, MZA) se distribuyen bien" << endl;
    cout << " Linear Probing: Resuelve colisiones eficientemente" << endl;
    cout << " Factor de carga: " << (centers.getLoadFactor() * 100) << "% (optimo < 70%)" << endl;
    
    // Limpiar memoria
    List allCodes = centers.getKeys();
    Node* current = allCodes.getHead();
    while (current != nullptr) {
        string code = any_cast<string>(current->getData());
        DistributionCenter* center = any_cast<DistributionCenter*>(centers.search(code));
        delete center;
        current = current->getNext();
    }
}

void testMultipleCentersWithStatistics() {
    cout << "\n=== Test 6: Estadisticas de Múltiples Centros ===" << endl;
    
    HashTable centers(23);
    
    // Agregar múltiples centros
    centers.insert("CBA", new DistributionCenter("CBA", "CentroCordoba", "Cordoba", 5000, 2000, 120));
    centers.insert("ROS", new DistributionCenter("ROS", "CentroRosario", "Rosario", 4000, 1800, 100));
    centers.insert("MZA", new DistributionCenter("MZA", "CentroMendoza", "Mendoza", 3000, 1200, 80));
    centers.insert("BUE", new DistributionCenter("BUE", "CentroBuenosAires", "Buenos Aires", 8000, 5000, 200));
    centers.insert("TUC", new DistributionCenter("TUC", "CentroTucuman", "Tucuman", 2500, 900, 60));
    centers.insert("SLA", new DistributionCenter("SLA", "CentroSalta", "Salta", 2000, 800, 50));
    
    cout << "\n--- Todos los Centros ---" << endl;
    List allCodes = centers.getKeys();
    Node* current = allCodes.getHead();
    
    int totalCapacity = 0;
    int totalPackages = 0;
    int totalEmployees = 0;
    
    while (current != nullptr) {
        string code = any_cast<string>(current->getData());
        DistributionCenter* center = any_cast<DistributionCenter*>(centers.search(code));
        cout << "  " << center->toString() << endl;
        
        totalCapacity += center->capacity;
        totalPackages += center->dailyPackages;
        totalEmployees += center->employees;
        
        current = current->getNext();
    }
    
    cout << "\n--- Estadisticas Generales ---" << endl;
    cout << "Total de centros: " << centers.getSize() << endl;
    cout << "Capacidad total: " << totalCapacity << " paquetes" << endl;
    cout << "Paquetes diarios totales: " << totalPackages << endl;
    cout << "Empleados totales: " << totalEmployees << endl;
    cout << "Promedio de capacidad: " << (totalCapacity / centers.getSize()) << " paquetes/centro" << endl;
    
    cout << "\n HashTable permite agregar y consultar centros eficientemente" << endl;
    cout << " List permite iterar sobre todos los centros" << endl;
    
    // Limpiar memoria
    current = allCodes.getHead();
    while (current != nullptr) {
        string code = any_cast<string>(current->getData());
        DistributionCenter* center = any_cast<DistributionCenter*>(centers.search(code));
        delete center;
        current = current->getNext();
    }
}

int main() {
    cout << "========================================" << endl;
    cout << "   SISTEMA DE CENTROS DE DISTRIBUCIÓN" << endl;
    cout << "   HashTable + List" << endl;
    cout << "========================================" << endl;
    
    testDistributionCenters();
    testShipmentManagement();
    testConnectionNetwork();
    testCenterOperations();
    testHashFunctionPerformance();
    testMultipleCentersWithStatistics();
    
    cout << "\n========================================" << endl;
    cout << "   RESUMEN DE VENTAJAS" << endl;
    cout << "========================================" << endl;
    cout << " HashTable: Búsqueda O(1) de centros por codigo" << endl;
    cout << " List: Almacenamiento de envios y conexiones" << endl;
    cout << " Division+Folding: Distribucion uniforme de codigos" << endl;
    cout << " Linear Probing: Resolucion eficiente de colisiones" << endl;
    cout << " Integracion: Base para algoritmo de camino minimo" << endl;
    cout << " Escalabilidad: Redimensionamiento automatico" << endl;
    cout << "========================================" << endl;
    
    return 0;
}


