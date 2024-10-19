#pragma once
#include <random>

#include "Organism.h"
#include "World.h"

class Plant : public Organism {
    public:
        Plant(char icon, int colornum, int x, int y, int strength, int initiative);
        virtual void Action();
        virtual void Collision(Organism* other);
};