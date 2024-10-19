#include "DeadlyNightshade.h"
#include "World.h"

DeadlyNightshade::DeadlyNightshade(int x, int y) : Plant('X', 10, x, y, 99, 0) {
}

void DeadlyNightshade::Collision(Organism* other) {
	world->AddLog(this, "poisoned an animal and died", 2);
	other->Kill();
	Kill();
}

Organism* DeadlyNightshade::Child() {
	return new DeadlyNightshade(*this);
}