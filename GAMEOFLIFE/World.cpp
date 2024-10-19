#include "World.h"
#include "Organism.h"
#include "Human.h"
#include "Grass.h"
#include "Dandelion.h"
#include "Guarana.h"
#include "DeadlyNightshade.h"
#include "SosnowskyHogweed.h"
#include "Wolf.h"
#include "Sheep.h"
#include "Fox.h"
#include "Turtle.h"
#include "Antelope.h"
#include <iostream>
#include <string>
#include <fstream>

#define NOTHING 13
#define OCCUPIED 1

World::World(int right, int bot){
    this->right = right;
    this->bot = bot;
    round = 0;
    logs = 0;
    animals = 0;
    human = nullptr;
}

World* World::current = nullptr;

World* World::GetCurrentWorld() {
    return current;
}

World* World::GetCurrent(int right, int bot) {
    if (current != nullptr)
        delete current;
    current = new World(right, bot);
        return current;
}

void World::DrawWorld() const {

    mvprintw(0, 3, "GAME OF LIFE, 2024, Tamara Mruk, s197584");
    mvprintw(3, 20, "OO");
    move(3, 22);
    hline('-', right);
    mvprintw(3, right+left, "OO");
    move(4, 20);
    vline('|', bot);
    mvprintw(4+bot, 20, "OO");
    move(4, 21);
    vline('|', bot);
    move(4+bot, 22);
    hline('-', right);
    mvprintw(4+bot, 22+right, "OO");
    move(4, 22+right);
    vline('|', bot);
    move(4, 23+right);
    vline('|', bot);
    mvprintw(4, 55, "Press [R] to move to the next round");
    mvprintw(6, 55, "Press [X] to use burning flames as the human");
    mvprintw(8, 55, "Use WASD to prepare a move for the human");
    mvprintw(10, 55, "Press [O] to save game, and [L] to load game");
    mvprintw(14, 55, "LAST EVENT:");

    mvprintw(3, 2, "ROUND: %d", round);
    mvprintw(5, 2, "ORGANISMS: %d", animals);

    for (Organism* o : organisms)
    {
        if(o->GetStrength()>-1)
		    o->Draw();
    }

    refresh();
}

void World::DoRound() {

    round++;

    for(int i=4; i<4+bot; i++){
        for(int j=22; j<22+right; j++){
            attron(COLOR_PAIR(NOTHING));
            mvaddch(i, j, ' ');
            attroff(COLOR_PAIR(NOTHING));
        }
    }
    attron(COLOR_PAIR(NOTHING));
    mvaddch(3, 9, ' ');
    attroff(COLOR_PAIR(NOTHING));
    attron(COLOR_PAIR(NOTHING));
    mvaddch(3, 10, ' ');
    attroff(COLOR_PAIR(NOTHING));
    attron(COLOR_PAIR(NOTHING));
    mvaddch(5, 13, ' ');
    attroff(COLOR_PAIR(NOTHING));
    attron(COLOR_PAIR(NOTHING));
    mvaddch(5, 14, ' ');
    attroff(COLOR_PAIR(NOTHING));
    attron(COLOR_PAIR(NOTHING));
    mvaddch(7, 18, ' ');
    attroff(COLOR_PAIR(NOTHING));
    attron(COLOR_PAIR(NOTHING));
    mvaddch(7, 19, ' ');
    attroff(COLOR_PAIR(NOTHING));

    std::sort(organisms.begin(), organisms.end(), Organism::CompareInitiativeAndAge);

    for (Organism* o : organisms) {
        if (o->GetStrength() > -1) {
            o->Action();
        }
        else {
            break;
        }
	}
}

void World::AddOrganism(Organism* organism) {
    organisms.push_back(organism);
    SetAnimals(GetAnimals()+1);
}

