#ifndef DISTRIBUTIONCENTER_MANAGER_H
#define DISTRIBUTIONCENTER_MANAGER_H

#include <string>
#include "../distributionCenter/DistributionCenter.h"
#include "../connection/Connection.h"
#include "../../utils/dataStructures/graph/GraphHashTable.h"
#include "../../utils/dataStructures/list/List.h"

class DistributionCenterManager{
    private:
        List distributionCenterPtrs;  //  Ahora almacena DistributionCenter* simples
        GraphHashTable distributionCenterNetwork;
    public:
        DistributionCenterManager();
        ~DistributionCenterManager();  //  Necesario para liberar memoria
        DistributionCenter createDistributionCenter(std::string code, std::string name, std::string city, int capacity, int dailyPackages, int employees);
        void relateDistributionCenter(std::string code1, std::string code2, int distance);
        bool hasCenter(std::string code) const;
        DistributionCenter* getCenter(std::string code) const;
        int getDistributionCentersCount() const;
        List getDistributionCentersCodes();
        void displayStatistics();
        List* getConnections(std::string code) const;
        void getCenters();
        DistributionCenter* getById(std::string id);
        GraphHashTable& getNetwork() const;
        List& getDistributionCentersList();
};

#endif // DISTRIBUTIONCENTER_MANAGER_H
