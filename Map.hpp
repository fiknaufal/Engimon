#ifndef MAP_HPP
#define MAP_HPP
#include "Player.hpp"
#include <stdlib.h>

class Map{
    public:
        Map(int n);
        ~Map();

        void updateMap(Position pp);
        void show();
        void addEngi();
        // void randomiseEnemyMovement();
    private:
        char mapMatrix[15][15];
        Position playerPos;
        vector<Engimon> wildEngi;
        int level;
};

#endif
