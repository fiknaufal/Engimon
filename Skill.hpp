#ifndef SKILL_HPP
#define SKILL_HPP
using namespace std;
#include <vector>

class Skill {
    private:
        string skillName;
        int basePower;
        int masteryLevel;
        vector<string> elements;
    public:
        Skill();
        Skill(string, int, int, string);
        Skill(string, int, int, vector<string>);
        string getSkillName();
        int getBasePower();
        int getMasteryLevel();
        vector<string> getElement();
        bool operator==(const Skill);
};

#endif
