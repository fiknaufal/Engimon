#include "Imam.hpp"
#include "Engimon.hpp"
#include "Position.hpp"
#include <iostream>

using std::cout;
using std::endl;


#pragma region Method2 Engimon

Position& Engimon::getEngimonPos() {
    return this->engimonPos;
}

void Engimon::setEngimonPos(Position p) {
    engimonPos.setX(p.getX());
    engimonPos.setY(p.getY());
}

void Engimon::printSound() {
    cout << sound << endl;
}

void Engimon::setLevelAfterBreeding() {
    cumulativeExp -= 100*30;
}

#pragma endregion