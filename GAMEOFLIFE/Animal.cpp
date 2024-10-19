#include <ncurses.h>
using namespace std;

#include "Animal.h"
#include "World.h"

Animal::Animal(char icon, int colornum, int x, int y, int strength, int initiative) : Organism(icon, colornum, x, y, strength, initiative) {
}

void Animal::Action() {

	std::vector<Organism*> organisms = world->GetOrganisms();

	AddAge();

    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> range(0, 3);

	int move = range(eng);
	
	while (!SetPos({ GetX()+moves[move][0], GetY()+moves[move][1] }, false)) {
		move++;
		move %= 4;
	}
}

void Animal::Collision(Organism *other)
{
	if(this==other){
		return;
	}
	if (typeid(*this) == typeid(*other)) {


		if(GetAge()<15||other->GetAge()<15){
			return;
		}

		auto child = dynamic_cast<Animal*>(this->Child());

		if (child != nullptr) {
			std::random_device rd;
			std::mt19937 eng(rd());
			std::uniform_int_distribution<> range(0, 3);

			int pick = range(eng);

			while (!child->SetPos({GetX()+moves[pick%4][0], GetY()+moves[pick%4][1]}, true)) {

				pick++;

				if (pick > 8) {
					world->AddLog(this, "no space for child", 1);
					child->Kill();
					return;
				}
			}
			world->AddLog(this, "baby is born", 1);
				
		}
	}
	else if (RunAway() || other->RunAway()) {
		return;
	}
	else if (GetStrength() > other->GetStrength()) {

		world->AddLog(this, "perseveres", 1);
		other->Kill();
	}
	else if (GetStrength() < other->GetStrength()) {

		world->AddLog(this, "dies", 1);
		Kill();
	}
	else {
		world->AddLog(this, "perseveres", 1);
		other->Kill();
	}
}
