# Simple Makefile for Micro Assignment 2

CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

OBJS = ma2.o Helpers.o InsertionSort.o QuickSort.o ShellSort.o
TARGET = SortingAnalysis

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

Main.o: ma2.cpp Helpers.h InsertionSort.h QuickSort.h ShellSort.h
	$(CXX) $(CXXFLAGS) -c ma2.cpp

Helpers.o: Helpers.cpp Helpers.h
	$(CXX) $(CXXFLAGS) -c Helpers.cpp

InsertionSort.o: InsertionSort.cpp InsertionSort.h
	$(CXX) $(CXXFLAGS) -c InsertionSort.cpp

QuickSort.o: QuickSort.cpp QuickSort.h
	$(CXX) $(CXXFLAGS) -c QuickSort.cpp

ShellSort.o: ShellSort.cpp ShellSort.h
	$(CXX) $(CXXFLAGS) -c ShellSort.cpp

clean:
	rm -f $(OBJS) $(TARGET)
