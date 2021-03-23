#ifndef SKILLITEM_HPP
#define SKILLITEM_HPP
#include "Skill.hpp"
#include "Engimon.hpp"
#include <string>
using namespace std;

class SkillItem{
protected:
    Skill skill;
    int jumlah;
public:
    SkillItem(Skill, int);

    bool operator==(const SkillItem);
    Skill getSkill();
    int getJumlah();
    void add(int);
    void learnSkill(Engimon& e);
};
#endif