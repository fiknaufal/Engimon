#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Position.hpp"
#include "SkillItem.hpp"
using namespace std;
#include <string>
#include <vector>

class Player
{
private:
    Position playerPos;
    vector<Engimon> inventoryE;
    vector<SkillItem> inventoryS;
    // MyEngimon* myEngimon;
    int maxInv;
    // int banyakEngimon;
    // int idActiveEngimon;
public:
    Player();
    ~Player();

    void Move(const string &s);
    Position& getPlayerPos();
    int getInvCount();
    boolean addEngimon(Engimon);
    boolean addSkillItem(SkillItem);
    void showEngimonList();
    void showSkillItemList();
    // void showActiveEngimon();
    // void showSkillItem();
    // void breedEngimon();
    // void battle();

};

#endif
