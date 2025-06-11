#include "klasy.h"

using namespace std;

const int SIZE = 9;


/*


bool isValidPosition(int x, int y) {
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
}
*/
int main() {
    /*int currentPlayer = 1; // 1 lub 2
    int fromX, fromY, toX, toY;
    char input;

    while(true) {
        printBoard();
        cout << "\nTura gracza " << currentPlayer << " ("
             << (currentPlayer == 1 ? "dolne" : "górne")
             << " bierki)\n";

        // Wybór bierki
        cout << "Podaj pozycję bierki (x y) lub 'q' aby wyjść: ";
        cin >> input;
        if(input == 'q') break;
        cin.putback(input);
        cin >> fromX >> fromY;

        // Konwersja na indeksy od 0
        fromX--; fromY--;

        // Walidacja pozycji startowej
        if(!isValidPosition(fromX, fromY) || board[fromY][fromX] == 0) {
            cout << "Nieprawidłowa pozycja startowa!\n";
            continue;
        }

        // Sprawdzenie właściciela bierki
        int piece = board[fromY][fromX];
        if((currentPlayer == 1 && piece < 0) ||
           (currentPlayer == 2 && piece > 0)) {
            cout << "To nie twoja bierka!\n";
            continue;
        }

        // Wybór celu
        cout << "Podaj docelową pozycję (x y): ";
        cin >> toX >> toY;
        toX--; toY--;

        if(!isValidPosition(toX, toY)) {
            cout << "Nieprawidłowa pozycja docelowa!\n";
            continue;
        }

        // Sprawdzenie czy pole docelowe jest puste
        if(board[toY][toX] != 0) {
            cout << "Pole docelowe nie jest puste! Wybierz inne pole.\n";
            continue;
        }

        // Wykonanie ruchu
        board[toY][toX] = piece;
        board[fromY][fromX] = 0;

        // Zmiana gracza
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }
*/
    plansza p;
    p.wyswietlPlansze();
    return 0;
}