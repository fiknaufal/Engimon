#include "SkillItem.hpp"
#include <iostream>
using namespace std;

SkillItem::SkillItem(Skill s, int j){
    skill = s;
    jumlah = j;
}

bool SkillItem::operator==(const SkillItem s){
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

void SkillItem::learnSkill(Engimon& e){
    bool can = false;
    for (int i = 0; i < skill.getElement().size(); i++){
        if (skill.getElement()[i] == e.getElement1() || skill.getElement()[i] == e.getElement2()){
            can = true;
        }
    }
    if (can){
        if (e.addSkill(skill)){
            jumlah = jumlah-1;
        }
    }
    else{
        cout << "Gagal mempelajari skill.\nEngimon memiliki elemen berbeda!" << endl;
    }
}
