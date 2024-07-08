# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# Executable names
EXEC = catan
TEST_EXEC = test

# Source files
SRCS = main.cpp Catan.cpp Board.cpp Node.cpp Edge.cpp Player.cpp DevelopmentCard.cpp Tile.cpp

# Test source files
TEST_SRCS = Test.cpp Board.cpp Catan.cpp Player.cpp DevelopmentCard.cpp Node.cpp Tile.cpp Edge.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# Header files
HDRS = Board.hpp Node.hpp Edge.hpp Player.hpp Catan.hpp DevelopmentCard.hpp Tile.hpp Resource.hpp CardType.hpp

# Default target
all: $(EXEC) $(TEST_EXEC)

# Rule to link the object files and create the executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

# Rule to link the test object files and create the test executable
$(TEST_EXEC): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_EXEC) $(TEST_OBJS)

# Rule to compile source files into object files
%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up the build files
clean:
	rm -f $(EXEC) $(TEST_EXEC) $(OBJS) $(TEST_OBJS)

# Run the main executable
run_main: $(EXEC)
	./$(EXEC)

# Run the test executable
run_tests: $(TEST_EXEC)
	./$(TEST_EXEC)

# Phony targets
.PHONY: all clean run_main run_tests

