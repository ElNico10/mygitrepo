CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall -Wextra -g

SRCS = main.cpp AVLMap.cpp USCity.cpp CSVParser.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = avl_benchmark
CSV = uszips.csv

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program automatically using the CSV file
run: $(TARGET)
	@if [ -f "$(CSV)" ]; then \
		echo "Running $(TARGET) with $(CSV)..."; \
		./$(TARGET) $(CSV); \
	else \
		echo "Error: $(CSV) not found! Please place uszips.csv in this folder."; \
	fi

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean run

test: CXXFLAGS += -g
test: tests/avl_rotation_test

tests/avl_rotation_test: AVLMap.cpp USCity.cpp tests/avl_rotation_test.cpp
	$(CXX) $(CXXFLAGS) -std=c++11 -I. -o $@ $^

.PHONY: test
