#ifndef POSITION_HPP
#define POSITION_HPP

class Position
{
private:
    int x;
    int y;
public:
    Position();
    Position(int x, int y);
    Position(const Position &p);
    ~Position();

    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    bool operator==(const Position &p);
};


#endif
