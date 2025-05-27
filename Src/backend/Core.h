#pragma once

//#include "Board.h"
#include "Action/Action.h"

#include <vector>
#include <memory>
#include <string>

class Deck; // Forward declaration
class Card; // Forward declaration
class Action;


class Player {
public:
    Player(const std::string& name);

    void move(int step);
    void updateScore(int points);
    std::string getName() const;
    int getPosition() const;
    int getScore() const;

    void skipNextTurn();           
    bool shouldSkipTurn() const;  
    void resetSkipTurn();         

    // เพิ่ม setter สำหรับ Board หรือการรีเซ็ตค่า
    void setPosition(int pos) { position_ = pos; }
    void setName(const std::string& name) { name_ = name; }
    void setScore(int score) { score_ = score; }

private:
    std::string name_;
    int position_ = 0;
    int score_ = 100;
    bool skip_turn_ = false;
};



class Game{
public:
    Game();

    void setupPlayers(int numPlayers);
    void startGame();
    void nextTurn();

    Card drawCard();

    int rollDice();
    bool checkGameEnd();
    const std::vector<Player>& getPlayers() const;

private:
    std::vector<Player> players_;
    //Board board_;   
    Deck* deck_;     
    int currentPlayerIndex_;
};



class tile {
public:
    tile(int index, Action* action) : index_(index), action_(action){}
    
    void triggerAction(Player& player, Deck& deck);

    int getIndex() const { return index_; }

    // Action getAction() const { return action_; }

    // void setAction(const Action& action) { action_ = action; }

    bool hasAction() const ;

private:
    int index_;
    Action* action_;;
    
};


class Tile {
public:
    std::string effect;
    int pointChange;
    std::vector<std::string> playersOnTile;

    Tile(const std::string& e = "normal", int change = 0)
        : effect(e), pointChange(change) {}
};

class Board {
public:
    Board();
    void printBoard() const;
    int getSize() const;
    int applyTileEffect(Player& player);
    void updatePlayersOnTiles(const std::vector<Player>& players); // เพิ่มบรรทัดนี้

private:
    int size_ = 50;
    std::vector<Tile> tiles_;
};


