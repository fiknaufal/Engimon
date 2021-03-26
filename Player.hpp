#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Position.hpp"
#include "SkillItem.hpp"
#include "Engimon.hpp"
#include "Inventory.hpp"
using namespace std;
#include <string>
#include <vector>

class Player
{
private:
    Position playerPos;
    Inventory<Engimon> inventoryE;
    Inventory<SkillItem> inventoryS;
    int maxInv;
    // int banyakEngimon;
    int idActiveEngimon;
public:
    Player();
    ~Player();

    void Move(const string &s);
    void MoveActiveEngi();
    Position& getPlayerPos();
    int getInvCount();
    Position getActivePos();
    bool addEngimon(Engimon);
    bool addSkillItem(SkillItem);
    void showEngimonList();
    void showSkillItemList();
    void showActiveEngimon();
    void showEngimon(int idx);
    void setActiveEngi(int);
    void petEngi();
    void useSkillItem(int idxsi, int idxengi);
    //int checkBattle(Engimon e[]);
    void breedEngimon(int idxA, int idxB);
    bool battle(Engimon e);
    bool lose();
    void updateSkillItem();

};

#endif
