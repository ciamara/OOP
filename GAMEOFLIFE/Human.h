#pragma once
#include <utility>

#include "Animal.h"

class Human : public Animal {
	private:
		int ability;
		pair<int,int> nextmove;
		const int range[8][2] = {{0,1},{1,0},{0,-1},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};
	public:
		Human(int x, int y);
		void Action();
		bool NextMove(pair<int,int> nextmove);
		void UseAbility();
		string Data();
		void SetAbility(int ability);
		Human* Child();
};