# Makefile for Micro Assignment 3
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = shortest_path
SOURCES = ma3.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: run clean