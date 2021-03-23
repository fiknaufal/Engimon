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

// Element make enum, tp g tau bagus ap kgks
enum Element { None, Electric, Fire, Ground, Ice, Water };

// fungsi battle
// Klo dah digabungin ke class player, harusnya cuman butuh 1 parameter, yaitu engimon musuh
bool battle(Engimon e1, Engimon e2) {
    int powerE1;
    int powerE2;

    // Misalkan atribut skill udh ad di engimon
    for (int i=0; i<4; i++) {
        powerE1 += e1.skill[i].basePower * e1.skill[i].masteryLevel;
        powerE2 += e2.skill[i].basePower * e2.skill[i].masteryLevel;
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
        if (A.getElmtAdv(B) > 1) {
            childElmt[0] = A.elements[0];
        }
        else if (B.getElmtAdv(A) > 1) {
            childElmt[0] = B.elements[0];
        }
        else {
            if (A.elements[0] == B.elements[0]) {
                childElmt[0] = A.elements[0];
            }
            else {
                childElmt[0] = min(A.elements[0], B.elements[0]);
                childElmt[1] = max(A.elements[0], B.elements[0]);
            }
        }

        string childName;
        cout << "Your new engimon name: ";
        cin >> childName;

        // Buat objek Engimon baru dgn element dan nama diatas
        output = new Engimon();

    }
    return output;
}


#endif