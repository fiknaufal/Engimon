#include "Engimon.hpp"
#include <string>
#include <iostream>
#include "Position.hpp"
#include "skillgacha.hpp"
using namespace std;

int Engimon::maxExp = 4000;

Engimon::Engimon(string names, string p1name, string p2name, string p1spc, string p2spc, string spc, int expr, Element e1, Element e2, int px, int py, string sounds) : engimonPos(px, py){
    name = names;
    parentNames[0] = p1name;
    parentNames[1] = p2name;
    parentSpecies[0] = p1spc;
    parentSpecies[1] = p2spc;
    exp = expr;
    cumulativeExp = expr;
    elements[0] = e1;
    elements[1] = e2;
    sound = sounds;
    species = spc;
}

Engimon::~Engimon(){}

int Engimon::getLevel(){
    return exp / 100;
}

bool Engimon::addSkill(const Skill& sk){
    if (skill.size() < 4){
        for (int i = 0; i < skill.size(); i++){
            if (sk == skill[i]){
                cout << "Skill sudah dipelajari" << endl;
                return false;
            }
        }
        skill.push_back(sk);
        return true;
    }
    else{
        cout << "Skill sudah penuh" << endl;
        return false;
    }
}

double Engimon::getElmtAdv(const Engimon& lawan){
    double tabelAdv[6][6] = {{0, 0, 0, 0, 0 ,0}, {0,1,0,1,0.5,2}, {0,2,1,0,1,1}, {0,1,2,1,0,1.5}, {0,1.5,1,2,1,0}, {0,0,1,0.5,2,1}};
    double adv[4];
    adv[0] = tabelAdv[elements[0]][lawan.elements[0]];
    adv[1] = tabelAdv[elements[0]][lawan.elements[1]];
    adv[2] = tabelAdv[elements[1]][lawan.elements[0]];
    adv[3] = tabelAdv[elements[1]][lawan.elements[1]];

    double max = 0;
    for (int i = 0; i < 4; i++){
        if (adv[i] > max){
            max = adv[i];
        }
    }
    return max;
}

Position& Engimon::getEngimonPos() {
    return this->engimonPos;
}

void Engimon::setEngimonPos(int x, int y) {
    engimonPos.setX(x);
    engimonPos.setY(y);
}

void Engimon::printSound() {
    cout << this->name << " : "<< sound << endl;
}

void Engimon::setLevelAfterBreeding() {
    exp -= 100*30;
}

string Engimon::getName(){
    return name;
}

string Engimon::getSpecies(){
    return species;
}

int Engimon::getCml(){
    return cumulativeExp;
}

void Engimon::plusExp(int i){
    exp += i;
    cumulativeExp += i;
    if(cumulativeExp >= maxExp){
        throw "mati bosku";
    }
}

void Engimon::printData(){
    cout << "Nama: " << name << endl;
    cout << "Parent 1: " << parentNames[0] << " species " << parentSpecies[0] << endl;
    cout << "Parent 2: " << parentNames[1] << " species " << parentSpecies[1] << endl;
    cout << "Element: " << getElementName(elements[0]) << "/" << getElementName(elements[1]) << endl;
    cout << "level: " << getLevel() << endl;
    cout << "experience: " << exp%100 << endl;
    cout << "Cumulative Experience: " << cumulativeExp << endl;
    printSkills();
}

void Engimon::printSkills(){
    for (int i = 0; i < skill.size(); i++){
        cout << "Skill " << i+1 << ": " << endl;
        cout << "   Nama Skill: "<< skill[i].getSkillName() << endl;
        cout << "   Base Power: "<< skill[i].getBasePower() << endl;
        cout << "   Mastery   : "<< skill[i].getMasteryLevel() << endl;
    }
}

Element Engimon::getElement1(){
    return elements[0];
}

Element Engimon::getElement2(){
    return elements[1];
}

char Engimon::getMapSymbol(int n){
    char big[5] = {'F', 'W', 'E', 'G', 'I'};
    char small[5] = {'f', 'w', 'e', 'g', 'i'};
    if(exp/100 < n){
        return small[elements[0]-1];
    }
    else{
        return big[elements[0]-1];
    }
}

string Engimon::getSound(){
    return sound;
}

vector<Skill> Engimon::getSkill(){
    return this->skill;
}

Position Engimon::randomMove(int n){
    int x = engimonPos.getX(), y = engimonPos.getY();
    Position p(x, y);
    if(n == 1){
        p.setX(x+1);
    }
    else if(n == 2){
        p.setX(x-1);
    }
    else if(n==3){
        p.setY(y+1);
    }
    else if(n==4){
        p.setY(y-1);
    }
    return p;
}

string Engimon::getElementName(Element e){
    if(e == None){
        return "None";
    }
    if(e == Fire){
        return "Fire";
    }
    if(e == Electric){
        return "Electric";
    }
    if(e == Ground){
        return "Ground";
    }
    if(e == Water){
        return "Water";
    }
    if(e == Ice){
        return "Ice";
    }
    else{
        return "Gaada bang";
    }
}

Firemon::Firemon(string name, string p1name, string p2name, string p1spc, string p2spc, int exp, int px, int py) :
Engimon(name, p1name, p2name, p1spc, p2spc,"Firemon", exp, Fire, None, px, py, "ROARRR"){
    skillgacha sg;
    skill = sg.getSkillGen(Fire, None);
}

