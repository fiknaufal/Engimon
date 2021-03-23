/*
Ini cuman tempan naro sementara, klo dah kelar tinggal dimasukin ke tempatnya masing2
*/
#ifndef IMAM_HPP
#define IMAM_HPP
#include "Engimon.hpp"
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
Engimon breeding (Engimon& A, Engimon& B) {
    Engimon output = NULL;

    // Cek level ortu
    if ((A.getLevel() < 30) && (B.getLevel() < 30)) 
        // Bingung antara throw atau munculin output aj
        cout << "Level ortu g cukup" << endl;

    // Cek muat atau g list engimon player (Blom bise diimplementasiin)

    // Cek elemen ortu dual atau g, mungkin di-g bisa dlu-in
    else if ((A.elements[1] != NULL) || (B.elements[1] != NULL))
        cout << "Dual elmt engimon g punya kelamin" << endl;

    else {
        Element childElmt[2] = {None, None};
        string spc; string sound;
        if (A.getElmtAdv(B) > 1) {
            childElmt[0] = A.elements[0];
            spc = A.getSpecies();
            sound = A.sound;
        }
        else if (B.getElmtAdv(A) > 1) {
            childElmt[0] = B.elements[0];
            spc = B.getSpecies();
            sound = B.sound;
        }
        else {
            if (A.elements[0] == B.elements[0]) {
                childElmt[0] = A.elements[0];
                spc = A.getSpecies();
                sound = A.sound;
            }
            else {
                childElmt[0] = min(A.elements[0], B.elements[0]);
                childElmt[1] = max(A.elements[0], B.elements[0]);
                spc = A.getSpecies(); //masih salah
                sound = A.sound; //masih salah
            }
        }

        string childName;
        cout << "Your new engimon name: ";
        cin >> childName;

        // Buat objek Engimon baru dgn element dan nama diatas
        output = new Engimon(childName, A.getName(), B.getName(), A.getSpecies(), B.getSpecies(), spc, 0, childElmt[0], childElmt[1], -1, -1, sound);

    }
    return output;
}


#endif