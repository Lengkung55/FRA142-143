#include "Core.h"
#include "Deck.h"
#include "Card.h"
#include "Action/Action.h"
#include "Action/ExtraClass.h"
#include "Action/AcademicLeave.h"
#include "Action/SubtractScore.h"
#include "Action/AddScore.h"
#include <iostream>
#include <algorithm>
#include <random>

// /*How to complie "g++ Main.cpp Core.cpp Deck.cpp Card.cpp Action\Action.cpp -o Main
//    How to run the program
//    1. Open a terminal.
//    2. Navigate to the directory where the files are located.
//    3. Compile the code using the command:
//       g++ Main.cpp Core.cpp Deck.cpp Card.cpp Action/Action.cpp -o Main
//    4. Run the program using the command:" 
// >> ./Main   */




// void printPlayerScores(const std::vector<Player>& players) {
//     std::cout << "\nPlayer Scores:\n";
//     for (const auto& player : players) {
//         std::cout << player.name << " : " << player.points << " points, Position: " << player.position + 1 << "\n";
//     }
// }

// int rollDice() {
//     return std::rand() % 6 + 1;
// }

// int main() {
//     int numPlayers;
//     std::cout << "Enter number of players (2-4): ";
//     std::cin >> numPlayers;
//     if (numPlayers < 2 || numPlayers > 4) {
//         std::cout << "Invalid number of players. Please enter between 2 and 4.\n";
//         return 1;
//     }

//     std::vector<Player> players;
//     for (int i = 0; i < numPlayers; ++i) {
//         players.emplace_back('A' + i);
//     }

//     GameBoard board;

//     std::srand(static_cast<unsigned int>(std::time(nullptr)));

//     bool gameOver = false;
//     int turn = 0;

//     while (!gameOver) {
//         Player& currentPlayer = players[turn % numPlayers];

//         std::cout << "\nPlayer " << currentPlayer.name << "'s turn. Press Enter to roll the dice...";
//         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//         std::cin.get();

//         int diceRoll = rollDice();
//         std::cout << "🎲 Dice rolled: " << diceRoll << "\n";

//         currentPlayer.position += diceRoll;
//         if (currentPlayer.position >= board.getSize()) {
//             currentPlayer.position = board.getSize() - 1;
//             std::cout << "Player " << currentPlayer.name << " reached the last tile!\n";
//             gameOver = true;
//         } else {
//             std::cout << "Player " << currentPlayer.name << " moves to tile " << currentPlayer.position + 1 << "\n";
//         }

//         int effect = board.applyTileEffect(currentPlayer);
//         if (effect != 0) {
//             if (effect > 0) {
//                 std::cout << "Good! Points +" << effect << "\n";
//             } else {
//                 std::cout << "Oh no! Points " << effect << "\n";
//             }
//         } else {
//             std::cout << "No point change on this tile.\n";
//         }

//         if (currentPlayer.points <= 0) {
//             std::cout << "Player " << currentPlayer.name << " has dropped to 0 points and failed the course! Game over.\n";
//             gameOver = true;
//         }

//         board.updatePlayersOnTiles(players);
//         printPlayerScores(players);
//         board.displayBoard();

//         turn++;
//     }

//     std::cout << "\nGame finished!\n";

//     // หาผู้ชนะ (คะแนนมากสุดและยังไม่ F)
//     int maxPoints = -9999;
//     char winner = '?';
//     for (const auto& p : players) {
//         if (p.points > maxPoints) {
//             maxPoints = p.points;
//             winner = p.name;
//         }
//     }
//     std::cout << "Winner is Player " << winner << " with " << maxPoints << " points!\n";

//     return 0;
// }#include "Core.h"
// #include <iostream>
// #include <limits>
// #include <ctime>

// int main() {
//     Game game;
//     int numPlayers;
//     std::cout << "Enter number of players (2-4): ";
//     std::cin >> numPlayers;
//     if (numPlayers < 2 || numPlayers > 4) {
//         std::cout << "Invalid number of players. Please enter between 2 and 4.\n";
//         return 1;
//     }
//     game.setupPlayers(numPlayers);
//     game.startGame();

//     while (!game.checkGameEnd()) {
//         // ตัวอย่างการวนลูปเทิร์น
//         std::cout << "\nPress Enter to roll the dice...";
//         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//         std::cin.get();

//         int roll = game.rollDice();
//         std::cout << "🎲 Dice rolled: " << roll << "\n";
//         // คุณสามารถเพิ่ม logic การเดินและการ์ดตรงนี้

//         game.nextTurn();
//     }

//     std::cout << "\nGame finished!\n";
//     // แสดงคะแนนผู้เล่น
//     const auto& players = game.getPlayers();
//     int maxScore = -9999;
//     std::string winner;
//     for (const auto& p : players) {
//         std::cout << p.getName() << " : " << p.getScore() << " points, Position: " << p.getPosition() << "\n";
//         if (p.getScore() > maxScore) {
//             maxScore = p.getScore();
//             winner = p.getName();
//         }
//     }
//     std::cout << "Winner is " << winner << " with " << maxScore << " points!\n";
//     return 0;
// }


// // int main() {


    
// //     // char option;
// //     // do {
// //     //     Game game;
// //     //     int numPlayers;

// //     //     std::cout << "Enter Player numbers: ";
// //     //     std::cin >> numPlayers;
// //     //     game.setupPlayers(numPlayers);

// //     //     game.startGame();

