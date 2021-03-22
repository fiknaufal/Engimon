#include "Player.hpp"
#include "Engimon.hpp"
using namespace std;
#include <string>

Player::Player(){
    this->playerPos.setX(0);
    this->playerPos.setY(0);
    maxInv = 50;
    inventoryE.reserve(maxInv);
    inventoryS.reserve(maxInv);
}

Player::~Player(){}

void Player::Move(const string &c){
    if (c == "w"){
        if (this->playerPos.getY() < 14){
            int curY = this->playerPos.getY();
            this->playerPos.setY(curY+1);
        }
    }
    if (c == "a"){
        if (this->playerPos.getX() > 0){
            int curX = this->playerPos.getX();
            this->playerPos.setX(curX-1);
        }
    }
    if (c == "s"){
        if (this->playerPos.getY() > 0){
            int curY = this->playerPos.getY();
            this->playerPos.setY(curY-1);
        }
    }
    if (c == "d"){
        if (this->playerPos.getX() < 14){
            int curX = this->playerPos.getX();
            this->playerPos.setX(curX+1);
        }
    }
}

Position& Player::getPlayerPos(){
    return this->playerPos;
}

int Player::getInvCount(){
    return inventoryE.size() + inventoryS.size();
}

boolean Player::addEngimon(Engimon e){
    if(getInvCount() < maxInv){
        inventoryE.push_back(e)
        return 1;
    }
    else{
        return 0;
    }
}

boolean Player::addSkillItem(SkillItem s){
    if(getInvCount() < maxInv){
        vector<SkillItem>::iterator i = find(inventoryS.begin(), inventoryS.end(), s);

        if(i == inventoryS.end()){
            inventoryS.push_back(s);
        }
        else{
            i->add(1);
        }
        return 1;
    }
    else{
        return 0;
    }
}

// bikin get Name sama get Spesies di ENgimon lah wkwk
void Player::showEngimonList(){
    list <int> :: iterator i;
    cout << "List of Engimon" << endl;
    for(i = inventoryE.begin(); i!= inventoryE.end(); ++i){
        cout << i->getName << " " << i->getSpecies << endl;
    }
}

void Player::showSkillItemList(){
    list <int> :: iterator i;
    cout << "List of Skill Item" << endl;
    for(i = inventoryE.begin(); i!= inventoryE.end(); ++i){
        cout << i->getName << " " << i->getSpecies << endl;
    }
}



// bagian engimon

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
