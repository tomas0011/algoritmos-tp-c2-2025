#ifndef MOCK_DATA_H
#define MOCK_DATA_H

#include <vector>
#include "entities/package/Package.h"
#include "entities/shipment/Shipment.h"
#include "entities/shipmentManager/ShipmentManager.h"
#include "entities/transport/Transport.h"
#include "entities/client/Client.h"
#include "entities/connection/Connection.h"
#include "entities/distributionCenter/DistributionCenter.h"
#include "entities/employee/Employee.h"

// Mock data for testing
extern std::vector<Package> mockPackages;
extern std::vector<Shipment> mockShipments;
extern std::vector<ShipmentManager> mockShipmentManagers;
extern std::vector<Transport> mockTransports;
extern std::vector<Client> mockClients;
extern std::vector<Connection> mockConnections;
extern std::vector<DistributionCenter> mockDistributionCenters;
extern std::vector<Employee> mockEmployees;

// Functions to display mock data
void displayMockPackages();
void displayMockShipments();
void displayMockShipmentManagers();
void displayMockTransports();
void displayMockClients();
void displayMockConnections();
void displayMockDistributionCenters();
void displayMockEmployees();

#endif // MOCK_DATA_H