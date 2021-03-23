#include "SkillItem.hpp"
using namespace std;

Skill::Skill() {
    skillName = "Stand still";
    basePower = 0;
    masteryLevel = 1;
    elements.push_back("Fire");
    elements.push_back("Water");
    elements.push_back("Electric");
    elements.push_back("Ground");
    elements.push_back("Ice");
}

Skill::Skill(string sName, int bPower, int mLevel, string elmt) {
    skillName = sName;
    basePower = bPower;
    masteryLevel = mLevel;
    elements.push_back(elmt);
}

Skill::Skill(string sName, int bPower, int mLevel, vector<string> elmts) {
    skillName = sName;
    basePower = bPower;
    masteryLevel = mLevel;
    
    for (int i = 0; i < elmts.size(); i++) {
        elements.push_back(elmts[i]);
    }
}

string Skill::getSkillName() {
    return skillName;
} 

int Skill::getBasePower() {
    return basePower;
}

int Skill::getMasteryLevel() {
    return masteryLevel;
}

vector<string> Skill::getElement() {
    return elements;
}

bool Skill::operator==(const Skill s) {
    return skillName == s.skillName;
}