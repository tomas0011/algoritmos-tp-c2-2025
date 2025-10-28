#ifndef DISTRIBUTIONCENTER_MANAGER_H
#define DISTRIBUTIONCENTER_MANAGER_H

#include <vector>
#include <string>
#include "../distributionCenter/DistributionCenter.h"

class DistributionCenterManager{
    private:
        std::vector<DistributionCenter> distributionCenters;
    public:
        void createDistributionCenter(int id, std::string name, std::string city, int capacity, int dailyPackages, int employees);
        void getCenters();
        const std::vector<DistributionCenter>& getDistributionCenters() const;
};

#endif // DISTRIBUTIONCENTER_MANAGER_H