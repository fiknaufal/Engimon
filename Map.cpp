#include "Map.hpp"
#include <iostream>
using namespace std;

Map::Map(int n){
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
    wildEngi.reserve(10);
    level = n;
}

Map::~Map(){}

void Map::updateMap(Position pp){
    this->playerPos.setX(pp.getX());
    this->playerPos.setY(pp.getY());
}

void Map::show(){
    char maps[15][15];

    for (int i = 14; i >= 0; i--){
        for (int j = 0; j < 15; j++){
            maps[i][j] = mapMatrix[i][j];
        }
    }

    maps[playerPos.getX()][playerPos.getY()] = 'P';
    for(int i = 0; i < wildEngi.size(); i++){
        maps[wildEngi[i].getEngimonPos().getX()][wildEngi[i].getEngimonPos().getY()] = wildEngi[i].getMapSymbol(level);
    }

    for (int i = 14; i >= 0; i--){
        for (int j = 0; j < 15; j++){
            cout << maps[i][j];
        }
        cout << endl;
    }
}

void Map::addEngi(){
    if(wildEngi.size() < 10){
        int r = (rand()%30 + 1)*100, r1 = rand()%8;
        int x = 0, y = 0;
        Engimon* w;
        switch(r1){
            case 0:
                w = new Firemon(r, x, y);
                break;
            case 1:
                w = new Watermon(r, x, y);
                break;
            case 2:
                w = new Electricmon(r, x, y);
                break;
            case 3:
                w = new Groundmon(r, x, y);
                break;
            case 4:
                w = new Icemon(r, x, y);
                break;
            case 5:
                w = new FireElectricmon(r, x, y);
                break;
            case 6:
                w = new WaterIcemon(r, x, y);
                break;
            case 7:
                w = new WaterGroundmon(r, x, y);
                break;
        }
        wildEngi.push_back(*w);
    }
}
