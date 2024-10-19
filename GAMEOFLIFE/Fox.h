#pragma once
#include "Animal.h"
#include <random>

class Fox : public Animal {
    public:
        Fox(int x, int y);
        void Action();
        Fox* Child();
};