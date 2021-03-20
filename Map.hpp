#ifndef MAP_HPP
#define MAP_HPP
#include "Player.hpp"

class Map{
    public:
        Map();
        ~Map();

        void updateMap(Position pp);
        void show();
        // void randomiseEnemyMovement();
    private:
        char mapMatrix[15][15];
        Position playerPos;
        // Wild wildArray[10];
};

#endif