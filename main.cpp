#include <iostream>
#include <iomanip>

using namespace std;

const int SIZE = 9;

// Inicjalizacja planszy zgodnie z podanym schematem
int board[SIZE][SIZE] = {
    {7, 6, 5, 4, 1, 4, 5, 6, 7},
    {0, 2, 0, 0, 0, 0, 0, 3, 0},
    {8, 8, 8, 8, 8, 8, 8, 8, 8},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {8, 8, 8, 8, 8, 8, 8, 8, 8},
    {0, 3, 0, 0, 0, 0, 0, 2, 0},
    {7, 6, 5, 4, 1, 4, 5, 6, 7}
};

void printBoard() {
    cout << "\n  ";
    for (int x = 0; x < SIZE; x++) {
        cout << setw(2) << x+1 << " ";
    }
    cout << "\n";

    for (int y = 0; y < SIZE; y++) {
        cout << y+1 << " ";
        for (int x = 0; x < SIZE; x++) {
            cout << setw(2) << board[y][x] << " ";
        }
        cout << "\n";
    }
}

bool isValidPosition(int x, int y) {
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
}

int main() {
    bool running = true;
    int fromX, fromY, toX, toY;
    char input;

    while(running) {
        printBoard();

        cout << "\nWybierz figure (x y) lub 'q' aby wyjsc: ";
        cin >> input;
        if(input == 'q') break;
        cin.putback(input);

        cin >> fromX >> fromY;
        fromX--; fromY--; // Konwersja na indeksy od 0

        if(!isValidPosition(fromX, fromY) || board[fromY][fromX] == 0) {
            cout << "Nieprawidlowa pozycja startowa!\n";
            continue;
        }

        cout << "Podaj docelowa pozycje (x y): ";
        cin >> toX >> toY;
        toX--; toY--;

        if(!isValidPosition(toX, toY)) {
            cout << "Nieprawidlowa pozycja docelowa!\n";
            continue;
        }

        // Wykonanie ruchu
        board[toY][toX] = board[fromY][fromX];
        board[fromY][fromX] = 0;
    }

    return 0;
}