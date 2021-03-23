#include "Player.hpp"
#include "Engimon.hpp"
using namespace std;
#include <iostream>
#include <string>
#include <bits/stdc++.h>

Player::Player(){
    this->playerPos.setX(0);
    this->playerPos.setY(0);
    maxInv = 50;
    inventoryE.reserve(maxInv);
    inventoryS.reserve(maxInv);
    idActiveEngimon = 0;
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
    MoveActiveEngi();
}

void Player::MoveActiveEngi(){ // cek obstacle belom jadi
    int x = playerPos.getX(), y = playerPos.getY(), x1 = x, y1 = y-1;
    bool outidx = false, obstacle = false;
    if(x1 < 0 || x1 > 14 || y1 < 0 || y1 > 14/* || obstacle()*/){ // bawah gabisa
        outidx = true;
        y1 = y+1;
    }
    if(x1 < 0 || x1 > 14 || y1 < 0 || y1 > 14){ // atas gabisa
        outidx = true;
        x1 = x-1;
        y1 = y;
    }
    if(x1 < 0 || x1 > 14 || y1 < 0 || y1 > 14){ // kiri gabisa
        outidx = true;
        x1 = x+1;
    }
    if(x1 < 0 || x1 > 14 || y1 < 0 || y1 > 14){ // kanan gabisa
        cout << "anjir dikepung";
    }
    else{
        inventoryE[idActiveEngimon].setEngimonPos(x1, y1);
    }
    if(outidx){
        throw "bambang mau kemana sih\n";
    }
}

Position& Player::getPlayerPos(){
    return this->playerPos;
}

int Player::getInvCount(){
    return inventoryE.size() + inventoryS.size();
}

bool Player::addEngimon(Engimon e){
    if(getInvCount() < maxInv){
        inventoryE.push_back(e);
        return 1;
    }
    else{
        return 0;
    }
}

bool Player::addSkillItem(SkillItem s){
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
    cout << "List of Engimon" << endl;
    for(auto i = inventoryE.begin(); i!= inventoryE.end(); ++i){
        cout << i->getName() << " " << i->getSpecies() << endl;
    }
}

void Player::showSkillItemList(){
    cout << "List of Skill Item" << endl;
    for(auto i = inventoryE.begin(); i != inventoryE.end(); ++i){
        cout << i->getName() << " " << i->getSpecies() << endl;
    }
}
