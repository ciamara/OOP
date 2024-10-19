#include "Dandelion.h"

Dandelion::Dandelion(int x, int y): Plant('*', 8, x, y, 0,  0) {
}

void Dandelion::Action() {
	for (int i = 0; i < 3; i++) {
		Plant::Action();
	}
	SetAge(GetAge()-2);
}

Organism* Dandelion::Child() {
	return new Dandelion(*this);
}