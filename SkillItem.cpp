#include "SkillItem.hpp"
using namespace std;

SkillItem::SkillItem(Skill s, int j){
    skill = s;
    jumlah = j;
}

boolean SkillItem::operator==(const SkillItem s){
    return skill==s.skill;
}

Skill SkillItem::getSkill(){
    return skill;
}

int SkillItem::getJumlah(){
    return jumlah;
}

void SkillItem::add(int n){
    jumlah += n;
}
