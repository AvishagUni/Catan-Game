all: catan

catan: main.o Board.o Tile.o Player.o Dice.o
    g++ -o catan main.o Board.o Tile.o Player.o Dice.o -std=c++11

main.o: main.cpp Board.hpp Player.hpp
    g++ -c main.cpp -std=c++11

Board.o: Board.cpp Board.hpp Tile.hpp Player.hpp Dice.hpp
    g++ -c Board.cpp -std=c++11

Tile.o: Tile.cpp Tile.hpp Resource.hpp TileType.hpp
    g++ -c Tile.cpp -std=c++11

Player.o: Player.cpp Player.hpp Resource.hpp
    g++ -c Player.cpp -std=c++11

Dice.o: Dice.cpp Dice.hpp
    g++ -c Dice.cpp -std=c++11

clean:
    rm -f *.o catan
