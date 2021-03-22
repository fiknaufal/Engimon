#ifndef SKILLITEM_HPP
#define SKILLITEM_HPP
#include "Skill.hpp"
using namespace std;
#include <string>

class SkillItem{
protected:
    Skill skill;
    int jumlah;
public:
    SkillItem(Skill, int);
    ~SkillItem();

    boolean operator==(const SkillItem);
    Skill getSkill();
    int getJumlah();
    void add(int);
};
