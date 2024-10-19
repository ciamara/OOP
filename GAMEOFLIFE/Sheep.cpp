#include "Sheep.h"

Sheep::Sheep(int x, int y) : Animal('o', 2, x, y, 4, 4) {
}

Sheep* Sheep::Child() {
    return new Sheep(*this);
}