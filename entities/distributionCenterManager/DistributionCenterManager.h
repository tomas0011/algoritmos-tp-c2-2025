#ifndef DISTRIBUTIONCENTER_MANAGER_H
#define DISTRIBUTIONCENTER_MANAGER_H

#include <string>
#include "../distributionCenter/DistributionCenter.h"
#include "../connection/Connection.h"
#include "../../utils/dataStructures/Graph/GraphHashTable.h"
#include "../../utils/dataStructures/List/List.h"
#include "../../services/connection/ConnectionService.h"

class DistributionCenterManager{
    private:
        List distributionCenterList;  // Almacena DistributionCenter*
        GraphHashTable distributionCenterNetwork;  // Grafo técnico con aristas
        ConnectionService* connectionService;  // Service para manejar conexiones
        
        // Método privado para sincronizar Connection con arista del grafo
        void addConnectionToGraph(const Connection& conn);
    public:
        DistributionCenterManager(ConnectionService* connService);
        ~DistributionCenterManager();
        
        // Gestión de centros
        DistributionCenter createDistributionCenter(std::string code, std::string name, std::string city, int capacity, int dailyPackages, int employees);
        bool hasCenter(std::string code) const;
        DistributionCenter* getCenter(std::string code) const;
        int getDistributionCentersCount() const;
        List getDistributionCentersCodes();
        void getCenters();
        DistributionCenter* getById(std::string id);
        
        // Gestión de Connections (usando ConnectionService)
        void createConnection(std::string originCode, std::string destinationCode, double distance);
        void createBidirectionalConnection(std::string originCode, std::string destinationCode, double distance);
        void relateDistributionCenter(std::string code1, std::string code2, int distance);  // Crea connection + arista
        void displayAllConnections() const;  // Mostrar todas las conexiones del service
        
        // Operaciones técnicas (usan el grafo interno)
        void displayStatistics();
        List* getConnections(std::string code) const;  // Para compatibilidad
        GraphHashTable& getNetwork() const;  // Para algoritmos como Dijkstra
        List& getDistributionCentersList();
};

#endif // DISTRIBUTIONCENTER_MANAGER_H
