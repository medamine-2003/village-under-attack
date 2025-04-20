#include "Board.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include "Buildings/ResourceGenerator.h"
#include "Buildings/GoldMine.h"
#include "Buildings/ElixirCollector.h"

Board::Board(int sizeX, int sizeY) : sizeX(sizeX), sizeY(sizeY) {}

Board::~Board() {
    for (Building* b : buildings) delete b;
    for (Entity* e : entities) delete e;
}

bool Board::placeBuilding(Building* building, const Resources& resources) {
    if (building->canPlace(resources)) {
        buildings.push_back(building);
        return true;
    }
    return false;
}

void Board::placeEntity(Entity* entity) {
    entities.push_back(entity);
}

void Board::moveEntity(Entity* entity, int dx, int dy) {
    entity->move(dx, dy);
    Position pos = entity->getPosition();
    pos.x = std::max(0, std::min(pos.x, sizeX - 1));
    pos.y = std::max(0, std::min(pos.y, sizeY - 1));
}

Building* Board::findNearestBuilding(Position pos) const {
    Building* nearest = nullptr;
    double minDist = std::numeric_limits<double>::max();
    for (Building* b : buildings) {
        Position bp = b->getPosition();
        double dist = std::sqrt(std::pow(bp.x - pos.x, 2) + std::pow(bp.y - pos.y, 2));
        if (dist < minDist) {
            minDist = dist;
            nearest = b;
        }
    }
    return nearest;
}

std::vector<Building*>& Board::getBuildings() {
    return buildings;
}

std::vector<Entity*>& Board::getEntities() {
    return entities;
}

void Board::render() const {
    std::vector<std::vector<std::string>> grid(sizeY, std::vector<std::string>(sizeX, "."));

    for (Building* b : buildings) {
        Position pos = b->getPosition();
        std::string repr = b->getRepr();
        ResourceGenerator* rg = dynamic_cast<ResourceGenerator*>(b);
        if (rg && rg->isFullGenerator()) {
            if (dynamic_cast<GoldMine*>(b)) repr = "🪙"; // Emoji 🪙
            else if (dynamic_cast<ElixirCollector*>(b)) repr = "🧴"; // Emoji 🧴
        }
        for (int y = pos.y; y < pos.y + b->getSizeY() && y < sizeY; ++y) {
            for (int x = pos.x; x < pos.x + b->getSizeX() && x < sizeX; ++x) {
                grid[y][x] = repr;
            }
        }
    }

    for (Entity* e : entities) {
        Position pos = e->getPosition();
        if (pos.x >= 0 && pos.x < sizeX && pos.y >= 0 && pos.y < sizeY) {
            grid[pos.y][pos.x] = e->getRepr();
        }
    }

    for (const auto& row : grid) {
        for (const auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }

    Player* player = nullptr;
    for (Entity* e : entities) {
        if (dynamic_cast<Player*>(e)) {
            player = dynamic_cast<Player*>(e);
            break;
        }
    }
    if (player) {
        std::cout << "Gold: " << player->getResources().gold
                  << " Elixir: " << player->getResources().elixir << std::endl;
    }
}
