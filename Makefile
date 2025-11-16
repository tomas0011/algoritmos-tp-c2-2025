CXX = g++
CXXFLAGS = -std=c++17 -Wall -I.
TARGET = tp_c2_2025
SRCS = main.cpp \
       bash/bash.cpp \
       storage/mockData.cpp \
       storage/storage.cpp \
       services/initializeServices.cpp \
       services/package/packageService.cpp \
       services/shipment/shipmentService.cpp \
       services/distributionCenter/distributionCenterService.cpp \
       services/client/clientService.cpp \
       services/employee/employeeService.cpp \
       services/Connection/ConnectionService.cpp \
       services/ShipmentManager/ShipmentManagerService.cpp \
       entities/employee/Employee.cpp \
       entities/distributionCenter/DistributionCenter.cpp \
       entities/distributionCenterManager/DistributionCenterManager.cpp \
       entities/package/Package.cpp \
       entities/shipment/Shipment.cpp \
       entities/shipmentManager/ShipmentManager.cpp \
       entities/transport/Transport.cpp \
       entities/client/Client.cpp \
       entities/connection/Connection.cpp

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Test targets
test-hashtable:
	$(CXX) $(CXXFLAGS) -o test_hashtable utils/dataStructures/hashtable/hashTableTest.cpp
	./test_hashtable

test-graphhashtable:
	$(CXX) $(CXXFLAGS) -o test_graphhashtable utils/dataStructures/graph/graphHashTableTest.cpp
	./test_graphhashtable

test-list:
	$(CXX) $(CXXFLAGS) -o test_list utils/dataStructures/list/listTest.cpp
	./test_list

test-tree:
	$(CXX) $(CXXFLAGS) -o test_tree utils/dataStructures/tree/treeTest.cpp
	./test_tree

clean:
	rm -f $(TARGET) test_hashtable test_graphhashtable test_list test_tree

.PHONY: clean test-hashtable test-graphhashtable test-list test-tree
