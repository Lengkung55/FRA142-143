#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <map>
#include <cstdlib>
#include <ctime>
#include <limits>

class Player {
public:
    char name;
    int points;
    int position;

    Player(char nameChar) : name(nameChar), points(100), position(0) {}
};

class Tile {
public:
    std::string effect;
    int pointChange;
    std::vector<char> playersOnTile;

    Tile(const std::string& e = "normal", int change = 0)
        : effect(e), pointChange(change) {}
};

class GameBoard {
    std::vector<Tile> tiles;

public:
    GameBoard() {
        // Example of 10 tiles with some effects
        tiles.emplace_back("normal", 0);
        tiles.emplace_back("playgame -25", -25);
        tiles.emplace_back("normal", 0);
        tiles.emplace_back("grant +20", +20);
        tiles.emplace_back("sleep in class -10", -10);
        tiles.emplace_back("normal", 0);
        tiles.emplace_back("quiz +30", +30);
        tiles.emplace_back("lose notebook -15", -15);
        tiles.emplace_back("normal", 0);
        tiles.emplace_back("bonus project +25", +25);
    }

    void updatePlayersOnTiles(std::vector<Player>& players) {
        // Clear the players from the tiles first
        for (auto& tile : tiles) {
            tile.playersOnTile.clear();
        }
        // Place the players on the tiles they are currently on
        for (const auto& player : players) {
            if (player.position < (int)tiles.size()) {
                tiles[player.position].playersOnTile.push_back(player.name);
            }
        }
    }

    void displayBoard(const std::vector<Player>& players) const {
        std::cout << "-------------------------------------------------------------\n";
        for (size_t i = 0; i < tiles.size(); ++i) {
            std::cout << "| " << std::setw(2) << (i + 1)
                      << " | " << std::setw(20) << std::left << tiles[i].effect;

            if (!tiles[i].playersOnTile.empty()) {
                std::cout << "| Player: ";
                for (char c : tiles[i].playersOnTile)
                    std::cout << c << " ";
            } else {
                std::cout << "| Player:       ";  // Empty when no player is on the tile
            }
            std::cout << "|\n";
            std::cout << "-------------------------------------------------------------\n";
        }
    }

    int getSize() const {
        return tiles.size();
    }

    int applyTileEffect(Player& player) {
        if (player.position >= (int)tiles.size()) return 0;
        player.points += tiles[player.position].pointChange;
        return tiles[player.position].pointChange;
    }
};

void printPlayerScores(const std::vector<Player>& players) {
    std::cout << "\nPlayer Scores:\n";
    for (const auto& player : players) {
        std::cout << player.name << " : " << player.points << " points\n";
    }
}

int main() {
    int numPlayers;
    std::cout << "Enter number of players (2-4): ";
    std::cin >> numPlayers;

    if (numPlayers < 2 || numPlayers > 4) {
        std::cout << "Invalid number of players. Please enter between 2 and 4.\n";
        return 1;
    }

    std::vector<Player> players;
    for (int i = 0; i < numPlayers; ++i) {
        players.emplace_back('A' + i);
    }

    GameBoard board;

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // First turn
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\nDice: Press Enter to roll the dice...\n";
    std::cin.get();

    int diceRoll = std::rand() % 6 + 1;
    std::cout << "Dice rolled: " << diceRoll << "\n";

    // Move player A
    players[0].position += diceRoll;
    if (players[0].position >= board.getSize()) {
        players[0].position = board.getSize() - 1;
    }

    int effect = board.applyTileEffect(players[0]);

    board.updatePlayersOnTiles(players);
    printPlayerScores(players);
    board.displayBoard(players);  // Pass players to update the board display

    return 0;
}
