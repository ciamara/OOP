#pragma once
#include <ncurses.h>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

#include "Organism.h"

class World {
    private:
        std::vector<Organism*> organisms;
        int top=4;
        int bot;
        int left=22;
        int right;
        int round;
        int logs;
        int animals;
        Organism* human;
        static World* current;
    public:
        World(int right, int bot);
        static World* GetCurrent(int right, int bot);
        static World* GetCurrentWorld();
        static World* Load();
        void DrawWorld() const;
        void SpawnOrganisms();
        int GetTop();
        int GetLeft();
        int GetRight();
        int GetBot();
        int GetRound();
        int GetLogs();
        void ClearLogs();
        void SetLogs(int amount);
        void SetAnimals(int amount);
        int GetAnimals();
        void AddLog(Organism* source, string log, int cut);
        void AddInfo(string log);
        Organism* GetOrganism(pair<int,int> pos);
        std::vector<Organism*> GetOrganisms();
        Organism* GetHuman();
        void DoRound();
        void Save();
        void AddOrganism(Organism* organism);
        ~World();
};