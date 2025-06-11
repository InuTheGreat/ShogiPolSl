//
// Created by Konrad Mrozowski & Mateusz Pietrzak on 01/06/2025
// UPDATED 11/06/2025
//

#include "klasy.h"
using namespace std;


int main() {
    plansza p;
    gracz gg;

    int fromX, fromY, toX, toY;
    char input;

    while (true) {
        p.wyswietlPlansze();

        cout << "\nTura gracza " << gg.getCurrent() << " ("
             << (gg.getCurrent() == 1 ? "dolne" : "górne")
             << " bierki)\n";

        if (pozycjaBierki(fromX,fromY)==false)break;

        if (!isValidPosition(fromX, fromY) || p.getPole(fromX, fromY) == ".") {
            cout << "Nieprawidłowa pozycja startowa!\n";
            continue;
        }

        string piece = p.getPole(fromX, fromY);
        if ((gg.getCurrent() == 1 && !isUpper(piece)) ||
            (gg.getCurrent() == 2 && !isLower(piece))) {
            cout << "To nie twoja bierka!\n";
            continue;
            }

        cout << "Podaj docelową pozycję (x y): ";
        cin >> toX >> toY;
        toX--; toY--;

        if (!isValidPosition(toX, toY)) {
            cout << "Nieprawidłowa pozycja docelowa!\n";
            continue;
        }

        if (p.getPole(toX, toY) != ".") {
            cout << "Pole docelowe nie jest puste! Wybierz inne pole.\n";
            continue;
        }

        // Przesunięcie bierki
        p.setPole(toX, toY, piece);
        p.setPole(fromX, fromY, ".");

        gg.setCurrent(gg.getCurrent() == 1 ? 2 : 1);
    }
    return 0;
}
