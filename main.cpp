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

        if (planszaGl.czySzach(gracz1.getCurrent()))
        {
            cout << "UWAGA: Twój król jest w szachu!\n";
            if (planszaGl.czyMat(gracz1.getCurrent()))
            {
                cout << "MAT! Gracz " << (gracz1.getCurrent() == 1 ? "2" : "1") << " wygrywa.\n";
                break;
            }
        }

        if (!pozycjaBierki(fromX, fromY, gracz1)) break;

        if (!isValidPosition(fromX, fromY) || planszaGl.getPole(fromX, fromY) == ".") {
            cout << "Nieprawidłowa pozycja startowa!\n";
            continue;
        }

        figura* figuraPtr = planszaGl.znajdzFigure(fromX, fromY);
        if (!figuraPtr || figuraPtr->getGracz() != gracz1.getCurrent()) {
            cout << "To nie twoja bierka!\n";
            continue;
        }

        if (!planszaGl.wczytajIWalidujRuch(toX, toY, fromX, fromY, gracz1.getCurrent())) {
            continue;
        }

        string bierka = planszaGl.getPole(fromX, fromY);
        bool promotionPossible = false;

        if (figuraPtr && canPromote(bierka)) {
            if (isPromotionZone(fromY, gracz1.getCurrent()) ||
                isPromotionZone(toY, gracz1.getCurrent())) {
                promotionPossible = true;
            }
        }

        if (promotionPossible && mustPromote(bierka, toY, gracz1.getCurrent())) {
            bierka = promotePiece(bierka);
            figuraPtr->promuj();
            cout << "Promocja obowiązkowa!\n";
        }
        else if (promotionPossible) {
            cout << "Czy chcesz promować tę bierkę? (t/n): ";
            char odp;
            cin >> odp;
            if (odp == 't' || odp == 'T') {
                bierka = promotePiece(bierka);
                figuraPtr->promuj();
                cout << "Bierka została promowana!\n";
            }
            cin.ignore();
        }

        planszaGl.setPole(toX, toY, bierka);
        planszaGl.setPole(fromX, fromY, ".");
        figuraPtr->ustawPozycje(toX, toY);

        gracz1.setCurrent(gracz1.getCurrent() == 1 ? 2 : 1);
    }

    return 0;
}