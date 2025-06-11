//
// Created by Konrad Mrozowski & Mateusz Pietrzak on 01/06/2025
// UPDATED 11/06/2025
//

#include "klasy.h"

// FIGURA______________________________________
figura::figura(string nazwa, int kodFigury, int x, int y)
    : nazwa(nazwa), kodFigury(kodFigury) {
    pozycja[0] = x;
    pozycja[1] = y;
}
figura::~figura() = default;
void figura::ruchFigury(plansza& p) { /* ... */ }
void figura::edytujPlansze(plansza& p, int a, int b) { /* ... */ }

// PLANSZA_________________________________________
plansza::plansza() {
    // Startowy układ shogi (małe litery - górny gracz, duże - dolny)
    tablicaPlanszy[0] = {"l", "n", "s", "g", "k", "g", "s", "n", "l"};
    tablicaPlanszy[1] = {".", "r", ".", ".", ".", ".", ".", "b", "."};
    tablicaPlanszy[2] = {"p", "p", "p", "p", "p", "p", "p", "p", "p"};
    for (int y = 3; y <= 5; ++y)
        tablicaPlanszy[y] = {".", ".", ".", ".", ".", ".", ".", ".", "."};
    tablicaPlanszy[6] = {"P", "P", "P", "P", "P", "P", "P", "P", "P"};
    tablicaPlanszy[7] = {".", "B", ".", ".", ".", ".", ".", "R", "."};
    tablicaPlanszy[8] = {"L", "N", "S", "G", "K", "G", "S", "N", "L"};
    tura = true;
}
plansza::~plansza() = default;

void plansza::wyswietlPlansze() const {
    cout << "   ";
    for (int x = 0; x < SIZE; ++x) cout << x+1 << " ";
    cout << endl;
    for (int y = 0; y < SIZE; ++y) {
        cout << y+1 << (y+1 < 10 ? "  " : " ");
        for (int x = 0; x < SIZE; ++x) {
            cout << tablicaPlanszy[y][x] << " ";
        }
        cout << endl;
    }
}

string plansza::getPole(int x, int y) const {
    return tablicaPlanszy[y][x];
}
void plansza::setPole(int x, int y, const string& val) {
    tablicaPlanszy[y][x] = val;
}

// GRACZ_________________________________________
gracz::gracz() { currentPlayer = 1; }
gracz::~gracz() = default;
void gracz::setCurrent(int i) { currentPlayer = i; }
int gracz::getCurrent() const { return currentPlayer; }

// WALIDACJA POZYCJI_____________________________
bool isValidPosition(int x, int y) {
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
}



bool isUpper(const string& s) {
    return !s.empty() && s[0] >= 'A' && s[0] <= 'Z';
}
bool isLower(const string& s) {
    return !s.empty() && s[0] >= 'a' && s[0] <= 'z';
}

bool pozycjaBierki(int& x, int& y)
{
    char input;
    cout << "Podaj pozycję bierki (x y) lub 'q' aby wyjść: ";
    cin >> input;
    if (input == 'q') return false;
    cin.putback(input);
    cin >> x >> y;
    x--; y--;
    return true;
}