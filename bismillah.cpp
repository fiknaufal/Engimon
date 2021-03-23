#include <iostream>
#include <string>
#include "Engimon.hpp"
#include "Position.hpp"
#include "Skill.hpp"
#include "SkillItem.hpp"

int main(){
    Firemon f("babang", "ayah", "ibu", "Firemon", "Firemon", 0, -1, -1);
    Watermon w("Squirtle", "a", "b", "Watermon", "Watermon", 0, -1, -1);
    Skill s("Splash", 100, 1, Water);

    SkillItem ski(s, 5);
    ski.learnSkill(w);
    ski.learnSkill(w);
    ski.learnSkill(f);
    w.printData();
    f.printData();
    cout << ski.getJumlah() << endl;
    return 0;
}