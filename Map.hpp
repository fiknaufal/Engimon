#ifndef MAP_HPP
#define MAP_HPP
#include "Player.hpp"
#include "skillgacha.hpp"
#include <stdlib.h>
#include <vector>
#include <time.h>

enum gameState {Jalan, Battle, Bag, Exit};

class Map{
    public:
        Map(int n, string namafile, int maxengi);
        ~Map();

        void show();
        void addEngi();
        void randomiseEnemyMovement();
        void gameFlow();
        int idSurroundEnemy();
        bool isBattle();
        bool canEngimonWalk(Engimon e, Position p);
        bool nobodyThere(Position p);
        bool isInMap(Position p);
    private:
        vector<string> mapMatrix;
        Player player;
        vector<Engimon> wildEngi;
        int level;
        skillgacha sg;
        gameState state;
};

#endif
