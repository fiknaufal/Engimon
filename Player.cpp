#include "Player.hpp"
#include "Engimon.hpp"
#include "Inventory.hpp"
using namespace std;
#include <iostream>
#include <string>
#include <bits/stdc++.h>

Player::Player() : inventoryE(), inventoryS(){
    this->playerPos.setX(0);
    this->playerPos.setY(1);
    maxInv = 50;
    idActiveEngimon = 0;
}

Player::~Player(){}

bool Player::lose(){
    return inventoryE.getSize() == 0;
}

void Player::showActiveEngimon(){
    inventoryE.getVector()[idActiveEngimon].printData();
}

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
        inventoryE.getVector()[idActiveEngimon].setEngimonPos(x1, y1);
    }
    if(outidx){
        throw "bambang mau kemana sih\n";
    }
}

Position& Player::getPlayerPos(){
    return this->playerPos;
}

int Player::getInvCount(){
    return inventoryE.getSize() + inventoryS.getSize();
}

bool Player::addEngimon(Engimon e){
    if(getInvCount() < maxInv){
        inventoryE.add(e);
        return 1;
    }
    else{
        return 0;
    }
}

bool Player::addSkillItem(SkillItem s){
    if(getInvCount() < maxInv){
        vector<SkillItem>::iterator i = find(inventoryS.getVector().begin(), inventoryS.getVector().end(), s);

        if(i == inventoryS.getVector().end()){
            inventoryS.add(s);
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
    int j = 1;
    cout << "List of Engimon" << endl;
    for(auto i = inventoryE.getVector().begin(); i!= inventoryE.getVector().end(); ++i){
        cout << j << ". " << i->getName() << " " << i->getSpecies() << " " << i->getLevel()<< endl;
        j++;
    }
}

void Player::showSkillItemList(){
    int j = 1;
    cout << "List of Skill Item" << endl;
    for(auto i = inventoryS.getVector().begin(); i != inventoryS.getVector().end(); ++i){
        cout << j << ". " << i->getSkill().getSkillName() << " " << i->getJumlah() << endl;
        j++;
    }
}

void Player::setActiveEngi(int i){
    if (i < inventoryE.getSize()){
        idActiveEngimon = i;
    }
    else{
        cout << "Id tidak valid, set Active Engimon pada Engimon pertama list" << endl;
        idActiveEngimon = 0;
    }
}

void Player::petEngi(){
    inventoryE.getVector()[idActiveEngimon].printSound();
}

bool Player::battle(Engimon e) {
    int powerE1 = 0;
    int powerE2 = 0;

    // Misalkan atribut skill udh ad di engimon
    for (int i=0; i<inventoryE.getVector()[idActiveEngimon].getSkill().size(); i++) {
        powerE1 += inventoryE.getVector()[idActiveEngimon].getSkill()[i].getBasePower() * inventoryE.getVector()[idActiveEngimon].getSkill()[i].getMasteryLevel();
    }

    for (int i=0; i<e.getSkill().size(); i++) {
        powerE2 += e.getSkill()[i].getBasePower() * e.getSkill()[i].getMasteryLevel();
    }

    powerE1 += inventoryE.getVector()[idActiveEngimon].getLevel() * inventoryE.getVector()[idActiveEngimon].getElmtAdv(e);
    powerE2 += e.getLevel() * e.getElmtAdv(inventoryE.getVector()[idActiveEngimon]);

    if (powerE1 < powerE2){
        inventoryE.removeAtIdx(idActiveEngimon);
    }
    return (powerE1 >= powerE2);
}

// fungsi breeding
// Tinggal digabungin ke class player jg, nnt anaknya langsung dimasukin ke list aj, kgk usah jd output
void Player::breedEngimon (Engimon& A, Engimon& B) {

    int breedingCase = -1;

    // Cek level ortu
    if ((A.getLevel() < 30) && (B.getLevel() < 30)) 
        // Bingung antara throw atau munculin output aj
        cout << "Level ortu g cukup" << endl;

    // Cek muat atau g list engimon player (Blom bise diimplementasiin)
    else if (this->getInvCount() > maxInv) 
        cout << "Inventory penuh" << endl;

    // Cek elemen ortu dual atau g, mungkin di-g bisa dlu-in
    else if ((A.getElement1() != None) || (B.getElement2() != None))
        cout << "Dual elmt engimon g punya kelamin" << endl;

    else {
        Element childElmt[2] = {None, None};
        string spc; string sound;
        if (A.getElmtAdv(B) > 1) {
            childElmt[0] = A.getElement1();
            spc = A.getSpecies();
            sound = A.getSound();
            
            breedingCase = 0;
        }
        else if (B.getElmtAdv(A) > 1) {
            childElmt[0] = B.getElement1();
            spc = B.getSpecies();
            sound = B.getSound();

            breedingCase = 1;
        }
        else {
            if (A.getElement1() == B.getElement1()) {
                childElmt[0] = A.getElement1();
                spc = A.getSpecies();
                sound = A.getSound();

                breedingCase = 2;
            }
            else {
                childElmt[0] = min(A.getElement1(), B.getElement1());
                childElmt[1] = max(A.getElement1(), B.getElement1());
                if (childElmt[0] == Fire) {
                    spc = "FireElectricmon";
                }
                else {
                    if (childElmt[1] == Ice) {
                        spc = "WaterIcemon";
                    }
                    else {
                        spc = "WaterGroundmon";
                    }
                }
                sound = A.getSound();

                breedingCase = 3;
            }
        }

        // Masukin nama
        string childName;
        cout << "Your new engimon name: ";
        cin >> childName;

        // Buat objek Engimon baru dgn element dan nama diatas
        Engimon anak = Engimon(childName, A.getName(), B.getName(), A.getSpecies(), B.getSpecies(), spc, 0, childElmt[0], childElmt[1], -1, -1, sound);

        // Masukin skill-skill nya
        vector<Skill> skillsA = A.getSkill();
        vector<Skill> skillsB = B.getSkill();

        // Singkirin skill yg g kompatibel
        int i = 0;
        while ((!skillsA.empty()) && (i< skillsA.size())) {
            if ((skillsA[i].getElement()[0] != childElmt[0]) && 
                (skillsA[i].getElement()[1] != childElmt[0]) && 
                (skillsA[i].getElement()[0] != childElmt[1]) && 
                (skillsA[i].getElement()[1] != childElmt[1])) {
                    skillsA.erase(skillsA.begin() + i);
                }
            else {
                i++;
            }
        }
        i = 0;
        while ((!skillsB.empty()) && (i < skillsB.size())) {
            if ((skillsB[i].getElement()[0] != childElmt[0]) && 
                (skillsB[i].getElement()[1] != childElmt[0]) && 
                (skillsB[i].getElement()[0] != childElmt[1]) && 
                (skillsB[i].getElement()[1] != childElmt[1])) {
                    skillsB.erase(skillsB.begin() + i);
                }
            else {
                i++;
            }
        }

        while ((anak.getSkill().size() <= 4) && (!skillsA.empty()) && (!skillsB.empty())) {
            int skillAIdx = -1;
            if (!skillsA.empty()) {
                for(int i=0; i<skillsA.size(); i++) {
                    if (skillAIdx == -1) {
                        skillAIdx = i;
                    }
                    else if (skillsA[i].getMasteryLevel() > skillsA[skillAIdx].getMasteryLevel()) {
                        skillAIdx = i;
                    }
                }
            }

            int skillBIdx = -1;
            if (!skillsB.empty()) {
                for(int i=0; i<skillsB.size(); i++) {
                    if (skillBIdx == -1) {
                        skillBIdx = i;
                    }
                    else if (skillsB[i].getMasteryLevel() > skillsB[skillBIdx].getMasteryLevel()) {
                        skillBIdx = i;
                    }
                }
            }

            if ((skillBIdx > -1) && (skillAIdx > -1)) {

                if (skillsA[skillAIdx].getMasteryLevel() > skillsB[skillBIdx].getMasteryLevel()) {
                    anak.addSkill(skillsA[skillAIdx]);
                    skillsA.erase(skillsA.begin() + skillAIdx);
                }
                else if (skillsA[skillAIdx].getMasteryLevel() < skillsB[skillBIdx].getMasteryLevel()) {
                    anak.addSkill(skillsB[skillBIdx]);
                    skillsB.erase(skillsB.begin() + skillBIdx);
                }
                else {
                    if (skillsA[skillAIdx] == skillsB[skillBIdx]) {
                        Skill upgradedSkill = skillsA[skillAIdx];
                        upgradedSkill.masteryLevelUp();
                        anak.addSkill(upgradedSkill);
                        skillsA.erase(skillsA.begin() + skillAIdx);
                        skillsB.erase(skillsB.begin() + skillBIdx);
                    }
                }
            }

            else {
                if (skillAIdx > -1) {
                    anak.addSkill(skillsA[skillAIdx]);
                    skillsA.erase(skillsA.begin() + skillAIdx);
                }

                else {
                    anak.addSkill(skillsB[skillBIdx]);
                    skillsB.erase(skillsB.begin() + skillBIdx);
                }
            }
        }

        // Tambahin anak ke list
        addEngimon(anak);
    }
}
