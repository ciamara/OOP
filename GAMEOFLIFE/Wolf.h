#pragma once
#include "Animal.h"

class Wolf : public Animal {
    public:
        Wolf(int x, int y);
        Wolf* Child();
};