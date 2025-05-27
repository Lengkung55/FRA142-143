#include "Core.h"
#include "Deck.h"
#include "Card.h"
#include "Action/Action.h"
#include "Action/AcademicLeave.h"
#include "Action/SubtractScore.h"
#include "Action/AddScore.h"
#include "Action/ExtraClass.h"
#include <iomanip>
#include <cstdlib>   //  rand()
#include <ctime>     //  srand()
#include <iostream>

Game::Game() : currentPlayerIndex_(0) {
    std::srand(std::time(nullptr)); // seed random
}

void Game::setupPlayers(int numPlayers){

    for (int i = 0; i < numPlayers; ++i){
        std::string name;
        std::cout << "Enter name" << (i + 1) << ": ";
        std::cin >> name;

        Player newPlayer(name);
        players_.push_back(newPlayer);
    }

    // for (int i = 0; i < players_.size(); ++i){
    //      std::cout << "Player " << (i + 1) << ": " << players_[i].getName() << std::endl;
    // }
}


void Game::startGame() {
    // check players size 
    if (players_.size() < 2 || players_.size() > 4) {
        std::cerr << "Needed at least 2 Players.\n";
        return;
    }
    std::cout << "Game Start!\n";
}

void Game::nextTurn() {
    currentPlayerIndex_ = (currentPlayerIndex_ + 1) % players_.size();
}

int Game::rollDice() {
    return rand() % 6 + 1; // dice roll random 1-6
}

bool Game::checkGameEnd() {
    // check position if all player at position = 50 else game continue 
    for (const auto& p : players_) { 
        if (p.getPosition() < 50) return false;
    }
    return true;
}

const std::vector<Player>& Game::getPlayers() const{
    return players_;
}

Card Game::drawCard() {
    if (!deck_) {
        deck_ = new Deck();
        deck_->setCard();
    }
    return deck_->drawCard();
}



Player::Player(const std::string& name)
    : name_(name), position_(0), score_(100), skip_turn_(false) {}

void Player::move(int steps) {
    position_ += steps;
}

void Player::updateScore(int points) {
    score_ += points;
}

std::string Player::getName() const {
    return name_;
}

int Player::getPosition() const {
    return position_;
}

int Player::getScore() const {
    return score_;
}

void Player::skipNextTurn() {
    skip_turn_ = true;
}

bool Player::shouldSkipTurn() const {
    return skip_turn_;
}

void Player::resetSkipTurn() {
    skip_turn_ = false;
}



Board::Board() {
    for (int i = 0; i < size_; ++i) {
        std::string effect = "ปกติ";
        int pointChange = 0;

        if (i == 4 || i == 14 || i == 34) {
            effect = "โดดเรียน -40";
            pointChange = -40;
        } else if (i == 9 || i == 29 || i == 39) {
            effect = "เล่นการพนัน -50";
            pointChange = -50;
        } else if (i == 19 || i == 44) {
            effect = "ติดยา -60";
            pointChange = -60;
        } else if (i == 24) {
            effect = "Academic Leave! ขาดเรียน -100";
            pointChange = -100;
        } else if (i == 49) {
            effect = "จบเกม!";
            pointChange = 0;
        } else if (i == 7 || i == 17 || i == 27 || i == 37 || i == 47) {
            effect = "ช่วยงานอาจารย์ +10";
            pointChange = +10;
        } else if (i == 12 || i == 22 || i == 32 || i == 42) {
            effect = "ทำกิจกรรม +8";
            pointChange = +8;
        } else if (i == 2 || i == 20 || i == 35) {
            effect = "ได้ทุนการศึกษา +15";
            pointChange = +15;
        }
        // ช่อง 10, 20, 30, 40 (index 9, 19, 29, 39) ให้เป็น Draw a card! ได้ถ้าต้องการ
        else if ((i + 1) % 10 == 0) {
            effect = "Draw a card!";
            // pointChange = 0;
        }

        tiles_.push_back(Tile(effect, pointChange));
    }
}

void Board::updatePlayersOnTiles(const std::vector<Player>& players) {
    for (auto& tile : tiles_) {
        tile.playersOnTile.clear();
    }
    for (const auto& player : players) {
        int pos = player.getPosition();
        if (pos >= 0 && pos < static_cast<int>(tiles_.size())) {
            tiles_[pos].playersOnTile.push_back(player.getName());
        }
    }
}

void Board::printBoard() const {
    const int width = 20, rows = 10, cols = 5;
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col)
            std::cout << "+" << std::string(width, '-');
        std::cout << "+\n";
        for (int col = 0; col < cols; ++col) {
            int index = row * cols + col;
            std::string label = "Tile " + std::to_string(index + 1);
            std::cout << "|" << std::setw(width) << std::left << label;
        }
        std::cout << "|\n";
        for (int col = 0; col < cols; ++col) {
            int index = row * cols + col;
            std::cout << "|" << std::setw(width) << std::left << tiles_[index].effect;
        }
        std::cout << "|\n";
        // แสดงชื่อผู้เล่นในแต่ละช่อง
        for (int col = 0; col < cols; ++col) {
            int index = row * cols + col;
            std::string pStr = "Player: ";
            for (const auto& name : tiles_[index].playersOnTile)
                pStr += name + " ";
            std::cout << "|" << std::setw(width) << std::left << pStr;
        }
        std::cout << "|\n";
    }
    for (int col = 0; col < cols; ++col)
        std::cout << "+" << std::string(width, '-');
    std::cout << "+\n";
}

int Board::getSize() const {
    return tiles_.size();
}

int Board::applyTileEffect(Player& player) {
    int pos = player.getPosition();
    if (pos < 0 || pos >= static_cast<int>(tiles_.size())) return 0;
    int pointChange = tiles_[pos].pointChange;
    player.updateScore(pointChange);
    return pointChange;
}
bool tile::hasAction() const {
    return action_ != nullptr;
}
