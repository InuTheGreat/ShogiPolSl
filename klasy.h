//
// Created by Konrad Mrozowski & Mateusz Pietrzak on 01/06/2025
// UPDATED 11/06/2025
//

#ifndef KLASY_H
#define KLASY_H

#include <iostream>
#include <array>
#include <string>
using namespace std;

const int SIZE = 9;

class plansza;

// FIGURA____________________________________________
class figura {
private:
    string nazwa;
    int kodFigury;
    int pozycja[2];
public:
    figura(string nazwa, int kodFigury, int x, int y);
    ~figura();
    void ruchFigury(plansza &p);
    void edytujPlansze(plansza& p, int a, int b);
};

// PLANSZA______________________________________________
class plansza {
private:
    array<array<string, SIZE>, SIZE> tablicaPlanszy;
    bool tura;
    friend void figura::edytujPlansze(plansza& p, int a, int b);
public:
    plansza();
    ~plansza();
    void wyswietlPlansze() const;
    string getPole(int x, int y) const;
    void setPole(int x, int y, const string& val);
};

// GRACZ_________________________________________________
class gracz {
private:
    int currentPlayer;
public:
    gracz();
    ~gracz();
    int getCurrent() const;
    void setCurrent(int i);
};

bool isValidPosition(int x, int y);
bool isUpper(const string& s);
bool isLower(const string& s);
bool pozycjaBierki(int& x, int& y);

#endif //KLASY_H
