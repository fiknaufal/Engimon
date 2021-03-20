#include "Map.hpp"
#include <iostream>
using namespace std;

Map::Map(){
    for (int i = 0; i < 15; i++){
        for (int j = 0; j < 15; j++){
            this->mapMatrix[i][j] = '-';
        }
    }

    for (int i = 0; i < 8; i++){
        for (int j = 7; j < 15; j++){
            this->mapMatrix[i][j] = '+';
        }
    }
    this->mapMatrix[this->playerPos.getY()][this->playerPos.getX()] = 'P';
    
}

Map::~Map(){}

void Map::updateMap(Position pp){
    for (int i = 0; i < 15; i++){
        for (int j = 0; j < 15; j++){
            this->mapMatrix[i][j] = '-';
        }
    }

    for (int i = 0; i < 8; i++){
        for (int j = 7; j < 15; j++){
            this->mapMatrix[i][j] = '+';
        }
    }
    this->playerPos.setX(pp.getX());
    this->playerPos.setY(pp.getY());
    this->mapMatrix[this->playerPos.getY()][this->playerPos.getX()] = 'P';
}

void Map::show(){
    for (int i = 14; i >= 0; i--){
        for (int j = 0; j < 15; j++){
            cout << this->mapMatrix[i][j];
        }
        cout << endl;
    }
}