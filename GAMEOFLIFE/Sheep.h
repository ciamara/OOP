#pragma once
#include "Animal.h"

class Sheep : public Animal {
    public:
        Sheep(int x, int y);
        Sheep* Child();
};