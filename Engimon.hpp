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
private:
    string name;
    vector<Skill> skill;
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
    Element getElement1();
    Element getElement2();
};



class Firemon : public Engimon{
public:
    Firemon(string name, string p1name, string p2name, string p1spc, string p2spc, int exp, int px, int py);
    ~Firemon();
};

class Watermon : public Engimon{
public:
    Watermon(string name, string p1name, string p2name, string p1spc, string p2spc, int exp, int px, int py);
    ~Watermon();
};

class Electricmon : public Engimon{
public:
    Electricmon(string name, string p1name, string p2name, string p1spc, string p2spc, int exp, int px, int py);
    ~Electricmon();
};

class Groundmon : public Engimon{
public:
    Groundmon(string name, string p1name, string p2name, string p1spc, string p2spc, int exp, int px, int py);
    ~Groundmon();
};

class Icemon : public Engimon{
public:
    Icemon(string name, string p1name, string p2name, string p1spc, string p2spc, int exp, int px, int py);
    ~Icemon();
};

class FireElectricmon : public Engimon{
public:
    FireElectricmon(string name, string p1name, string p2name, string p1spc, string p2spc, int exp, int px, int py);
    ~FireElectricmon();
};

class WaterIcemon : public Engimon{
public:
    WaterIcemon(string name, string p1name, string p2name, string p1spc, string p2spc, int exp, int px, int py);
    ~WaterIcemon();
};

class WaterGroundmon : public Engimon{
public:
    WaterGroundmon(string name, string p1name, string p2name, string p1spc, string p2spc, int exp, int px, int py);
    ~WaterGroundmon();
};

#endif
