/*
Ini cuman tempan naro sementara, klo dah kelar tinggal dimasukin ke tempatnya masing2
*/
#ifndef IMAM_HPP
#define IMAM_HPP
#include "Engimon.hpp"
#include "Player.hpp"
#include <iostream>
#include <algorithm>
#include <string>

using std::cout;
using std::endl;
using std::min;
using std::max;
using std::string;



// fungsi battle
// Klo dah digabungin ke class player, harusnya cuman butuh 1 parameter, yaitu engimon musuh
bool battle(Engimon e1, Engimon e2) {
    int powerE1;
    int powerE2;

    // Misalkan atribut skill udh ad di engimon
    for (int i=0; i<e1.skill.size(); i++) {
        powerE1 += e1.skill[i].getBasePower() * e1.skill[i].getMasteryLevel();
    }

    for (int i=0; i<e2.skill.size(); i++) {
        powerE2 += e2.skill[i].getBasePower() * e2.skill[i].getMasteryLevel();
    }

    powerE1 += e1.getLevel() * e1.getElmtAdv(e2);
    powerE2 += e2.getLevel() * e2.getElmtAdv(e1);

    return (powerE1 > powerE2);
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


#endif