#include "Map.hpp"
#include <iostream>
#include <fstream>
using namespace std;

Map::Map(int n, string namafile) : sg(){

    fstream mapfile;
    mapfile.open(namafile,ios::in);
    if (mapfile.is_open()){
        string line;
        while(getline(mapfile, line)){
            mapMatrix.push_back(line);
        }
    }
    wildEngi.reserve(10);

    while (wildEngi.size() < 5){
        addEngi();
    }

    Firemon f(3000, 0, 0);
    Electricmon e(3000, 0, 0);
    player.addEngimon(f);
    player.addEngimon(e);
    level = n;
    this->state = Jalan;
}

Map::~Map(){

}

void Map::gameFlow(){
    string cmd;
    srand(time(0));
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
                if (cmd == "w"){
                    if (player.getPlayerPos().getY() < mapMatrix.size()-1){
                        player.Move(cmd);
                    }
                }else if (cmd == "a"){
                    if (player.getPlayerPos().getX() > 0){
                        player.Move(cmd);
                    }
                }else if (cmd == "s"){
                    if (player.getPlayerPos().getY() > 0){
                        player.Move(cmd);
                    }
                }else{
                    if (player.getPlayerPos().getX() < mapMatrix[0].length()-1){
                        player.Move(cmd);
                    }
                }
                randomiseEnemyMovement();
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
            while (state == Bag){
                cout << "--- BAG ---" << endl;
                cout << "Available Commands:" << endl;
                cout << "1. engimons: show engimons\n2. skillItems: show skill items\n3. chooseActive: pilih active engimon\n4. breed: Breed Engimon\n5.  close: close bag" << endl;
                cout << "-----------" << endl;
                cout << "command: ";
                string cmdbag;
                cin >> cmdbag;
                cout << "\n";
                if (cmdbag == "engimons"){
                    player.showEngimonList();
                }else if(cmdbag == "skillItems"){
                    player.showSkillItemList();
                }else if(cmdbag == "chooseActive"){
                    player.showEngimonList();
                    cout << "Pilih Active Engimon dengan nomor: " ;
                    int idx;
                    cin >> idx;
                    cout << "\n";
                    player.setActiveEngi(idx-1);
                }else if (cmdbag == "breed"){
                    player.showEngimonList();
                    cout << "Pilih Engimon 1: " ;
                    int idx1;
                    cin >> idx1;
                    cout << "Pilih Engimon 2: " ;
                    int idx2;
                    cin >> idx2;
                    cout << "\n";
                    player.breedEngimon(idx1-1, idx2-1);
                }
                else if (cmdbag == "close"){
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
    char maps[mapMatrix.size()][mapMatrix[0].length()];
    cout << "masuk" << endl;
    for (int i = mapMatrix.size()-1; i >= 0; i--){
        for (int j = 0; j < mapMatrix[0].length(); j++){
            maps[i][j] = mapMatrix[i][j];
        }
    }
    cout << "masuk" << endl;
    maps[player.getPlayerPos().getY()][player.getPlayerPos().getX()] = 'P';
    maps[player.getActivePos().getY()][player.getActivePos().getX()] = 'X';
    for(int i = 0; i < wildEngi.size(); i++){
        maps[wildEngi[i].getEngimonPos().getY()][wildEngi[i].getEngimonPos().getX()] = wildEngi[i].getMapSymbol(level);
    }
    cout << "masuk" << endl;
    for (int i = mapMatrix.size()-1; i >= 0; i--){
        for (int j = 0; j < mapMatrix[0].length(); j++){
            cout << maps[i][j];
        }
        cout << endl;
    }
    cout << "masuk" << endl;
}

void Map::addEngi(){
    if(wildEngi.size() < 10){
        int r = (rand()%30 + 1)*100;
        int x = rand()%mapMatrix[0].length(), y = rand()%mapMatrix.size();
        Engimon* w;

        if (mapMatrix[y][x] == '+'){
            int e1 = rand()%4;
            switch(e1){
                case 0:
                    w = new Watermon(r, x, y);
                    break;
                case 1:
                    w = new Icemon(r, x, y);
                    break;
                case 2:
                    w = new WaterIcemon(r, x, y);
                    break;
                case 3:
                    w = new WaterGroundmon(r, x, y);
                    break;
            }
            wildEngi.push_back(*w);
        } else if(mapMatrix[y][x] == '-'){
            int e2 = rand()%4;
            switch(e2){
                case 0:
                    w = new Firemon(r, x, y);
                    break;
                case 1:
                    w = new Groundmon(r, x, y);
                    break;
                case 2:
                    w = new Electricmon(r, x, y);
                    break;
                case 3:
                    w = new FireElectricmon(r, x, y);
                    break;
            }
            wildEngi.push_back(*w);
        }
    }
}

void Map::randomiseEnemyMovement(){
    int r, m;
    Position p;
    for(int i = 0; i < wildEngi.size(); i++){
        r = rand()%4 + 1;
        m = rand()%3;
        p = wildEngi[i].randomMove(r);
        if(m==0 && isInMap(p) && canEngimonWalk(wildEngi[i], p) && nobodyThere(p)){
            wildEngi[i].setEngimonPos(p.getX(), p.getY());
        }
    }
}
bool Map::canEngimonWalk(Engimon e, Position p){
    Element e1 = e.getElement1(), e2 = e.getElement2();
    char alas = mapMatrix[p.getY()][p.getX()];
    if(alas == '-'){
        if(e1==Fire || e1 == Electric || e1 == Ground || e2==Fire || e2 == Electric || e2 == Ground){
            return true;
        }
    }
    else{
        if(e1==Water || e1 ==Ice || e2==Water || e2 ==Ice){
            return true;
        }
    }
    return false;
}

bool Map::nobodyThere(Position p){
    if(p == player.getPlayerPos()){
        return false;
    }
    for(int i = 0; i < wildEngi.size(); i++){
        if(p == wildEngi[i].getEngimonPos()){
            return false;
        }
    }
    return true;
}

bool Map::isInMap(Position p){
    return p.getX() >= 0 && p.getX() < mapMatrix[0].length() && p.getY() >= 0 && p.getY() < mapMatrix.size();
}
