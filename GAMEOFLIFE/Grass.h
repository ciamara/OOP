#pragma once
#include "Plant.h"

class Grass : public Plant {
    public:
        Grass(int x, int y);
        Organism* Child();
};