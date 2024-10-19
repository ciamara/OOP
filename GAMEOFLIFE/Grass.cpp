#include "Grass.h"

Grass::Grass(int x, int y) : Plant(' ', 7, x, y, 0, 0) {
}

Organism* Grass::Child() {
    return new Grass(*this);
}