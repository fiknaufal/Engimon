#include "skillgacha.hpp"
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

skillgacha::skillgacha(){
    Skill s1("Pound", 1, 1, {Fire, Water, Ice, Ground, Electric});
    Skill s2("Fireball", 2, 1, {Fire, Ground});
    Skill s3("Aqua Tail", 2, 1, {Water, Ice});
    Skill s4("Thunder Bolt", 2, 1, {Electric, Water});
    Skill s5("Rock Blast", 2, 1, {Ground, Electric});
    Skill s6("Todoroki Strike", 2, 1, {Ice, Fire});
    Skill s7("Fire Tornado", 3, 1, {Fire, Electric, Ground});
    Skill s8("Blizzard", 3, 1, {Water, Ice, Ground});
    Skill s9("Banjir Bandang", 3, 1, {Water, Ground, Ice});

    skillDB = {s1, s2, s3, s4, s5, s6, s7, s8, s9};
}

skillgacha::~skillgacha(){}

Skill skillgacha::getRandomSkill(Element e1, Element e2){
    if (e2 == None){
        return skillDB[e1+1];
    }
    else{
        if (e2 == Electric){
            return skillDB[6];
        }else if (e2 == Ice){
            return skillDB[7];
        }else{
            return skillDB[8];
        }
    }
}

vector<Skill> skillgacha::getSkillGen(Element e1, Element e2){
    vector<Skill> temp;
    if (e2 == None){
        if (e1 == Fire){
            temp = {skillDB[0], skillDB[1], skillDB[5], skillDB[6]};
        }else if (e1 == Water){
            temp = {skillDB[0], skillDB[2], skillDB[3], skillDB[7]};
        }else if (e1 == Ice){
            temp = {skillDB[0], skillDB[2], skillDB[5], skillDB[7]};
        }else if (e1 == Ground){
            temp = {skillDB[0], skillDB[1], skillDB[4], skillDB[6]};
        }else{
            temp = {skillDB[0], skillDB[3], skillDB[4], skillDB[6]};
        }
    }else{
        if (e2 == Electric){
            temp = {skillDB[1], skillDB[3], skillDB[5], skillDB[6]};
        }else if (e2 == Ice){
            temp = {skillDB[2], skillDB[5], skillDB[7], skillDB[8]};
        }else{
            temp = {skillDB[2], skillDB[3], skillDB[6], skillDB[8]};
        }
    }
    temp.resize(rand()%4+1);
    return temp;
}