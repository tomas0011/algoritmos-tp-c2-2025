#ifndef DISTRIBUTION_CENTER_SERVICE_H
#define DISTRIBUTION_CENTER_SERVICE_H

#include "../../utils/dataStructures/matias/graph/Graph.h"
#include "../../entities/distributionCenter/DistributionCenter.h"
#include <iostream>

class DistributionCenterService {
private:
    Graph& network; // Referencia al grafo de la red de distribución

public:
    DistributionCenterService(Graph& networkRef);

    // CRUD operations
    //verificar si employees y capacity van como vectores o enteros??

    void createCenter(int id, const std::string& name, const std::string& city,
                      int capacity, int warehouse, int employees);
    DistributionCenter* getCenterById(int id);
    void connectCenters(int id1, int id2, double distance);
    void displayAllCenters();
    void displayConnections(int id);
};

#endif // DISTRIBUTION_CENTER_SERVICE_H