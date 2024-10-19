#include "SosnowskyHogweed.h"
#include "World.h"
#include "Animal.h"

SosnowskyHogweed::SosnowskyHogweed(int x, int y) : Plant('$', 11, x, y, 10, 0) {
}

void SosnowskyHogweed::Action() {

	Plant::Action();

	for (int i = 0; i < 4; i++) {

		auto proximity = world->GetOrganism({ GetX() + moves[i][0], GetY() + moves[i][1]});

		if (proximity != nullptr) {
			bool animal = dynamic_cast<Animal*>(proximity);
			if (animal) {
				world->AddLog(this, "poisoned an animal in its proximity", 2);
				proximity->Kill();
			}
		}
	}
}

void SosnowskyHogweed::Collision(Organism* other) {
	world->AddLog(this, "poisoned an animal and died", 2);
	other->Kill();
	Kill();
}

Organism* SosnowskyHogweed::Child() {
	return new SosnowskyHogweed(*this);
}