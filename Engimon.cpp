#include "Engimon.hpp"
#include <string>
#include <iostream>
#include "Position.hpp"
using namespace std;

int Engimon::maxExp = 4000;

Engimon::Engimon(string name, string p1name, string p2name, string p1spc, string p2spc, string spc, int exp, Element e1, Element e2, int px, int py, string sound) : engimonPos(px, py){
    name = name;
    parentNames[0] = p1name;
    parentNames[1] = p2name;
    parentSpecies[0] = p1spc;
    parentSpecies[1] = p2spc;
    exp = exp;
    cumulativeExp = exp;
    elements[0] = e1;
    elements[1] = e2;
    sound = sound;
    species = spc;
}

Engimon::~Engimon(){}

int Engimon::getLevel(){
    return exp % 100;
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
    cout << "Element: " << elements[0] << "/" << elements[1] << endl;
    cout << "level: " << getLevel() << endl;
    cout << "experience: " << exp << endl;
    cout << "Cumulative Experience: " << cumulativeExp << endl;
}

Element Engimon::getElement1(){
    return elements[0];
}

Element Engimon::getElement1(){
    return elements[1];
}

Firemon::Firemon(string name, string p1name, string p2name, string p1spc, string p2spc, int exp, int px, int py) : 
Engimon(name, p1name, p2name, p1spc, p2spc,"Firemon", exp, Fire, None, px, py, "ROARRR"){}

Firemon::~Firemon(){};

Watermon::Watermon(string name, string p1name, string p2name, string p1spc, string p2spc, int exp, int px, int py) : 
Engimon(name, p1name, p2name, p1spc, p2spc,"Watermon", exp, Water, None, px, py, "BYURBYURR"){}

Watermon::~Watermon(){};

Electricmon::Electricmon(string name, string p1name, string p2name, string p1spc, string p2spc, int exp, int px, int py) : 
Engimon(name, p1name, p2name, p1spc, p2spc,"Electricmon", exp, Electric, None, px, py, "AYAYAYAYYY"){}

Electricmon::~Electricmon(){};

Groundmon::Groundmon(string name, string p1name, string p2name, string p1spc, string p2spc, int exp, int px, int py) : 
Engimon(name, p1name, p2name, p1spc, p2spc,"Groundmon", exp, Ground, None, px, py, "BUMBUMMM"){}

Groundmon::~Groundmon(){};

Icemon::Icemon(string name, string p1name, string p2name, string p1spc, string p2spc, int exp, int px, int py) : 
Engimon(name, p1name, p2name, p1spc, p2spc,"Icemon", exp, Ice, None, px, py, "BRRR BRRR"){}

Icemon::~Icemon(){};

FireElectricmon::FireElectricmon(string name, string p1name, string p2name, string p1spc, string p2spc, int exp, int px, int py) : 
Engimon(name, p1name, p2name, p1spc, p2spc,"FireElectricmon", exp, Fire, Electric, px, py, "BRRR BRRR"){}

FireElectricmon::~FireElectricmon(){};

WaterIcemon::WaterIcemon(string name, string p1name, string p2name, string p1spc, string p2spc, int exp, int px, int py) : 
Engimon(name, p1name, p2name, p1spc, p2spc,"WaterIcemon", exp, Water, Ice, px, py, "BRRR BRRR"){}

WaterIcemon::~WaterIcemon(){};

WaterGroundmon::WaterGroundmon(string name, string p1name, string p2name, string p1spc, string p2spc, int exp, int px, int py) : 
Engimon(name, p1name, p2name, p1spc, p2spc,"WaterGroundmon", exp, Water, Ground, px, py, "BRRR BRRR"){}

WaterGroundmon::~WaterGroundmon(){};