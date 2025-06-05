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
        int kodFigury; //Kod liczbowy, który identyfikuje figurę na planszy.

};


class plansza{
    private:
        int rozmiarPlanszy[8][8];
        bool tura;
    public:
        void startPlanszy();

};

class gracz {

};



#endif //KLASY_H
