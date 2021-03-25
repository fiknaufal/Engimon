#ifndef ENGIMON_HPP
#define ENGIMON_HPP
#include <string>
#include "Position.hpp"
#include "Skill.hpp"
#include <vector>
using namespace std;

class Engimon
{
    friend bool battle(Engimon e1, Engimon e2);
    friend Engimon breeding (Engimon& A, Engimon& B);
protected:
    vector<Skill> skill;
private:
    string name;
    string parentNames[2];
    string parentSpecies[2];
    string species;
    Element elements[2];
    string sound;
    static int maxExp;
    int exp;
    int cumulativeExp;
    Position engimonPos;

public:
    Engimon(string name, string p1name, string p2name, string p1spc, string p2spc, string spc, int exp, Element e1, Element e2, int px, int py, string sound);
    virtual ~Engimon();
    int getLevel();
    int getCml();
    double getElmtAdv(const Engimon& lawan);

    Position& getEngimonPos();
    void setEngimonPos(int x, int y);
    void printSound();
    void setLevelAfterBreeding();
    void printData();
    void printSkills();
    void plusExp(int exp);
    bool addSkill(const Skill& sk);
    string getName();
    string getSpecies();
    string getSound();
    Element getElement1();
    Element getElement2();
    char getMapSymbol(int);
    vector<Skill> getSkill();
    Position randomMove(int);
    string getElementName(Element);
};

class Firemon : public Engimon{
public:
    Firemon(string name, string p1name, string p2name, string p1spc, string p2spc, int exp, int px, int py);
    Firemon(int, int, int);
    ~Firemon();
};

class Watermon : public Engimon{
public:
    Watermon(string name, string p1name, string p2name, string p1spc, string p2spc, int exp, int px, int py);
    Watermon(int, int, int);
    ~Watermon();
};

class Electricmon : public Engimon{
public:
    Electricmon(string name, string p1name, string p2name, string p1spc, string p2spc, int exp, int px, int py);
    Electricmon(int, int, int);
    ~Electricmon();
};

class Groundmon : public Engimon{
public:
    Groundmon(string name, string p1name, string p2name, string p1spc, string p2spc, int exp, int px, int py);
    Groundmon(int, int, int);
    ~Groundmon();
};

class Icemon : public Engimon{
public:
    Icemon(string name, string p1name, string p2name, string p1spc, string p2spc, int exp, int px, int py);
    Icemon(int, int, int);
    ~Icemon();
};

class FireElectricmon : public Engimon{
public:
    FireElectricmon(string name, string p1name, string p2name, string p1spc, string p2spc, int exp, int px, int py);
    FireElectricmon(int, int, int);
    ~FireElectricmon();
};

class WaterIcemon : public Engimon{
public:
    WaterIcemon(string name, string p1name, string p2name, string p1spc, string p2spc, int exp, int px, int py);
    WaterIcemon(int, int, int);
    ~WaterIcemon();
};

class WaterGroundmon : public Engimon{
public:
    WaterGroundmon(string name, string p1name, string p2name, string p1spc, string p2spc, int exp, int px, int py);
    WaterGroundmon(int, int, int);
    ~WaterGroundmon();
};

#endif
