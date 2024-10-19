#pragma once
#include "Animal.h"
#include <random>
#include <typeinfo>

class Turtle : public Animal {
    public:
        Turtle(int x, int y);
        void Action();
        void Collision(Organism* other);
        Turtle* Child();
};