Firemon::Firemon(int x, int px, int py) :
Engimon("Wild Firemon", "Firemon Ibu", "Firemon Ibu juga", "Firemon", "Firemon", "Firemon", x, Fire, None, px, py, "ROARRR"){
    skillgacha sg;
    skill = sg.getSkillGen(Fire, None);
}

Firemon::~Firemon(){};

Watermon::Watermon(string name, string p1name, string p2name, string p1spc, string p2spc, int exp, int px, int py) :
Engimon(name, p1name, p2name, p1spc, p2spc,"Watermon", exp, Water, None, px, py, "BYURBYURR"){
    skillgacha sg;
    skill = sg.getSkillGen(Water, None);
}

Watermon::Watermon(int x, int px, int py) :
Engimon("Wild Watermon", "Watermon Ibu", "Watermon Ibu juga", "Watermon", "Watermon","Watermon", x, Water, None, px, py, "BYURBYURR"){
    skillgacha sg;
    skill = sg.getSkillGen(Water, None);
}

Watermon::~Watermon(){};

Electricmon::Electricmon(string name, string p1name, string p2name, string p1spc, string p2spc, int exp, int px, int py) :
Engimon(name, p1name, p2name, p1spc, p2spc,"Electricmon", exp, Electric, None, px, py, "AYAYAYAYYY"){
    skillgacha sg;
    skill = sg.getSkillGen(Electric, None);
}

Electricmon::Electricmon(int x,int px, int py) :
Engimon("Wild Electricmon", "Electricmon Ibu", "Electricmon Ibu juga", "Electricmon", "Electricmon", "Electricmon", x, Electric, None, py, px, "AYAYAYAYYY"){
    skillgacha sg;
    skill = sg.getSkillGen(Electric, None);
}

Electricmon::~Electricmon(){};

Groundmon::Groundmon(string name, string p1name, string p2name, string p1spc, string p2spc, int exp, int px, int py) :
Engimon(name, p1name, p2name, p1spc, p2spc,"Groundmon", exp, Ground, None, px, py, "BUMBUMMM"){
    skillgacha sg;
    skill = sg.getSkillGen(Ground, None);
}

Groundmon::Groundmon(int x, int px, int py) :
Engimon("Wild Groundmon", "Groundmon Ibu", "Groundmon Ibu juga", "Groundmon", "Groundmon","Groundmon", x, Ground, None, px, py, "BUMBUMMM"){
    skillgacha sg;
    skill = sg.getSkillGen(Ground, None);
}

Groundmon::~Groundmon(){};

Icemon::Icemon(string name, string p1name, string p2name, string p1spc, string p2spc, int exp, int px, int py) :
Engimon(name, p1name, p2name, p1spc, p2spc,"Icemon", exp, Ice, None, px, py, "BRRR BRRR"){
    skillgacha sg;
    skill = sg.getSkillGen(Ice, None);
}

Icemon::Icemon(int x, int px, int py) :
Engimon("Wild Icemon", "Icemon Ibu", "Icemon Ibu juga", "Icemon", "Icemon","Icemon", x, Ice, None, px, py, "BRRR BRRR"){
    skillgacha sg;
    skill = sg.getSkillGen(Ice, None);
}

Icemon::~Icemon(){};

FireElectricmon::FireElectricmon(string name, string p1name, string p2name, string p1spc, string p2spc, int exp, int px, int py) :
Engimon(name, p1name, p2name, p1spc, p2spc,"FireElectricmon", exp, Fire, Electric, px, py, "ROAR AYAY"){
    skillgacha sg;
    skill = sg.getSkillGen(Fire, Electric);
}

FireElectricmon::FireElectricmon(int x, int px, int py) :
Engimon("Wild FireElectricmon", "FireElectricmon Ibu", "FireElectricmon Ibu juga", "FireElectricmon", "FireElectricmon","FireElectricmon", x, Fire, Electric, px, py, "ROAR AYAY"){
    skillgacha sg;
    skill = sg.getSkillGen(Fire, Electric);
}

FireElectricmon::~FireElectricmon(){};

WaterIcemon::WaterIcemon(string name, string p1name, string p2name, string p1spc, string p2spc, int exp, int px, int py) :
Engimon(name, p1name, p2name, p1spc, p2spc,"WaterIcemon", exp, Water, Ice, px, py, "BYUR BRRR"){
    skillgacha sg;
    skill = sg.getSkillGen(Water, Ice);
}

WaterIcemon::WaterIcemon(int x, int px, int py) :
Engimon("Wild WaterIcemon", "WaterIcemon Ibu", "WaterIcemon Ibu juga", "WaterIcemon", "WaterIcemon","WaterIcemon", x, Water, Ice, px, py, "BYUR BRRR"){
    skillgacha sg;
    skill = sg.getSkillGen(Water, Ice);
}

WaterIcemon::~WaterIcemon(){};

WaterGroundmon::WaterGroundmon(string name, string p1name, string p2name, string p1spc, string p2spc, int exp, int px, int py) :
Engimon(name, p1name, p2name, p1spc, p2spc,"WaterGroundmon", exp, Water, Ground, px, py, "BUMM BYURR"){
    skillgacha sg;
    skill = sg.getSkillGen(Water, Ground);
}

WaterGroundmon::WaterGroundmon(int x, int px, int py) :
Engimon("Wild WaterGroundmon", "WaterGroundmon Ibu", "WaterGroundmon Ibu juga", "WaterGroundmon", "WaterGroundmon","WaterGroundmon", x, Water, Ground, px, py, "BUMM BYURR"){
    skillgacha sg;
    skill = sg.getSkillGen(Water, Ground);
}

WaterGroundmon::~WaterGroundmon(){};
