#include "Organism.h"
#include "World.h"

Organism::Organism(char icon, int colornum, int x, int y, int strength, int initiative) {
    this->world = World::GetCurrentWorld();
	this->strength = strength;
	this->initiative = initiative;
	this->pos = { x, y };
    this->icon = icon;
    this->colornum = colornum;
	this->age = 0;
    if (world != nullptr) {
        world->AddOrganism(this);
    }
}

Organism::Organism(const Organism& o) {
	this->world = o.world;
	this->strength = o.strength;
	this->initiative = o.initiative;
	this->pos = o.pos;
    this->icon = o.icon;
    this->colornum = o.colornum;
	this->age = 0;
	world->AddOrganism(this);
}

bool Organism::RunAway() {
	return false;
}

void Organism::Kill() {

	pos = { -1, -1 };
	strength = -1;
	initiative = -1;

	world->SetAnimals(world->GetAnimals()-1);
}

void Organism::RevertMove()
{
	SetPos(pastpos, false);
}

int Organism::GetX() {
	return pos.first;
}

int Organism::GetY() {
	return pos.second;
}

int Organism::GetStrength() {
    return strength;
}

int Organism::GetInitiative() {
    return initiative;
}

int Organism::GetAge() {
    return age;
}

char Organism::GetIcon() {
    return icon;
}

void Organism::AddAge() {
	age += 1;
}

void Organism::SetAge(int amount){
	age = amount;
}

void Organism::Strengthen() {
    strength += 3;
}

void Organism::SetStrength(int amount){
	strength = amount;
}

void Organism::Draw() {
    attron(COLOR_PAIR(colornum));
    mvaddch(pos.second, pos.first, icon);
    attroff(COLOR_PAIR(colornum));
    refresh();
}

bool Organism::CompareInitiativeAndAge(Organism* a, Organism* b) {

	if(a->GetInitiative() > b->GetInitiative()){
		return 1;
	}
	else if (a->GetInitiative() < b->GetInitiative()){
		return 0;
	}
	else{
		if (a->GetAge() > b->GetAge()){
			return 1;
		}
		else{
			return 0;
		}
	}
}

bool Organism::SetPos(pair<int, int> pos, bool empty)
{
	if (pos.first < world->GetLeft() || pos.first > (world->GetRight()+world->GetLeft()-1) || pos.second < world->GetTop() || pos.second > (world->GetBot()+world->GetTop()-1)){
		return false;
	}
	if (empty && world->GetOrganism(pos) != nullptr){
		return false;
	}
	pastpos = this->pos;
	Organism* other = world->GetOrganism(pos);
	this->pos = pos;
	if (other != nullptr) {
		other->Collision(this);
	}
	return true;
}

string Organism::Data()
{
	string out = "";
	out += typeid(*this).name();
	out += "|";
	out += to_string(pos.first);
	out += "|";
	out += to_string(pos.second);
	out += "|";
	out += to_string(strength);
	out += "|";
	out += to_string(age);
	return out;
}
