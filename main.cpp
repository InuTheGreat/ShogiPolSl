#include "klasy.h"
using namespace std;

int main() {
    plansza planszaGl;
    gracz gracz1;
    int fromX, fromY, toX, toY;

    while (true) {
        planszaGl.wyswietlPlansze();
        cout << "\nTura gracza " << gracz1.getCurrent() << " ("
             << (gracz1.getCurrent() == 1 ? "dolne" : "górne")
             << " bierki)\n";

        if (planszaGl.czySzach(gracz1.getCurrent())) {
            cout << "UWAGA: Twój król jest w szachu!\n";
            if (planszaGl.czyMat(gracz1.getCurrent())) {
                cout << "MAT! Gracz " << (gracz1.getCurrent() == 1 ? "2" : "1") << " wygrywa.\n";
                break;
            }
        }
        if (!planszaGl.wczytajRuch(fromX, fromY, toX, toY, gracz1.getCurrent()))
        {
            continue;
        }
        string bierka = planszaGl.getPole(fromX, fromY);
        figura* figuraPtr = planszaGl.znajdzFigure(fromX, fromY);
        planszaGl.setPole(toX, toY, bierka, gracz1.getCurrent());
        figuraPtr->ustawPozycje(toX, toY);

        gracz1.setCurrent(gracz1.getCurrent() == 1 ? 2 : 1);
    }

    return 0;
}