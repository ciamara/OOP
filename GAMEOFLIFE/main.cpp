#include <ncurses.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <inttypes.h>
using namespace std;

#include "World.h"
#include "Human.h"

#define WOLF 1 
#define SHEEP 2 
#define FOX 3 
#define TURTLE 4 
#define ANTELOPE 5 
#define CYBERSHEEP 6 
#define GRASS 7
#define DANDELION 8
#define GUARANA 9
#define DEADLYNIGHTSHADE 10
#define SOSNOWSKYHOGWEED 11
#define HUMAN 12
#define NOTHING 13


int main() {

    int bot, right;

    cout<<"Input width"<<endl;
    cin>>right;
    cout<<"Input height"<<endl;
    cin>>bot;


    initscr();
    cbreak();
    noecho();
    curs_set(0);

    start_color();
    init_pair(WOLF, COLOR_WHITE, COLOR_BLACK);
    init_pair(SHEEP, COLOR_BLACK, COLOR_WHITE);
    init_pair(FOX, COLOR_YELLOW, COLOR_RED);
    init_pair(TURTLE, COLOR_GREEN, COLOR_CYAN);
    init_pair(ANTELOPE, COLOR_WHITE, COLOR_YELLOW);
    init_pair(CYBERSHEEP, COLOR_RED, COLOR_WHITE);
    init_pair(GRASS, COLOR_GREEN, COLOR_GREEN);
    init_pair(DANDELION, COLOR_YELLOW, COLOR_GREEN);
    init_pair(GUARANA, COLOR_RED, COLOR_GREEN);
    init_pair(DEADLYNIGHTSHADE, COLOR_BLUE, COLOR_GREEN);
    init_pair(SOSNOWSKYHOGWEED, COLOR_BLACK, COLOR_GREEN);
    init_pair(HUMAN, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(NOTHING, COLOR_BLACK, COLOR_BLACK);  

    WINDOW *win = newwin(30, 130, 1,10);

    World* world = World::GetCurrent(right, bot);

    char ch;

    clear();
    world->SpawnOrganisms();
    world->DrawWorld();

    do {

        ch = getch();

        Human* human = dynamic_cast<Human*>(world->GetHuman());

        switch (ch) {
            case 'w':
                if(!human->NextMove({ 0, -1 })){
                    continue;
                }
                break;
            case 'd':
                if(!human->NextMove({+1, 0})) {
                    continue;
                }
                break;
            case 's':
                if(!human->NextMove({0, +1})) {
                    continue;
                }
                break;
            case 'a':
                if(!human->NextMove({-1, 0})) {
                    continue;
                }
                break;
            case 'x':
                human->UseAbility();
                continue;
            case 'o':
                world->Save();
                continue;
            case 'l':
                world = World::Load();
                world->DrawWorld();
                continue;
            case 'r':
                break;
            default:
                continue;
        }
        if(ch!='r'){
            continue;
        }
        world->DoRound();
        world->DrawWorld();
    } while (ch!='q');

    endwin();
    exit(0);
    
return 0;
}