Settlers of Catan Simplified Version
Overview
This project implements a simplified version of the board game "Settlers of Catan" for three players. The game combines strategic thinking, resource management, and trading ability. The goal of the game is to be the first to score 10 victory points.

Game Rules
Board:
The game board consists of 19 hexagonal tiles arranged in a hexagonal grid. Each tile represents a plot of land that yields resources, except for the desert tile, which yields nothing. The tiles are as follows:

Forest (F): Yields wood
Hills (H): Yields bricks
Pasture (P): Yields wool
Fields (M): Yields oats
Mountains (M): Yields iron
Desert (D): Yields nothing
Each tile is assigned a number between 2 and 12.

Setup:
Each player starts with 2 settlements and 2 road segments, giving them 2 victory points.
Players receive starting resources based on the locations of their initial settlements.

Gameplay:
Rolling the Dice: At the start of their turn, a player rolls two dice. All players receive resources based on the dice roll and the locations of their settlements and cities.
Trading: Players can trade resources with each other or with the bank.
Building: Players can build roads, settlements, and cities or buy development cards if they have the necessary resources.
Using Development Cards: Players can use development cards to gain special advantages.
Ending the Turn: The player's turn ends, and the next player takes their turn.
Win Condition
The game ends when a player reaches 10 or more victory points.

Project Structure
Classes:
Tile: Represents a tile on the board.
Derived classes: ForestTile, HillsTile, PastureTile, FieldsTile, MountainsTile, DesertTile

Vertex: Represents a vertex where settlements and cities can be placed.

Edge: Represents an edge where roads can be built.

Board: Represents the game board, containing tiles, vertices, and edges.

Player: Represents a player in the game.

Dice: Represents the dice used for rolling.

DevelopmentCard: Represents a development card.
Derived classes: KnightCard, MonopolyCard, RoadBuildingCard, YearOfPlentyCard

PlayerAction: Represents an action a player can take.
Derived classes: BuildSettlementAction, BuildRoadAction, BuildCityAction, TradeWithPlayerAction, TradeWithBankAction, UseDevelopmentCardAction, EndTurnAction

Namespaces
Game: Contains all game-related classes.
DevelopmentCards: Contains all development card classes.
Actions: Contains all player action classes.

Main Program
The main program demonstrates a round of the game with three players. It handles the game loop, player turns, and checks for win conditions.

Files:
Tile.h / Tile.cpp: Defines the Tile class and its derived classes.
Vertex.h / Vertex.cpp: Defines the Vertex class.
Edge.h / Edge.cpp: Defines the Edge class.
Board.h / Board.cpp: Defines the Board class and its methods.
Player.h / Player.cpp: Defines the Player class and its methods.
Dice.h / Dice.cpp: Defines the Dice class.
DevelopmentCard.h / DevelopmentCard.cpp: Defines the DevelopmentCard class and its derived classes.
PlayerAction.h / PlayerAction.cpp: Defines the PlayerAction class and its derived classes.
main.cpp: The main program that runs the game.

Implementation Details
Board Initialization:
The board is initialized with 19 tiles in a hexagonal grid. Each tile is assigned 6 vertices and 6 edges, shared with adjacent tiles.

Player Actions:
Player actions are implemented using inheritance, allowing for easy addition of new actions. Each action is derived from the PlayerAction base class and implements the execute method.

Development Cards:
Development cards are also implemented using inheritance, allowing for different types of cards with unique effects. Each card is derived from the DevelopmentCard base class and implements the use method.

Resource Distribution:
When a player rolls the dice, resources are distributed to all players based on the locations of their settlements and cities. If the dice roll is 7, the robber is activated, and players with more than 7 resource cards must discard half of them.

Conclusion
This project provides a simplified implementation of the Settlers of Catan game. It demonstrates the use of object-oriented programming principles, such as inheritance and polymorphism, to create a modular and extensible codebase. Enjoy playing the game!






