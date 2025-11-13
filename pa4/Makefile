# Makefile for PA4 - Movie and TV Show Search and Sort

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g

TARGET = pa4

SOURCES = main.cpp Movie.cpp MovieDatabase.cpp Utils.cpp Tests.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
