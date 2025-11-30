CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g
TARGET = emergency_system
OBJS = main.o Graph.o PriorityQueue.o Hospital.o EmergencySystem.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp Graph.h Hospital.h EmergencySystem.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Graph.o: Graph.cpp Graph.h
	$(CXX) $(CXXFLAGS) -c Graph.cpp

PriorityQueue.o: PriorityQueue.cpp PriorityQueue.h
	$(CXX) $(CXXFLAGS) -c PriorityQueue.cpp

Hospital.o: Hospital.cpp Hospital.h PriorityQueue.h
	$(CXX) $(CXXFLAGS) -c Hospital.cpp

EmergencySystem.o: EmergencySystem.cpp EmergencySystem.h Graph.h Hospital.h
	$(CXX) $(CXXFLAGS) -c EmergencySystem.cpp

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean