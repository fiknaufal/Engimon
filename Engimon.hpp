#ifndef ENGIMON_HPP
#define ENGIMON_HPP
#include <string>
#include "Position.hpp"
using namespace std;

class Engimon
{
private:
    string name;
    // Skill skill[4]
    string parentNames[2];
    string parentSpecies[2];
    string species;
    string elements[2];
    string sound;
    int level;
    int maxExp;
    int exp;
    int cumulativeExp;
    Position engimonPos;

public:
    Engimon();
    virtual ~Engimon();
    int getLevel();
    int calcPower(const Engimon &engimon);

    Position& getEngimonPos();
    void setEngimonPos();
    void printSound();
    void setLevelAfterBreeding();
    void printData();
    void plusExp(int exp);
    string getName();
    string getSpecies();
};



class Firemon : public Engimon{
public:
    Firemon(string nama, string namaBapak, string namaIbu, string spcBapak, string spcIbu, int level);
    ~Firemon();
};

class Watermon : public Engimon{
public:
    Watermon(string nama, string namaBapak, string namaIbu, string spcBapak, string spcIbu, int level);
    ~Watermon();
};

class Electricmon : public Engimon{
public:
    Electricmon(string nama, string namaBapak, string namaIbu, string spcBapak, string spcIbu, int level);
    ~Electricmon();
};

class Groundmon : public Engimon{
public:
    Groundmon(string nama, string namaBapak, string namaIbu, string spcBapak, string spcIbu, int level);
    ~Groundmon();
};

class Icemon : public Engimon{
public:
    Icemon(string nama, string namaBapak, string namaIbu, string spcBapak, string spcIbu, int level);
    ~Icemon();
};

class FireElectricmon : public Engimon{
public:
    FireElectricmon(string nama, string namaBapak, string namaIbu, string spcBapak, string spcIbu, int level);
    ~FireElectricmon();
};

class WaterIcemon : public Engimon{
public:
    WaterIcemon(string nama, string namaBapak, string namaIbu, string spcBapak, string spcIbu, int level);
    ~WaterIcemon();
};

class WaterGroundmon : public Engimon{
public:
    WaterGroundmon(string nama, string namaBapak, string namaIbu, string spcBapak, string spcIbu, int level);
    ~WaterGroundmon();
};

#endif
