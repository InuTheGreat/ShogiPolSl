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
    public:
        figura(string nazwa, int kodFigury);
        ~figura();

};


class plansza{
    private:
        int rozmiarPlanszy[9][9];
        bool tura;
    public:
        plansza();
        ~plansza();
        void startPlanszy(int testArray[9][9]);
        void wyswietlPlansze();

};

class gracz {

};



#endif //KLASY_H
