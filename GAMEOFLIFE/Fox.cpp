#include "Fox.h"
#include "Animal.h"
#include "World.h"

Fox::Fox(int x, int y) : Animal('^', 3, x, y, 3, 7) {
}

void Fox::Action() {

	AddAge();

	std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> range(0, 3);
	int move = range(eng);

	pair<int, int> newpos;

	while (move <= 8) {
		newpos = { GetX() + moves[move%4][0], GetY() + moves[move%4][1] };
		if (world->GetOrganism(newpos) == nullptr) {
			if (SetPos(newpos, false))
				break;
		}
		else if(world->GetOrganism(newpos)->GetStrength()<=GetStrength()){
			if (SetPos(newpos, false))
				break;
		}
		else if(world->GetOrganism(newpos)->GetStrength()>GetStrength()){
			world->AddLog(this, "avoided a stronger enemy", 1);
		}
		move++;
	}
}

Fox* Fox::Child() {
	return new Fox(*this);
}