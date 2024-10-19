#pragma once
#include "Plant.h"

class DeadlyNightshade : public Plant {
    public:
        DeadlyNightshade(int x, int y);
        void Collision(Organism* other);
        Organism* Child();
};