#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Position.hpp"
#include "SkillItem.hpp"
#include "Engimon.hpp"
using namespace std;
#include <string>
#include <vector>

class Player
{
private:
    Position playerPos;
    vector<Engimon> inventoryE;
    vector<SkillItem> inventoryS;
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
    void setActiveEngi(int);
    void petEngi();
    //int checkBattle(Engimon e[]);
    // void showActiveEngimon();
    // void showSkillItem();
    void breedEngimon(Engimon& A, Engimon& B);
    // void battle();

};

#endif
