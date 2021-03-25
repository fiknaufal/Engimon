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
    wildEngi.reserve(10);
    for (int i = 0; i<5; i++){
        addEngi();
    }
    FireElectricmon f(3000, 0, 0);
    player.addEngimon(f);
    level = n;
    this->state = Jalan;
}

Map::~Map(){}

void Map::gameFlow(){
    string cmd;
    while (state != Exit && !player.lose()){
        if (isBattle()){
            this->state = Battle;
        }
        if (state == Jalan){
            show();
            cout << "\n";
            cout << "--------------------" << endl;
            cout << "Available Commands:" << endl;
            cout << "1. w,a,s,d: Move\n2. bag: Open Bag\n3. show: Show Active Engimon\n4. pet: Pet Active Engimon\n5. exit: Exit the game" << endl;
            cout << "--------------------" << endl;
            cout << "command: ";
            cin >> cmd;
            cout << "\n";
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
            cout << "1. engimons: show engimons\n2. skillItems: show skill items\n3. close: close bag" << endl;
            cout << "-----------" << endl;
            while (state == Bag){
                cout << "command: ";
                string cmdbag;
                cin >> cmdbag;
                cout << "\n";
                if (cmdbag == "engimons"){
                    player.showEngimonList();
                }else if(cmdbag == "skillItems"){
                    player.showSkillItemList();
                }else if (cmdbag == "close"){
                    state = Jalan;
                }else{
                    cout << "Command tidak dikenali" << endl;
                }
            }

        }else if (state == Battle){
            cout << "\n";
            show();
            cout << "\n";
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
                addEngi();
                state = Jalan;
            }
            else{
                cout << "Kamu Kalah!" << endl;
                if (!player.lose()){
                    cout << "Pilih Engimon lain untuk bertarung :"<< endl;
                    player.showEngimonList();
                    cout << "Pilih engimon nomor: " << endl;
                    int id;
                    cin >> id;
                    player.setActiveEngi(id-1);
                }
            }
        }
    }
}

bool Map::isBattle(){
    for (int i = 0; i < wildEngi.size(); i++){
        if (player.getPlayerPos().getY()+1 == wildEngi[i].getEngimonPos().getY() && player.getPlayerPos().getX() == wildEngi[i].getEngimonPos().getX()){
            return true;
        }
        if (player.getPlayerPos().getY() == wildEngi[i].getEngimonPos().getY() && player.getPlayerPos().getX()+1 == wildEngi[i].getEngimonPos().getX()){
            return true;
        }
        if (player.getPlayerPos().getY()-1 == wildEngi[i].getEngimonPos().getY() && player.getPlayerPos().getX() == wildEngi[i].getEngimonPos().getX()){
            return true;
        }
        if (player.getPlayerPos().getY() == wildEngi[i].getEngimonPos().getY() && player.getPlayerPos().getX()-1 == wildEngi[i].getEngimonPos().getX()){
            return true;
        }
    }
    return false;
}

int Map::idSurroundEnemy(){
    for (int i = 0; i < wildEngi.size(); i++){
        if (player.getPlayerPos().getY()+1 == wildEngi[i].getEngimonPos().getY() && player.getPlayerPos().getX() == wildEngi[i].getEngimonPos().getX()){
            return i;
        }
        if (player.getPlayerPos().getY() == wildEngi[i].getEngimonPos().getY() && player.getPlayerPos().getX()+1 == wildEngi[i].getEngimonPos().getX()){
            return i;
        }
        if (player.getPlayerPos().getY()-1 == wildEngi[i].getEngimonPos().getY() && player.getPlayerPos().getX() == wildEngi[i].getEngimonPos().getX()){
            return i;
        }
        if (player.getPlayerPos().getY() == wildEngi[i].getEngimonPos().getY() && player.getPlayerPos().getX()-1 == wildEngi[i].getEngimonPos().getX()){
            return i;
        }
    }
    return -1;
}

void Map::show(){
    char maps[15][15];

    for (int i = 14; i >= 0; i--){
        for (int j = 0; j < 15; j++){
            maps[i][j] = mapMatrix[i][j];
        }
    }

    maps[player.getPlayerPos().getY()][player.getPlayerPos().getX()] = 'P';
    for(int i = 0; i < wildEngi.size(); i++){
        maps[wildEngi[i].getEngimonPos().getY()][wildEngi[i].getEngimonPos().getX()] = wildEngi[i].getMapSymbol(level);
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
        int x = rand()%15, y = rand()%15;
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
