#include "Guarana.h"
#include "World.h"

Guarana::Guarana(int x, int y) : Plant('%', 9, x, y, 0, 0) {
}

void Guarana::Collision(Organism* other) {
	world->AddLog(this, "strengthens an animal", 1);
	other->Strengthen();
	Kill();
}

Organism* Guarana::Child() {
	return new Guarana(*this);
}