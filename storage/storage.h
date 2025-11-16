#ifndef STORAGE_H
#define STORAGE_H

#include "../utils/dataStructures/list/List.h"
#include "../entities/package/Package.h"
#include "../entities/shipment/Shipment.h"
#include "../entities/shipmentManager/ShipmentManager.h"
#include "../entities/transport/Transport.h"
#include "../entities/client/Client.h"
#include "../entities/connection/Connection.h"
#include "../entities/distributionCenter/DistributionCenter.h"
#include "../entities/distributionCenterManager/DistributionCenterManager.h"
#include "../entities/employee/Employee.h"
#include "../utils/dataStructures/graph/Graph.h"

// Global storage lists for all entities
extern List packages;
extern List shipments;
extern List shipmentManagers;
extern List transports;
extern List clients;
extern List connections;
extern List distributionCenters;
extern List distributionCenterManagers;
extern List employees;
extern Graph distributionNetwork;

#endif // STORAGE_H
