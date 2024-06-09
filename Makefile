# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra -I.

# Executable name
EXEC = catan

# Source files
SRC = main.cpp Board.cpp Tile.cpp Vertex.cpp Edge.cpp Player.cpp Dice.cpp DevelopmentCard.cpp PlayerAction.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Default target
all: $(EXEC)

# Linking the executable
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compiling source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and the executable
clean:
	rm -f $(OBJ) $(EXEC)

# Phony targets
.PHONY: all clean
