#include "Entity.h"

Entity::Entity(int x, int y, const std::string& r, int h)
    : position(x, y), repr(r), health(h) {}

void Entity::takeDamage(int amount) {
    health -= amount;
}

bool Entity::isDestroyed() const {
    return health <= 0;
}

Position Entity::getPosition() const { return position; }
std::string Entity::getRepr() const { return repr; }
int Entity::getHealth() const { return health; }
