//
// Created by Konrad Mrozowski & Mateusz Pietrzak on 01/06/2025
// UPDATED 12/06/2025
//

#include "klasy.h"
#include <cmath>

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

bool pozycjaBierki(int& x, int& y) {
    char input;
    cout << "Podaj pozycję bierki (x y) lub 'q' aby wyjść: ";
    cin >> input;
    if (input == 'q') return false;
    cin.putback(input);
    cin >> x >> y;
    x--; y--;
    return true;
}

// WALIDACJA RUCHU FIGUR SZOGI___________________
bool isMoveValid(const plansza& p, int fromX, int fromY, int toX, int toY, int currentPlayer) {
    string piece = p.getPole(fromX, fromY);
    if (piece == ".") return false;
    bool isUpperPiece = isUpper(piece);
    char type = tolower(piece[0]);
    int dx = toX - fromX;
    int dy = toY - fromY;

    if ((currentPlayer == 1 && !isUpperPiece) || (currentPlayer == 2 && isUpperPiece)) return false;
    if (piece[0] == '+') type = tolower(piece[1]); // promowana bierka

    switch(type) {
        case 'k': // Król
            return abs(dx) <= 1 && abs(dy) <= 1;
        case 'g': // Złoty generał i promowane: pion, lanca, koń, srebrny
            if(abs(dx) > 1 || abs(dy) > 1) return false;
            if(isUpperPiece && dy == 1 && dx != 0) return false;
            if(!isUpperPiece && dy == -1 && dx != 0) return false;
            return true;
        case 's': // Srebrny generał
            if(abs(dx) > 1 || abs(dy) > 1) return false;
            if(isUpperPiece && dy == -1 && dx == 0) return true;
            if(!isUpperPiece && dy == 1 && dx == 0) return true;
            return abs(dx) == 1 && abs(dy) == 1;
        case 'b': { // Goniec
            if(abs(dx) != abs(dy)) return false;
            int stepX = dx > 0 ? 1 : -1;
            int stepY = dy > 0 ? 1 : -1;
            for(int i=1; i<abs(dx); ++i)
                if(p.getPole(fromX + i*stepX, fromY + i*stepY) != ".")
                    return false;
            return true;
        }
        case 'r': { // Wieża
            if(dx != 0 && dy != 0) return false;
            int step = dx != 0 ? (dx > 0 ? 1 : -1) : (dy > 0 ? 1 : -1);
            int steps = max(abs(dx), abs(dy));
            for(int i=1; i<steps; ++i) {
                int x = fromX + (dx != 0 ? i*step : 0);
                int y = fromY + (dy != 0 ? i*step : 0);
                if(p.getPole(x, y) != ".") return false;
            }
            return true;
        }
        case 'p': // Pion
            if(dx != 0) return false;
            return isUpperPiece ? dy == -1 : dy == 1;
        case 'l': { // Lance
            if(dx != 0) return false;
            int dir = isUpperPiece ? -1 : 1;
            if((toY - fromY) * dir <= 0) return false;
            for(int y = fromY + dir; y != toY; y += dir)
                if(p.getPole(fromX, y) != ".") return false;
            return true;
        }
        case 'n': // Koń
            if(isUpperPiece)
                return dy == -2 && abs(dx) == 1;
            else
                return dy == 2 && abs(dx) == 1;
        default: return false;
    }
}

// PROMOCJA SZOGI________________________________
bool isPromotionZone(int y, int player) {
    // Gracz 1: rzędy 0,1,2; Gracz 2: rzędy 6,7,8
    if (player == 1) return y >= 0 && y <= 2;
    else return y >= 6 && y <= 8;
}

bool canPromote(const std::string& piece) {
    char c = tolower(piece[0]);
    if (piece[0] == '+') return false; // już promowana
    return c == 'p' || c == 'l' || c == 'n' || c == 's' || c == 'b' || c == 'r';
}

bool mustPromote(const std::string& piece, int toY, int player) {
    char c = tolower(piece[0]);
    if (piece[0] == '+') return false;
    if (c == 'p' || c == 'l') {
        if ((player == 1 && toY == 0) || (player == 2 && toY == 8)) return true;
    }
    if (c == 'n') {
        if ((player == 1 && (toY == 0 || toY == 1)) ||
            (player == 2 && (toY == 8 || toY == 7))) return true;
    }
    return false;
}

std::string promotePiece(const std::string& piece) {
    if (piece[0] == '+') return piece; // już promowana
    char c = piece[0];
    return "+" + std::string(1, c);
}
