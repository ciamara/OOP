#pragma once
#include "Organism.h"
#include <typeinfo>
#include <random>

class Animal : public Organism {
    public:
        Animal(char icon, int colornum, int x, int y, int strength, int initiative);
        virtual void Action();
        virtual void Collision(Organism* other);
};