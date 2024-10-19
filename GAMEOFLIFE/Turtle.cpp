#include "Turtle.h"
#include "World.h"

Turtle::Turtle(int x, int y): Animal('@', 4, x, y, 2, 1) {
}

void Turtle::Action() {

    AddAge();

    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> chance(0, 4);

	int movechance = chance(eng);

    if (movechance==4) {
        world->AddLog(this, "managed to move", 1);
        Animal::Action();
    }
}

void Turtle::Collision(Organism* other) {
    if (other->GetStrength() < 5 && typeid(*this) != typeid(*other)) {
        world->AddLog(this, "survived the attack", 1);
        other->RevertMove();
    }
    else if (other->GetStrength() >= 5 && typeid(*this) != typeid(*other)){
        world->AddLog(this, "did not block the attack", 1);
        Animal::Collision(other);
    }
}

Turtle* Turtle::Child() {
    return new Turtle(*this);
}