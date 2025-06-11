
#include "klasy.h"

using namespace std;


int main() {
    plansza p;
    //int currentPlayer = 1; // 1 lub 2
    gracz gg;
    int fromX, fromY, toX, toY;
    char input;

    while(true) {
        p.wyswietlPlansze();
        cout << "\nTura gracza " << gg.getCurrent() << " ("
             << (gg.getCurrent() == 1 ? "dolne" : "górne")
             << " bierki)\n";

        // Wybór bierki
        cout << "Podaj pozycję bierki (x y) lub 'q' aby wyjść: ";
        cin >> input;
        if(input == 'q') break;
        cin.putback(input);
        cin >> fromX >> fromY;

        // Konwersja na indeksy od 0 (jeśli chcemy indeksowanie od 1)
        // fromX--; fromY--;

        // Walidacja pozycji startowej
       /* if(!isValidPosition(fromX, fromY) || p.tablicaPlanszy[fromY][fromX] == 0) {
            cout << "Nieprawidłowa pozycja startowa!\n";
            continue;
        }

        // Sprawdzenie właściciela bierki
        int piece = p.tablicaPlanszy[fromY][fromX];
        if((currentPlayer == 1 && piece < 0) ||
           (currentPlayer == 2 && piece > 0)) {
            cout << "To nie twoja bierka!\n";
            continue;
           }

        // Wybór celu
        cout << "Podaj docelową pozycję (x y): ";
        cin >> toX >> toY;
        // toX--; toY--;

        if(!isValidPosition(toX, toY)) {
            cout << "Nieprawidłowa pozycja docelowa!\n";
            continue;
        }

        // Sprawdzenie czy pole docelowe jest puste
        if(p.tablicaPlanszy[toY][toX] != 0) {
            cout << "Pole docelowe nie jest puste! Wybierz inne pole.\n";
            continue;
        }

        // Wykonanie ruchu
        p.tablicaPlanszy[toY][toX] = piece;
        p.tablicaPlanszy[fromY][fromX] = 0;

        // Zmiana gracza
        currentPlayer = (currentPlayer == 1) ? 2 : 1;*/
    }
    //plansza p;
    p.wyswietlPlansze();
    return 0;
}