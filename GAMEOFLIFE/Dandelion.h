#pragma once
#include "Plant.h"

class Dandelion : public Plant {
	public:
        Dandelion(int x, int y);
        void Action();
        Organism* Child();
};