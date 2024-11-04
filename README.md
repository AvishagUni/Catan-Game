# Catan Game Simulation

This project is a simulation of the popular board game **Catan** (formerly known as *The Settlers of Catan*). It replicates the game’s mechanics digitally, allowing players to experience virtual gameplay that includes building, trading, resource management, and strategic planning.

---

## 🎲 Game Overview

In this simulation, players can:
- Build settlements, cities, and roads.
- Collect resources and trade with others.
- Purchase and use development cards strategically.
- Compete to be the first to reach 10 victory points to win the game.

### Key Features

- **Board Setup**: Generates a randomized game board with hexagonal resource tiles, nodes (for settlements/cities), and edges (for roads).
- **Player Actions**: Includes actions like building, trading, and purchasing development cards.
- **Resource Management**: Players collect resources (Brick, Grain, Lumber, Ore, Wool) for various constructions and trades.
- **Development Cards**: Offers development cards with unique abilities (Victory Point, Knight, Road Building, Year of Plenty, Monopoly).
- **Win Condition**: Checks for the win condition—first player to reach 10 points wins the game.

---

## 🏗️ Classes and Structure

- **Player**: Manages player-specific resources, points, and owned assets (settlements, cities, roads, and development cards).
- **Node**: Represents intersections on the board where players can build settlements and cities.
- **Edge**: Represents a road connecting two nodes, which can be owned by players.
- **Tile**: Represents hexagonal tiles with resource types and dice numbers for resource production.
- **Board**: Manages the overall game board, including nodes, edges, and tiles.
- **DevelopmentCard**: Represents development cards that players can purchase and use during their turns.

---

## 📂 Project Structure

- **Main.cpp**: Entry point of the game, containing the main function.
- **Player.hpp/cpp**: Defines the Player class, including resource management, actions, and interactions with the board.
- **Node.hpp/cpp**: Defines the Node class, representing intersections on the board.
- **Edge.hpp/cpp**: Defines the Edge class, representing roads.
- **Tile.hpp/cpp**: Defines the Tile class, representing hexagonal resource tiles.
- **Board.hpp/cpp**: Defines the Board class, managing the game’s overall state.
- **DevelopmentCard.hpp/cpp**: Defines the DevelopmentCard class for handling actions related to development cards.

---

## 🛠️ Dependencies

- **C++ Standard Library**: Uses standard containers (`vector`, `map`) and utilities (`iostream`, `algorithm`).
- **Random Number Generation**: Utilizes `rand()` for generating random values and `srand(time(nullptr))` for seeding randomness.

---

## 🎮 How to Play

1. **Setup**: Players start with initial resources and place their initial settlements and roads.
2. **Turns**:
   - Players roll dice to collect resources based on dice roll outcomes.
   - Perform actions like building, trading, and using development cards.
3. **Victory**: The game ends when a player reaches 10 or more victory points, earned through settlements, cities, and development cards.

---

## 📝 Notes

- **Randomness**: The simulation includes random elements like dice rolls and card draws.
- **Error Handling**: Implemented to handle invalid actions and moves.
- **Scalability**: Board size and number of players can be adjusted by modifying constants in the source code.

---

This simulation project brings the strategic depth of Catan into a digital format, providing a foundation for learning about game development and object-oriented programming in C++. Enjoy building, trading, and strategizing your way to victory!

