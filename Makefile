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

clean:
	rm -f $(TARGET)

.PHONY: clean
