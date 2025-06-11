//
// Created by Konrad Mrozowski on 01/06/2025.
//

#ifndef KLASY_H
#define KLASY_H
#include <iostream>
#include <string>
#include <array>
#include <iomanip>

using namespace std;

const int SIZE = 9;

class plansza;

//FIGURA____________________________________________
class figura {
private:
    string nazwa; //to tak tylko wstępnie. Wydaje mi się, że wyrzucimy ten parametr, gdyż wystarczy sam kod figury
    int kodFigury{}; //Kod liczbowy, który identyfikuje figurę na planszy.
    int pozycja[2];
public:
    figura(string nazwa, int kodFigury, int x, int y);
    ~figura();

    void ruchFigury(plansza &p);
    void edytujPlansze(plansza& p,int a, int b);

};


//PLANSZA______________________________________________
class plansza
{
private:
    array<array<int, SIZE>, SIZE> tablicaPlanszy;
    bool tura;
    friend void figura::edytujPlansze(plansza& p,int a, int b);
public:
    plansza();
    ~plansza();
    void wyswietlPlansze()const;
};


//PLANSZA_________________________________________________
class gracz
{
    private:
        int currentPlayer;
    public:
        gracz();
        ~gracz();
        int getCurrent()const;
        void setCurrent(int i);
};

bool isValidPosition(int x, int y);
void wyborBierki();
#endif //KLASY_H