// //     //     while (!game.checkGameEnd()) {
// //     //         std::cout << "Roll Dice (y), Restart (r), Quit (q): ";
// //     //         std::cin >> option;

// //     //         if (option == 'y') {
// //     //             int roll = game.rollDice();
// //     //             std::cout << "Roll Dice: " << roll << std::endl;
// //     //             // 
// //     //             //  Game  getCurrentPlayer()  player 
// //     //             //  player.move(roll)

// //     //             game.nextTurn(); // 
// //     //         } else if (option == 'r') {
// //     //             std::cout << "Restarting game...\n";
// //     //             break; // while 
// //     //         } else if (option == 'q') {
// //     //             std::cout << "Quitting game...\n";
// //     //             return 0;
// //     //         } else {
// //     //             std::cout << "Invalid option. Try again.\n";
// //     //         }
// //     //     }

// //     //     if (game.checkGameEnd()) {
// //     //         std::cout << "Game Ended!\n";
// //     //     }

// //     // } while (option == 'r');

// //       Action* action = new ExtraClass();
// //       action->Execute(*(new Player("Player1")), *(new Deck()));
// //       delete action; // Clean up dynamically allocated memory


// //     return 0;
// // }


void printPlayerScores(const std::vector<Player>& players) {
    std::cout << "\nPlayer Scores:\n";
    for (const auto& player : players) {
        std::cout << player.getName() << " : " << player.getScore() << " points, Position: " << player.getPosition() + 1 << "\n";
    }
}

int main() {
    std::cout << "Escape from F: Survive 50 tiles and avoid failing!\n";
    int numPlayers;

    // วนลูปจนกว่าจะกรอกจำนวนผู้เล่นถูกต้อง
    while (true) {
        std::cout << "Enter number of players (2-4): ";
        std::cin >> numPlayers;
        if (numPlayers >= 2 && numPlayers <= 4) {
            break; // ออกจากลูปถ้าถูกต้อง
        }
        std::cout << "Invalid number of players. Please enter between 2 and 4.\n";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // <<== เพิ่มบรรทัดนี้

    Game game;
    game.setupPlayers(numPlayers);

    // สุ่มลำดับผู้เล่น
    auto& players = const_cast<std::vector<Player>&>(game.getPlayers());
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(players.begin(), players.end(), g);

    game.startGame();

    // สร้างกระดานและแสดงตารางหลังเริ่มเกม
    Board board;
    board.printBoard();

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    bool gameOver = false;
    int turn = 0;
    while (!gameOver) {
        Player& currentPlayer = players[turn % numPlayers];

        std::cout << "\nPlayer " << currentPlayer.getName() << "'s turn.\n";
        std::cout << "Roll Dice (y), Restart (r), Quit (q): ";
        char option;
        std::cin >> option;

        if (option == 'q') {
            std::cout << "Quitting game...\n";
            break;
        } else if (option == 'r') {
            std::cout << "Restarting game...\n";
            return main();
        } else if (option == 'y') {
            int diceRoll = game.rollDice();
            std::cout << "Dice rolled: " << diceRoll << "\n";
            currentPlayer.move(diceRoll);

            // Check if reached the last tile
            if (currentPlayer.getPosition() >= 49) {
                std::cout << "Player " << currentPlayer.getName() << " reached the last tile!\n";
                gameOver = true;
            } else {
                std::cout << "Player " << currentPlayer.getName() << " moves to tile " << currentPlayer.getPosition() + 1 << "\n";
            }

            // ตัวอย่าง: ถ้าตกช่องพิเศษ (ทุกๆ 7 ช่อง หรือ tile 10, 20, 30, 40)
            if ((currentPlayer.getPosition() + 1) % 10 == 0) {
                std::cout << "Special tile! Draw a card!\n";
                Card card = game.drawCard();
                card.affect(currentPlayer);
            }
            // ตัวอย่าง: ถ้าตกช่อง academic leave (เช่น tile 25)
            else if (currentPlayer.getPosition() == 24) {
                std::cout << "📚 Academic Leave! Skip next turn.\n";
                currentPlayer.skipNextTurn();
            }
            
            else {

                int effect = board.applyTileEffect(currentPlayer);
                if (effect != 0) {
                    if (effect > 0) {
                        std::cout << "Good! Points +" << effect << "\n";
                    } else {
                        std::cout << "Oh no! Points " << effect << "\n";
                    }
                } else {
                    std::cout << "No point change on this tile.\n";
                }
            }

            // Check F
            if (currentPlayer.getScore() <= 0) {
                std::cout << "Player " << currentPlayer.getName() << " has dropped to 0 points and failed the course! Game over.\n";
                gameOver = true;
            }

            board.updatePlayersOnTiles(game.getPlayers());
            board.printBoard();

            printPlayerScores(game.getPlayers());
            game.nextTurn();
            ++turn; // เพิ่มตรงนี้
        } else {
            std::cout << "Invalid option. Please try again.\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
    }

    std::cout << "\nGame finished!\n";
    // หาผู้ชนะ (คะแนนมากสุด)
    const auto& finalPlayers = game.getPlayers(); // <== เปลี่ยนชื่อ
    int maxPoints = -9999;
    std::string winner;
    for (const auto& p : finalPlayers) {
        if (p.getScore() > maxPoints) {
            maxPoints = p.getScore();
            winner = p.getName();
        }
    }
    std::cout << "Winner is " << winner << " with " << maxPoints << " points!\n";
    return 0;
}