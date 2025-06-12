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

        // 1. Wybór bierki do ruchu
        if (!pozycjaBierki(fromX, fromY)) break;

        if (!isValidPosition(fromX, fromY) || p.getPole(fromX, fromY) == ".") {
            cout << "Nieprawidłowa pozycja startowa!\n";
            continue;
        }

        // 2. Sprawdzenie czy bierka należy do gracza
        figura* figuraPtr = p.znajdzFigure(fromX, fromY);
        if (!figuraPtr || figuraPtr->getGracz() != gg.getCurrent()) {
            cout << "To nie twoja bierka!\n";
            continue;
        }

        // 3. Wczytanie i walidacja ruchu (nowa metoda planszy)
        if (!p.wczytajIWalidujRuch(toX, toY, fromX, fromY, gg.getCurrent())) {
            continue;
        }

        // 4. Obsługa promocji
        string bierka = p.getPole(fromX, fromY);
        bool promotionPossible = false;

        if (figuraPtr && canPromote(bierka)) {
            if (isPromotionZone(fromY, gg.getCurrent()) ||
                isPromotionZone(toY, gg.getCurrent())) {
                promotionPossible = true;
            }
        }

        if (promotionPossible && mustPromote(bierka, toY, gg.getCurrent())) {
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
            cin.ignore(); // Czyścimy bufor po cin >> odp
        }

        // 5. Wykonanie ruchu
        p.setPole(toX, toY, bierka);
        p.setPole(fromX, fromY, ".");
        figuraPtr->ustawPozycje(toX, toY);

        // 6. Zmiana gracza
        gg.setCurrent(gg.getCurrent() == 1 ? 2 : 1);
    }

    return 0;
}