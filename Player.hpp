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
    bool addEngimon(Engimon);
    bool addSkillItem(SkillItem);
    void showEngimonList();
    void showSkillItemList();
    void showActiveEngimon();
    void setActiveEngi(int);
    void petEngi();
    //int checkBattle(Engimon e[]);
    void breedEngimon(Engimon& A, Engimon& B);
    bool battle(Engimon e);
    bool lose();

};

#endif
