#include "Map.hpp"
#include <iostream>
using namespace std;

Map::Map(int n) : sg(){
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
    this->mapMatrix[this->player.getPlayerPos().getY()][this->player.getPlayerPos().getX()] = 'P';
    wildEngi.reserve(10);
    level = n;
    this->state = Jalan;
}

Map::~Map(){}

void Map::gameFlow(){
    string cmd;
    while (state != Exit){
        if (isBattle()){
            this->state = Battle;
        }
        if (state == Jalan){
            show();
            cout << "--------------------" << endl;
            cout << "Available Commands:" << endl;
            cout << "1. w,a,s,d: Move\n2. bag: Open Bag\n3. show: Show Active Engimon\n4. pet: Pet Active Engimon\n5. exit: Exit the game" << endl;
            cout << "--------------------" << endl;
            cout << "command: ";
            cin >> cmd;
            if (cmd == "w"||cmd == "a"||cmd == "s"||cmd == "d"){
                player.Move(cmd);
            }else if (cmd == "bag"){
                state = Bag;
            }else if (cmd == "show"){
                player.showActiveEngimon();
            }else if (cmd == "pet"){
                player.petEngi();
            }else if (cmd == "exit"){
                state = Exit;
            }else{
                cout << "Command tidak dikenali" << endl;
            }
        }else if (state == Bag){
            cout << "--- BAG ---" << endl;
            cout << "Available Commands:" << endl;
            cout << "1. show engimons\n2. show skill items\n3. close bag" << endl;
            cout << "-----------" << endl;
            cout << "command: ";
            cin >> cmd;
            if (cmd == "show engimons"){
                player.showEngimonList();
            }else if(cmd == "show skill items"){
                player.showSkillItemList();
            }else if (cmd == "close bag"){
                state = Jalan;
            }else{
                cout << "Command tidak dikenali" << endl;
            }
        }else if (state == Battle){
            cout << "You are battling:" << endl;
            wildEngi[idSurroundEnemy()].printData();
            cout << "Battle result:" << endl;
            if (player.battle(wildEngi[idSurroundEnemy()])){
                if (player.addEngimon(wildEngi[idSurroundEnemy()])){
                    cout << "Kamu menang!\n"<< wildEngi[idSurroundEnemy()].getName() << " dimasukkan ke dalam inventory!" << endl;
                    SkillItem si(sg.getRandomSkill(wildEngi[idSurroundEnemy()].getElement1(), wildEngi[idSurroundEnemy()].getElement2()), 1);
                    cout << si.getSkill().getSkillName() << " didapatkan" << endl;
                    player.addSkillItem(si);
                }else{
                    cout << "Kamu menang!\n"<< wildEngi[idSurroundEnemy()].getName() << " tidak dapat dimasukkan ke dalam inventory!" << endl;
                }
                wildEngi.erase(wildEngi.begin()+idSurroundEnemy());
            }
            else{
                cout << "Kamu Kalah!\nPilih Engimon lain untuk bertarung :"<< endl;
                player.showEngimonList();
                // suruh pilih engimon baru
            }
        }
    }
}

void Map::show(){
    char maps[15][15];

    for (int i = 14; i >= 0; i--){
        for (int j = 0; j < 15; j++){
            maps[i][j] = mapMatrix[i][j];
        }
    }

    maps[player.getPlayerPos().getX()][player.getPlayerPos().getY()] = 'P';
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
