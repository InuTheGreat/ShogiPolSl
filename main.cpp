//
// Created by Konrad Mrozowski & Mateusz Pietrzak on 01/06/2025
// UPDATED 12/06/2025
//

#include "klasy.h"
#include <iostream>
using namespace std;

int main() {
    plansza p;
    gracz gg;
    int fromX, fromY, toX, toY;

    while (true) {
        p.wyswietlPlansze();
        cout << "\nTura gracza " << gg.getCurrent() << " ("
             << (gg.getCurrent() == 1 ? "dolne" : "górne")
             << " bierki)\n";

        if (!pozycjaBierki(fromX, fromY)) break;

        if (!isValidPosition(fromX, fromY) || p.getPole(fromX, fromY) == ".") {
            cout << "Nieprawidłowa pozycja startowa!\n";
            continue;
        }

        string bierka = p.getPole(fromX, fromY);
        figura* figuraPtr = p.znajdzFigure(fromX, fromY);

        if ((gg.getCurrent() == 1 && !isUpper(bierka)) ||
            (gg.getCurrent() == 2 && !isLower(bierka))) {
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

        string target = p.getPole(toX, toY);
        if (target != ".") {
            if ((isUpper(target) && gg.getCurrent() == 1) ||
                (isLower(target) && gg.getCurrent() == 2)) {
                cout << "Nie możesz zbić własnej bierki!\n";
                continue;
            }
        }

        if (!isMoveValid(p, fromX, fromY, toX, toY, gg.getCurrent())) {
            cout << "Nieprawidłowy ruch dla tej bierki!\n";
            continue;
        }

        // PROMOCJA
        bool promotionPossible = false;
        if (figuraPtr && canPromote(bierka)) {
            if (isPromotionZone(fromY, gg.getCurrent()) || isPromotionZone(toY, gg.getCurrent())) {
                promotionPossible = true;
            }
        }

        if (promotionPossible && mustPromote(bierka, toY, gg.getCurrent())) {
            bierka = promotePiece(bierka);
            if (figuraPtr) figuraPtr->promuj();
            cout << "Promocja obowiązkowa!\n";
        } else if (promotionPossible) {
            cout << "Czy chcesz promować tę bierkę? (t/n): ";
            char odp;
            cin >> odp;
            if (odp == 't' || odp == 'T') {
                bierka = promotePiece(bierka);
                if (figuraPtr) figuraPtr->promuj();
                cout << "Bierka została promowana!\n";
            }
        }

        // Przesunięcie bierki
        p.setPole(toX, toY, bierka);
        p.setPole(fromX, fromY, ".");
        if (figuraPtr) figuraPtr->ustawPozycje(toX, toY);

        gg.setCurrent(gg.getCurrent() == 1 ? 2 : 1);
    }

    return 0;
}