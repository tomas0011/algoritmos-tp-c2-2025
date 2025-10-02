CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = tp_c2_2025
SRCS = main.cpp \
       entities/employee/Employee.cpp \
       entities/distributionCenter/DistributionCenter.cpp

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

.PHONY: clean
