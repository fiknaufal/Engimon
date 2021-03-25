#ifndef MAP_HPP
#define MAP_HPP
#include "Player.hpp"
#include "skillgacha.hpp"
#include <stdlib.h>
#include <vector>

enum gameState {Jalan, Battle, Bag, Exit};

class Map{
    public:
        Map(int n, string namafile);
        ~Map();
    
        void show();
        void addEngi();
        void randomiseEnemyMovement();
        void gameFlow();
        int idSurroundEnemy(); //ini belom
        bool isBattle(); //ini belom
    private:
        vector<string> mapMatrix;
        Player player;
        vector<Engimon> wildEngi;
        int level;
        skillgacha sg;
        gameState state;
};

#endif
