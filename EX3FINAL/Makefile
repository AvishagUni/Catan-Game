# Compiler
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Executable
EXEC = catan

# Source files
SRC = main.cpp Catan.cpp Player.cpp HexTile.cpp DevelopmentCard.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Default target
all: $(EXEC)

# Linking
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilation
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean up build artifacts
clean:
	rm -f $(OBJ) $(EXEC)

# Phony targets
.PHONY: all clean