void World::SpawnOrganisms() {

    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distributionHorizontal(left, left+right-1);
    std::uniform_int_distribution<> distributionVertical(top, top+bot-1);

    int randH=distributionHorizontal(eng), randV=distributionVertical(eng);

    int spaces[20][20]={0};

    spaces[top+(bot/2)][left+(right/2)]=OCCUPIED;


    human = new Human(left+(right/2), top+(bot/2));
    

    while (spaces[randV-top][randH-left]==OCCUPIED) {
        randH = distributionHorizontal(eng);
        randV = distributionVertical(eng);
    }
    spaces[randV-top][randH-left]=OCCUPIED;
    new Grass(randH, randV);


    while (spaces[randV-top][randH-left]==OCCUPIED) {
        randH = distributionHorizontal(eng);
        randV = distributionVertical(eng);
    }
    spaces[randV-top][randH-left]=OCCUPIED;
    new Dandelion(randH, randV);


    while (spaces[randV-top][randH-left]==OCCUPIED) {
        randH = distributionHorizontal(eng);
        randV = distributionVertical(eng);
    }
    spaces[randV-top][randH-left]=OCCUPIED;
    new Guarana(randH, randV);


    while (spaces[randV-top][randH-left]==OCCUPIED) {
        randH = distributionHorizontal(eng);
        randV = distributionVertical(eng);
    }
    spaces[randV-top][randH-left]=OCCUPIED;
    new DeadlyNightshade(randH, randV);
    

    while (spaces[randV-top][randH-left]==OCCUPIED) {
        randH = distributionHorizontal(eng);
        randV = distributionVertical(eng);
    }
    spaces[randV-top][randH-left]=OCCUPIED;
    new SosnowskyHogweed(randH, randV);


    while (spaces[randV-top][randH-left]==OCCUPIED) {
        randH = distributionHorizontal(eng);
        randV = distributionVertical(eng);
    }
    spaces[randV-top][randH-left]=OCCUPIED;
    new Wolf(randH, randV);

    // while (spaces[randV-top][randH-left]==OCCUPIED) {
    //     randH = distributionHorizontal(eng);
    //     randV = distributionVertical(eng);
    // }
    // spaces[randV-top][randH-left]=OCCUPIED;
    // new Wolf(randH, randV);



    while (spaces[randV-top][randH-left]==OCCUPIED) {
        randH = distributionHorizontal(eng);
        randV = distributionVertical(eng);
    }
    spaces[randV-top][randH-left]=OCCUPIED;
    new Sheep(randH, randV);

    while (spaces[randV-top][randH-left]==OCCUPIED) {
        randH = distributionHorizontal(eng);
        randV = distributionVertical(eng);
    }
    spaces[randV-top][randH-left]=OCCUPIED;
    new Sheep(randH, randV);


    while (spaces[randV-top][randH-left]==OCCUPIED) {
        randH = distributionHorizontal(eng);
        randV = distributionVertical(eng);
    }
    spaces[randV-top][randH-left]=OCCUPIED;
    new Fox(randH, randV);


    while (spaces[randV-top][randH-left]==OCCUPIED) {
        randH = distributionHorizontal(eng);
        randV = distributionVertical(eng);
    }
    spaces[randV-top][randH-left]=OCCUPIED;
    new Turtle(randH, randV);


    while (spaces[randV-top][randH-left]==OCCUPIED) {
        randH = distributionHorizontal(eng);
        randV = distributionVertical(eng);
    }
    spaces[randV-top][randH-left]=OCCUPIED;
    new Antelope(randH, randV);
}

int World::GetTop() {
    return top;
}

int World::GetLeft() {
    return left;
}

int World::GetBot() {
    return bot;
}

int World::GetRight() {
    return right;
}

int World::GetRound() {
    return round;
}

int World::GetLogs() {
    return logs;
}

void World::SetLogs(int amount){
    logs = amount;
}

void World::SetAnimals(int amount){
    animals = amount;
}

int World::GetAnimals(){
    return animals;
}

Organism* World::GetOrganism(pair<int,int> pos)
{
    if(pos.first < GetLeft() || pos.first >= (GetRight()+GetLeft()-1) || pos.second < GetTop() || pos.second >= (GetBot()+GetTop()-1)) {
        return nullptr;
    }
    for (Organism* o : organisms) {
        if (o->GetX() == pos.first && o->GetY() == pos.second) {
			return o;
		}
	}
	return nullptr;
}

