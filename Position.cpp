#include "Position.hpp"
using namespace std;

Position::Position(){
    this->x = 0;
    this->y = 0;
}

Position::Position(int x, int y){
    this->x = x;
    this->y = y;
}

Position::Position(const Position &p){
    this->x = p.x;
    this->y = p.y;
}

Position::~Position(){}

int Position::getX(){
    return this->x;
}

int Position::getY(){
    return this->y;
}

void Position::setX(int x){
    this->x = x;
}

void Position::setY(int y){
    this->y = y;
}

bool Position::operator==(const Position &p){
    return (this->x == p.x && this->y == p.y);
}