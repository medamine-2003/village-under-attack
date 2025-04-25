
#include "Board.h"
#include "buildings/TownHall.h"
#include "buildings/GoldMine.h"
#include "buildings/ElixirCollector.h"
#include "buildings/Wall.h"
#include <iostream>
#include <iomanip>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

bool kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    
    if(ch != EOF) {
        ungetc(ch, stdin);
        return true;
    }
    return false;
}

int getch() {
    int ch;
    struct termios oldt, newt;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

void render(const Board& board) {
    clearScreen();

    // Simple grid rendering
    for (int y = 0; y < board.getPlayer().getPosition().y - 5; y++) {
        std::cout << std::endl;
    }

    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 20; x++) {
            Position pos(x + board.getPlayer().getPosition().x - 10, 
                         y + board.getPlayer().getPosition().y - 5);

            bool rendered = false;

            // Render player
            if (pos == board.getPlayer().getPosition()) {
                std::cout << board.getPlayer().getRepr();
                rendered = true;
            }

            // Render buildings
            if (!rendered) {
                for (const auto& building : board.getBuildings()) {
                    if (building->isColliding(pos)) {
                        std::cout << building->getRepr();
                        rendered = true;
                        break;
                    }
                }
            }

            // Render enemies
            if (!rendered) {
                for (const auto& enemy : board.getEnemies()) {
                    if (enemy->getPosition() == pos) {
                        std::cout << enemy->getRepr();
                        rendered = true;
                        break;
                    }
                }
            }

            if (!rendered) {
                std::cout << "·";
            }
        }
        std::cout << std::endl;
    }

    // Display resources
    std::cout << "\n╔════════════════ Resources ════════════════╗";
    std::cout << "\n║ Gold: " << std::setw(5) << board.getPlayer().getResources().getGold();
    std::cout << "  Elixir: " << std::setw(5) << board.getPlayer().getResources().getElixir();
    std::cout << "  TH Health: ";
    
    for (const auto& building : board.getBuildings()) {
        if (dynamic_cast<TownHall*>(building.get())) {
            std::cout << std::setw(3) << building->getHealth() << " ║";
            break;
        }
    }
    
    std::cout << "\n╠════════════════ Controls ══════════════════╣";
    std::cout << "\n║ Movement:  ↑ = Up    ↓ = Down             ║";
    std::cout << "\n║           ← = Left   → = Right            ║";
    std::cout << "\n╠═════════════ Building Controls ═══════════╣";
    std::cout << "\n║ G = Build Gold Mine (Cost: 100 Elixir)    ║";
    std::cout << "\n║ E = Build Elixir Collector (Cost: 100 Gold)║";
    std::cout << "\n║ W = Build Wall (Cost: 10 Gold)            ║";
    std::cout << "\n║ C = Collect Resources                      ║";
    std::cout << "\n╚═════════════════════════════════════════════╝";
}

int main() {
    Board board(40, 40);

    while (!board.isTownHallDestroyed()) {
        // Handle input
        if (kbhit()) {
            char ch = getch();
            
            switch (ch) {
                case 27: // ESC
                    break;
                case 'A': // Up Arrow
                    board.getPlayer().move(0, -1); 
                    break;
                case 'B': // Down Arrow
                    board.getPlayer().move(0, 1);
                    break;
                case 'D': // Left Arrow
                    board.getPlayer().move(-1, 0);
                    break;
                case 'C': // Right Arrow
                    board.getPlayer().move(1, 0);
                    break;
                default:
                    switch (toupper(ch)) {
                        case 'G': {
                            auto pos = board.getPlayer().getPosition();
                            if (board.getPlayer().build('G', pos.x, pos.y)) {
                                board.addBuilding(std::make_unique<GoldMine>(pos.x, pos.y));
                            }
                            break;
                        }
                        case 'E': {
                            auto pos = board.getPlayer().getPosition();
                            if (board.getPlayer().build('E', pos.x, pos.y)) {
                                board.addBuilding(std::make_unique<ElixirCollector>(pos.x, pos.y));
                            }
                            break;
                        }
                        case 'W': {
                            auto pos = board.getPlayer().getPosition();
                            if (board.getPlayer().build('W', pos.x, pos.y)) {
                                board.addBuilding(std::make_unique<Wall>(pos.x, pos.y));
                            }
                            break;
                        }
                        case 'C': {
                            auto building = board.getBuildingAt(board.getPlayer().getPosition());
                            if (building) {
                                board.getPlayer().collectFrom(building);
                            }
                            break;
                        }
                    }
            }
        }

        board.update();
        render(board);
        usleep(100000); // 100ms delay
    }

    std::cout << "\nGame Over! Town Hall destroyed!\n";
    return 0;
}
