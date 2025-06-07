//
// Created by Konrad Mrozowski on 01/06/2025.
//

#ifndef KLASY_H
#define KLASY_H
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
class figura {
private:
    string nazwa; //to tak tylko wstępnie. Wydaje mi się, że wyrzucimy ten parametr, gdyż wystarczy sam kod figury
    int kodFigury{}; //Kod liczbowy, który identyfikuje figurę na planszy.
    int pozycja[2];
public:
    figura(string nazwa, int kodFigury, int x, int y);
    ~figura();

    void ruchFigury();
    void edytujPlansze(class plansza& p);

};

class plansza{
private:
    int tablicaPlanszy[9][9]{};
    bool tura;
    friend void figura::edytujPlansze(plansza& p);
public:
    plansza();
    ~plansza();
    void wyswietlPlansze();


};











class gracz {

};



#endif //KLASY_H
