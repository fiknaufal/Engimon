#ifndef MAP_HPP
#define MAP_HPP
#include "Player.hpp"
#include "skillgacha.hpp"
#include <stdlib.h>

enum gameState {Jalan, Battle, Bag, Exit};

class Map{
    public:
        Map(int n);
        ~Map();
    
        void show();
        void addEngi();
        void randomiseEnemyMovement();
        void gameFlow();
        int idSurroundEnemy(); //ini belom
        bool isBattle(); //ini belom
    private:
        char mapMatrix[15][15];
        Player player;
        vector<Engimon> wildEngi;
        int level;
        skillgacha sg;
        gameState state;
};

#endif
