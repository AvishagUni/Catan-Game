Catan Game Simulation
Overview

This project is a simulation of the popular board game Catan (formerly known as The Settlers of Catan). The simulation allows players to interact with a virtual board, build settlements and cities, construct roads, trade resources, and manage development cards. The game aims to mimic the rules and mechanics of the original Catan game in a digital format.
Features

    Board Setup: Generates a randomized board with tiles, nodes (intersections), and edges (roads).
    Player Actions: Players can perform actions such as building settlements, cities, and roads, trading resources, and purchasing development cards.
    Resource Management: Players collect and manage resources (Brick, Grain, Lumber, Ore, Wool) necessary for construction and trading.
    Development Cards: Includes different types of development cards (Victory Point, Knight, Road Building, Year of Plenty, Monopoly) that players can purchase and use strategically.
    Win Condition: The game checks for a win condition where the first player to reach 10 points wins the game. Points are accumulated through settlements, cities, and certain development cards.

Classes and Structure
Classes

    Player: Represents a player in the game, tracks resources, points, owned settlements, cities, roads, and development cards.
    Node: Represents an intersection on the board where settlements and cities can be built.
    Edge: Represents a road connecting nodes, which can be owned by players.
    Tile: Represents a hexagonal tile on the board with a resource type and a dice number for resource production.
    Board: Manages the overall game board, including nodes, edges, and tiles.
    DevelopmentCard: Represents development cards that players can purchase and use during their turns.

Project Structure

    Main.cpp: Contains the main function to start the game.
    Player.hpp/cpp: Definitions for the Player class, including resource management, actions, and interaction with the board.
    Node.hpp/cpp: Definitions for the Node class, representing intersections on the board.
    Edge.hpp/cpp: Definitions for the Edge class, representing roads connecting nodes.
    Tile.hpp/cpp: Definitions for the Tile class, representing hexagonal tiles on the board.
    Board.hpp/cpp: Definitions for the Board class, managing overall game state and interactions.
    DevelopmentCard.hpp/cpp: Definitions for the DevelopmentCard class, handling actions related to development cards.

Dependencies

    C++ Standard Library: Uses standard containers (vector, map) and utilities (iostream, algorithm).
    Random Number Generation: Utilizes rand() for random number generation and srand(time(nullptr)) for seeding.

How to Play

    Setup: Players are initialized with starting resources and can place their initial settlements and roads on the board.
    Turns: Players take turns rolling dice, collecting resources based on dice rolls, and performing actions such as building settlements, cities, roads, trading, and using development cards.
    Victory: The game ends when a player reaches 10 or more points (accumulated through settlements, cities, and certain development cards).

Notes

    Randomness: The game includes random elements such as dice rolls and development card draws.
    Error Handling: Proper error handling is implemented for invalid actions or moves.
    Scalability: The board size and number of players can be adjusted by modifying constants and parameters in the source code.
