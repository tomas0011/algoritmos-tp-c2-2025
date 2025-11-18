#ifndef DISTRIBUTIONCENTER_MANAGER_H
#define DISTRIBUTIONCENTER_MANAGER_H

#include <vector>
#include <string>
#include "../distributionCenter/DistributionCenter.h"
#include "../../utils/dataStructures/graph/GraphHashTable.h"

class DistributionCenterManager{
    private:
        std::vector<DistributionCenter> distributionCenters;
        GraphHashTable distributionCenterNetwork;
    public:
        DistributionCenterManager();
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
        const std::vector<DistributionCenter>& getDistributionCenters() const;
        DistributionCenter* getById(int id);
};

#endif // DISTRIBUTIONCENTER_MANAGER_H
