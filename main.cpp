#include "klasy.h"

int main() {

    plansza p1;

    figura pionek1("Pionek1",1,6,4);
    p1.wyswietlPlansze();
    pionek1.ruchFigury(p1);
    p1.wyswietlPlansze();



    return 0;

}