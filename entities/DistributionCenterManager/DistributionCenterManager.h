#ifndef DISTRIBUTIONCENTER_MANAGER_H
#define DISTRIBUTIONCENTER_MANAGER_H

#include <map>
#include <string>
#include "DistributionCenter.h"

class DistributionCenterManager{
    private:
        std::map<int, DistributionCenter> centers;
    public:
        void createDistributionCenter(int id, std::string name, std::string city, int capacity, int dailyPackages, int employees);
        void getCenters();
};

#endif // DISTRIBUTIONCENTER_MANAGER_H