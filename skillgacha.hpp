#ifndef SKILLGACHA_HPP
#define SKILLGACHA_HPP
#include "Skill.hpp"
#include <string>
#include <vector>
using namespace std;

class skillgacha
{
private:
    vector<Skill> skillDB;
public:
    skillgacha();
    ~skillgacha();
    Skill getRandomSkill(Element e1, Element e2);
    vector<Skill> getSkillGen(Element e1, Element e2);
};


#endif