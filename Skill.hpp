#ifndef SKILL_HPP
#define SKILL_HPP
using namespace std;
#include <vector>
#include <string>

enum Element { None, Fire, Water, Electric, Ground, Ice };

class Skill {

    private:
        string skillName;
        int basePower;
        int masteryLevel;
        vector<Element> elements;
    public:
        Skill();
        Skill(string, int, int, Element);
        Skill(string, int, int, vector<Element>);
        string getSkillName();
        int getBasePower();
        int getMasteryLevel();
        vector<Element> getElement();
        void masteryLevelUp();
        bool operator==(const Skill)const;
};

#endif
