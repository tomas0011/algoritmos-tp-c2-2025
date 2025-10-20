#ifndef SHIPMENT_MANAGER_H
#define SHIPMENT_MANAGER_H

#include "../shipment/Shipment.h"
#include <vector>
#include <map>
#include <string>

class ShipmentManager {
private:
    std::vector<Shipment> shipments;
    
    // Índices para optimizar búsquedas (se crean al cargar datos)
    std::map<std::string, std::vector<int>> centerIndex;     // centro -> índices de envíos
    std::map<int, std::vector<int>> clientIndex;             // cliente -> índices de envíos
    std::map<int, std::vector<int>> dateIndex;               // fecha -> índices de envíos
    
    bool indicesBuilt;
    
    // Métodos privados
    void buildIndices();
    void clearIndices();

public:
    // Constructor
    ShipmentManager();
    
    // Carga de datos
    bool loadFromFile(const std::string& filename);
    void addShipment(const Shipment& shipment);
    
    // Funcionalidades del ítem B
    
    // B.1: Total de envíos por centro en rango de fechas
    std::map<std::string, int> getShipmentsByCenter(int startDate, int endDate);
    
    // B.2: Detectar centros con sobrecarga
    std::vector<std::string> getOverloadedCenters(int maxShipmentsPerWeek);
    
    // B.3: Buscar envíos de un cliente
    std::vector<Shipment> getShipmentsByClient(int clientId);
    std::vector<Shipment> getShipmentsByPackage(int packageId);  // Por si acaso
    
    // Métodos de utilidad
    int getTotalShipments() const;
    void printStatistics() const;
    
    // Para análisis de complejidad
    void analyzeComplexity() const;
};

#endif