#pragma once
#include "Plant.h"

class Guarana : public Plant {
    public:
        Guarana(int x, int y);
        void Collision(Organism* other);
        Organism* Child();
};