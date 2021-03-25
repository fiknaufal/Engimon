#include "Player.hpp"
#include "Engimon.hpp"
#include "Inventory.hpp"
using namespace std;
#include <iostream>
#include <string>
#include <bits/stdc++.h>

Player::Player() : inventoryE(), inventoryS(){
    this->playerPos.setX(1);
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
    inventoryE.getVector()[idActiveEngimon].setEngimonPos(playerPos.getX(), playerPos.getY());
    if (c == "w"){
            int curY = this->playerPos.getY();
            this->playerPos.setY(curY+1);
    }
    if (c == "a"){
            int curX = this->playerPos.getX();
            this->playerPos.setX(curX-1);
    }
    if (c == "s"){
            int curY = this->playerPos.getY();
            this->playerPos.setY(curY-1);
    }
    if (c == "d"){
            int curX = this->playerPos.getX();
            this->playerPos.setX(curX+1);
    }
}

Position Player::getActivePos(){
    return inventoryE.getVector()[idActiveEngimon].getEngimonPos();
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
    int n = 0;
    vector<SkillItem> v = inventoryS.getVector();
    for(int i = 0; i < v.size(); i++){
        n += v[i].getJumlah();
    }
    return inventoryE.getSize() + n;
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
    }else{
        inventoryE.getVector()[idActiveEngimon].plusExp(50);
        if (inventoryE.getVector()[idActiveEngimon].getCml() >= 4000){
            inventoryE.removeAtIdx(idActiveEngimon);
            setActiveEngi(0);
            cout << "Active Engimon mati karena melampaui batas level maksimal!\nActive Engimon sekarang adalah Engimon teratas di list." << endl;
        }
    }
    return (powerE1 >= powerE2);
}

// fungsi breeding
// Tinggal digabungin ke class player jg, nnt anaknya langsung dimasukin ke list aj, kgk usah jd output
void Player::breedEngimon (int idxA, int idxB) {

    int breedingCase = -1;

    // Cek level ortu
    if ((inventoryE.getVector()[idxA].getLevel() < 30) && (inventoryE.getVector()[idxB].getLevel() < 30))
        // Bingung antara throw atau munculin output aj
        cout << "Level ortu g cukup" << endl;

    // Cek muat atau g list engimon player (Blom bise diimplementasiin)
    else if (this->getInvCount() > maxInv)
        cout << "Inventory penuh" << endl;

    /*
    // Cek elemen ortu dual atau g, mungkin di-g bisa dlu-in
    else if ((inventoryE.getVector()[idxA].getElement2() != None) || (inventoryE.getVector()[idxB].getElement2() != None))
        cout << "Dual elmt engimon g punya kelamin" << endl;
    */

    else {
        Engimon engiA(inventoryE.getVector()[idxA]);
        engiA.setElement2(None);
        Engimon engiB(inventoryE.getVector()[idxB]);
        engiB.setElement2(None);

        Element childElmt[2] = {None, None};
        string spc; string sound;
        if (engiA.getElmtAdv(engiB) > 1) {
            childElmt[0] = engiA.getElement1();
            spc = engiA.getSpecies();
            sound = engiA.getSound();

            breedingCase = 0;
        }
        else if (engiB.getElmtAdv(engiA) > 1) {
            childElmt[0] = engiB.getElement1();
            spc = engiB.getSpecies();
            sound = engiB.getSound();

            breedingCase = 1;
        }
        else {
            if (engiA.getElement1() == engiB.getElement1()) {
                childElmt[0] = engiA.getElement1();
                spc = engiA.getSpecies();
                sound = engiA.getSound();

                breedingCase = 2;
            }
            else {
                childElmt[0] = min(engiA.getElement1(), engiB.getElement1());
                childElmt[1] = max(engiA.getElement1(), engiB.getElement1());
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
                sound = engiA.getSound();

                breedingCase = 3;
            }
        }

        // Masukin nama
        string childName;
        cout << "Your new engimon name: ";
        cin >> childName;

        // Buat objek Engimon baru dgn element dan nama diatas
        Engimon anak = Engimon(childName, engiA.getName(), engiB.getName(), engiA.getSpecies(), engiB.getSpecies(), spc, 0, childElmt[0], childElmt[1], -1, -1, sound);

        // Masukin skill-skill nya
        vector<Skill> skillsA (engiA.getSkill());
        vector<Skill> skillsB (engiB.getSkill());


        // Singkirin skill yg g kompatibel
        int i = 0;
        while ((!skillsA.empty()) && (i< skillsA.size())) {
            bool compatible = false;
            for (Element e : skillsA[i].getElement()) {
                if ((e == childElmt[0]) || (e == childElmt[1]))
                    compatible = true;
            }

            if (!compatible) {
                skillsA.erase(skillsA.begin() + i);
            }
            else {
                i++;
            }
        }

        i = 0;
        while ((!skillsB.empty()) && (i < skillsB.size())) {
            bool compatible = false;
            for (Element e : skillsB[i].getElement()) {
                if ((e == childElmt[0]) || (e == childElmt[1]))
                    compatible = true;
            }

            if (!compatible) {
                skillsB.erase(skillsB.begin() + i);
            }
            else {
                i++;
            }
        }


        while ((anak.getSkill().size() <= 4) && (!skillsA.empty() || !skillsB.empty())) {
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
                    else {
                        anak.addSkill(skillsA[skillAIdx]);
                        skillsA.erase(skillsA.begin() + skillAIdx);
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
        inventoryE.getVector()[idxA].setLevelAfterBreeding();
        inventoryE.getVector()[idxB].setLevelAfterBreeding();
    }
}

void Player::updateSkillItem(){
    int i = 0;
    while(i < inventoryS.getSize()){
        if(inventoryS.getElement(i).getJumlah() == 0){
            inventoryS.removeAtIdx(i);
        }
        else{
            i++;
        }
    }
}
