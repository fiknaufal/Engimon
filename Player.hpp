#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Position.hpp"
using namespace std;
#include <string>

class Player
{
private:
    Position playerPos;
    // MyEngimon* myEngimon;
    // int maxEngimon;
    // int banyakEngimon;
    // int idActiveEngimon;
public:
    Player();
    ~Player();

    void Move(const string &s);
    Position& getPlayerPos();
    // void showEngimonList();
    // void showActiveEngimon();
    // void showSkillItem();
    // void breedEngimon();
    // void battle();

};

#endif