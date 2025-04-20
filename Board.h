#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include "Buildings/Building.h"
#include "Entities/Entity.h"
#include "Entities/Player.h"
#include "Entities/Enemies/Raider.h"

class Board {
private:
    int sizeX;
    int sizeY;
    std::vector<Building*> buildings;
    std::vector<Entity*> entities;

public:
    Board(int sizeX = 20, int sizeY = 20);
    ~Board();
    bool placeBuilding(Building* building, const Resources& resources);
    void placeEntity(Entity* entity);
    void moveEntity(Entity* entity, int dx, int dy);
    void render() const;
    Building* findNearestBuilding(Position pos) const;
    std::vector<Building*>& getBuildings();  // Ensure this declaration is present
    std::vector<Entity*>& getEntities();     // Ensure this declaration is present
};

#endif
