#include "Plant.h"

Plant::Plant(char icon, int colornum, int x, int y, int strength, int initiative) : Organism(icon, colornum, x, y, strength, initiative) {
}

void Plant::Action() {

    AddAge();

    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> range(0, 3);
    std::uniform_int_distribution<> chance(0, 200);
    int chancetospread;

    chancetospread = chance(eng);

    if(chancetospread==0) {

        auto child = dynamic_cast<Plant*>(this->Child());

        int pick = range(eng);

        while (!child->SetPos({GetX() + moves[pick % 4][0], GetY() + moves[pick % 4][1] }, true)) {
			pick++;
			if (pick > 8) {
                if(this->GetStrength()>0){
                    world->AddLog(this, "has no place to spread", 2);
                }
                else{
                    world->AddLog(this, "has no place to spread", 1);
                }
				child->Kill();
				return;
			}
		}

        if(this->GetStrength()>0){
            world->AddLog(this, "spreads", 2);
        }
        else{
            world->AddLog(this, "spreads", 1);
        }
    }
}

void Plant::Collision(Organism* other)
{
	if(this==other){
        return;
    }
	if (GetStrength() >= other->GetStrength()) {
		world->AddLog(this, "killed the attacker", 1);
		other->Kill();
	}
	else if (GetStrength() < other->GetStrength()) {
		world->AddLog(this, "got eaten/destroyed", 1);
		Kill();
	}
}