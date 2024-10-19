#include "Antelope.h"
#include "World.h"

Antelope::Antelope(int x, int y): Animal('&', 5, x, y, 4, 4) {
}

void Antelope::Action() {

	AddAge();

    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> range(0, 7);

	int move = range(eng);

	while (!SetPos({ GetX() + moves[move][0], GetY() + moves[move][1] }, false)) {
		move++;
		move %= 8;
	}
}

bool Antelope::RunAway() {

    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> chance(0, 1);

	bool runaway = chance(eng);

	if (runaway==1) {

		int move = 0;

		while (!SetPos({ GetX() + moves[move][0], GetY() + moves[move][1] }, true)) {
			move++;
			if (move == 8) {
				world->AddLog(this, "failed to run away", 1);
				return false;
			}
		}
		world->AddLog(this, "escaped", 1);
		return true;
	}
	return false;
}

Antelope* Antelope::Child()
{
	return new Antelope(*this);
}