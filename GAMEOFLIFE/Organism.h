#pragma once
using namespace std;
#include <typeinfo>
#include <string>

class World;

class Organism {
    protected:
        int strength;
        int initiative;
        int age;
        pair<int, int> pos;
	    pair<int,int> pastpos;
        char icon;
        int colornum;
        World* world;
        const int moves[4][2] = { {0,1},{1,0},{0,-1},{-1,0} };
    public:
        Organism(char icon, int colornum, int x, int y, int strength, int initiative);
        Organism(const Organism& o);
        virtual void Action()=0;
        virtual void Collision(Organism* other)=0;
        virtual Organism* Child()=0;
        virtual bool RunAway();
        void Draw();
        virtual string Data();
        int GetStrength();
        int GetInitiative();
        int GetAge();
        char GetIcon();
        void Kill();
        void Strengthen();
        void SetStrength(int amount);
        void AddAge();
        void SetAge(int amount);
        int GetX();
        int GetY();
        bool SetPos(pair<int, int> pos, bool empty);
        void RevertMove();
        static bool CompareInitiativeAndAge(Organism* a, Organism* b);
}; 