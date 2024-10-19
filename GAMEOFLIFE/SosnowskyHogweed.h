#pragma once
#include "Plant.h"

class SosnowskyHogweed : public Plant {
    public:
        SosnowskyHogweed(int x, int y);
        void Action();
        void Collision(Organism* other);
        Organism* Child();
};