Organism* World::GetHuman() {
    return human;
}

std::vector<Organism*> World::GetOrganisms() {
    return organisms;
}

void World::ClearLogs(){
    for(int i=16; i<40; i++){
        for(int j=55; j<130; j++){
            attron(COLOR_PAIR(NOTHING));
            mvaddch(i, j, ' ');
            attroff(COLOR_PAIR(NOTHING));
        }
    }
}

void World::AddLog(Organism* source, string log, int cut){ 
    if (GetLogs()>9){
        ClearLogs();
        SetLogs(0);
    }
    string creature = typeid(*source).name();
    log = creature + " " + log;
    if(cut==2){
        log = log.substr(2,log.length());
    }
    else{
        log = log.substr(1,log.length());
    }
    mvaddstr(16+(GetLogs()*2), 55, log.c_str());
    SetLogs(GetLogs()+1);
}

void World::AddInfo(string log){
    if (GetLogs()>9){
        ClearLogs();
        SetLogs(0);
    }

    mvaddstr(16+(GetLogs()*2), 55, log.c_str());
    SetLogs(GetLogs()+1);
}

void World::Save(){

    ofstream file;

    file.open("save.txt");

    file << right <<endl;
    file << bot <<endl;
    file << round <<endl;
    
    for (Organism* o : organisms){
        if (o->GetStrength() > -1) {
			file << o->Data() << endl;
		}
	}
    file.close();

    AddInfo("Saved the game");
}

World* World::Load(){

    delete current;

    current = nullptr;

    ifstream file;
    file = ifstream("save.txt");

    int right, bot, round, ability, age;

    string line;

    getline(file, line);
    right = stoi(line);

    getline(file, line);
    bot = stoi(line);

    getline(file, line);
    round = stoi(line);

    current = new World(right, bot);
    current->round = round;
    current->logs = 0;
    current->animals = 0;

    while (getline(file, line, '|')) {
        Organism* o = nullptr;
        if (line.size()<2){
            continue;
        }

        string name = line.substr(line.find(' ')+1, line.length());
        getline(file, line, '|');
        int x = stoi(line);
        getline(file, line, '|');
        int y = stoi(line);
        getline(file, line, '|');
        int strength = stoi(line);
        if (name == "5Human") {
            o = new Human(x, y);
            current->human = o;
            getline(file, line, '|');
            age = stoi(line);
            getline(file, line);
            int ability = stoi(line);
            ((Human*)o)->SetAbility(ability);
        }
        else if(name=="4Wolf"){
            getline(file, line);
            age = stoi(line);
            o = new Wolf(x,y);
        }
        else if(name=="5Sheep"){
            getline(file, line);
            age = stoi(line);
            o = new Sheep(x,y);
        }
        else if(name=="3Fox"){
            getline(file, line);
            age = stoi(line);
            o = new Fox(x,y);
        }
        else if(name=="6Turtle"){
            getline(file, line);
            age = stoi(line);
            o = new Turtle(x,y);
        }
        else if(name=="8Antelope"){
            getline(file, line);
            age = stoi(line);
            o = new Antelope(x,y);
        }
        else if(name=="5Grass"){
            getline(file, line);
            age = stoi(line);
            o = new Grass(x,y);
        }
        else if(name=="9Dandelion"){
            getline(file, line);
            age = stoi(line);
            o = new Dandelion(x,y);
        }
        else if(name=="7Guarana"){
            getline(file, line);
            age = stoi(line);
            o = new Guarana(x,y);
        }
		else if(name=="16DeadlyNightshade"){
            getline(file, line);
            age = stoi(line);
            o = new DeadlyNightshade(x,y);
        }
		else if(name=="16SosnowskyHogweed"){
            getline(file, line);
            age = stoi(line);
            o = new SosnowskyHogweed(x,y);
        }
        o->SetStrength(strength);
        o->SetAge(age);
        current->ClearLogs();
	}
    file.close();
    return current;
}

World::~World(){
    for (auto o : organisms) {
        delete o;
    }
}