#include "Human.h"
#include "World.h"

Human::Human(int x, int y) : Animal('|', 12, x, y, 5, 4) {
	ability = 0;
	nextmove = {0, 0};
}

void Human::Action() {

	mvprintw(7, 2, "BURNING FLAMES: %d", ability);
	refresh();

	AddAge();

	if(ability>0){
		ability--;
	}

	if(ability>=5){

		for (int i = 0; i < 8; i++) {
			auto proximity = world->GetOrganism({ GetX() + moves[i][0], GetY() + moves[i][1]});

			if (proximity != nullptr) {
				bool ahuman = dynamic_cast<Human*>(proximity);
				if(!ahuman){
					world->AddLog(this, "poisoned an organism in his proximity", 1);
					proximity->Kill();
				}
				
			}
		}
	}
	
	SetPos({GetX()+nextmove.first, GetY()+nextmove.second}, false);

	if(ability>=5){

		for (int i = 0; i < 0; i++) {
			auto proximity = world->GetOrganism({ GetX() + moves[i][0], GetY() + moves[i][1]});

			if (proximity != nullptr) {
				
				world->AddLog(this, "poisoned an organism in his proximity", 1);
				proximity->Kill();
				
			}
		}
	}

	nextmove = { 0,0 };
}

bool Human::NextMove(pair<int,int> nextmove) {
	if((GetX()+nextmove.first)<world->GetLeft() || (GetX()+nextmove.first)>=(world->GetRight()+world->GetLeft()-1) || (GetY()+nextmove.second)<world->GetTop() || (GetY()+nextmove.second)>=(world->GetBot()+world->GetTop()-1)) {
        return false;
    }
	this->nextmove = nextmove;
	return true;
}

void Human::UseAbility() {
	if (ability == 0) {
		ability = 10;
		world->AddLog(this, "burning flames activated", 1);
	}
}

string Human::Data(){

	string data = Animal::Data();
	data += "|" + to_string(ability);
	return data;
}

void Human::SetAbility(int ability){
	this->ability = ability;
}

Human* Human::Child() {
	return nullptr;
}

