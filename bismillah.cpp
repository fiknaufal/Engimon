#include <iostream>
#include <string>
#include "Engimon.hpp"
#include "Position.hpp"
#include "Skill.hpp"
#include "SkillItem.hpp"

int main(){
    Firemon f("babang", "ayah", "ibu", "Firemon", "Firemon", 0, -1, -1);
    Watermon w("Squirtle", "a", "b", "Watermon", "Watermon", 0, -1, -1);

    f.printData();
    w.printData();
    return 0;
}