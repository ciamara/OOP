#pragma once
#include "Animal.h"
#include <random>

class Antelope : public Animal {
	private:
        const int moves[8][2] = {{0,2},{2,0},{0,-2},{-2,0},{1,1},{1,-1},{-1,1},{-1,-1}};
    public:
        Antelope(int x, int y);
        void Action();
        bool RunAway();
        Antelope* Child();
};