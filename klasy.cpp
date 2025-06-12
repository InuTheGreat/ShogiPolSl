//
// Created by Konrad Mrozowski & Mateusz Pietrzak on 01/06/2025
// UPDATED 12/06/2025
//

#include "klasy.h"


// FIGURA______________________________________
figura::figura(char symbol, int x, int y)
    : symbol(symbol), promowana(false), pozycja{x, y}
{
    gracz = (symbol >= 'A' && symbol <= 'Z') ? 1 : 2;
}

figura:: ~figura()= default;

int figura::getGracz() const { return gracz; }
bool figura::isPromoted() const { return promowana; }
void figura::promuj() { promowana = true; }

int figura::pozycjaX() const { return pozycja[0]; }
int figura::pozycjaY() const { return pozycja[1]; }
void figura::ustawPozycje(int x, int y)
{
    pozycja[0] = x;
    pozycja[1] = y;
}



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
    inicjalizujFigury();
}
plansza::~plansza() = default;
bool plansza::wczytajRuch(int& fromX, int& fromY, int& toX, int& toY, int currentPlayer) {
    if (!pozycjaBierki(fromX, fromY, currentPlayer)) return false;

    if (!isValidPosition(fromX, fromY) || getPole(fromX, fromY) == ".") {
        cout << "Nieprawidłowa pozycja startowa!\n";
        return false;
    }

    figura* figuraPtr = znajdzFigure(fromX, fromY);
    if (!figuraPtr || figuraPtr->getGracz() != currentPlayer) {
        cout << "To nie twoja bierka!\n";
        return false;
    }

    string input;
    cout << "Podaj docelową pozycję (x y) lub 'q' aby anulować: ";
    getline(cin, input);

    if (input == "q") return false;

    istringstream iss(input);
    if (!(iss >> toX >> toY)) {
        cerr << "Nieprawidłowy format! Wprowadź dwie liczby (np. '3 5').\n";
        return false;
    }

    toX--; toY--;

    if (!isValidPosition(toX, toY)) {
        cout << "Nieprawidłowa pozycja docelowa!\n";
        return false;
    }


    string target = getPole(toX, toY);
    if (target != ".") {
        if ((isUpper(target) && currentPlayer == 1) || (isLower(target) && currentPlayer == 2)) {
            cout << "Nie możesz zbić własnej bierki!\n";
            return false;
        }
    }

    if (!isMoveValid(*this, fromX, fromY, toX, toY, currentPlayer)) {
        cout << "Nieprawidłowy ruch dla tej bierki!\n";
        return false;
    }

    return true;
}
void plansza::wyswietlPlansze() const
{
    cout << "   ";
    for (int x = 0; x < SIZE; ++x) cout << x+1 << " ";
    cout << endl;
    for (int y = 0; y < SIZE; ++y)
        {
        cout << y+1 << (y+1 < 10 ? "  " : " ");
        for (int x = 0; x < SIZE; ++x)
            {
            cout << tablicaPlanszy[y][x] << " ";
        }
        cout << endl;
    }
}
string plansza::getPole(int x, int y) const
{
    return tablicaPlanszy[y][x];
}
void plansza::setPole(int x, int y, const string& val)
{
    tablicaPlanszy[y][x] = val;
}
void plansza::inicjalizujFigury()
{
    for (int y = 0; y < SIZE; ++y)
    {
        for (int x = 0; x < SIZE; ++x)
        {
            string pole = tablicaPlanszy[y][x];
            if (pole != ".")
            {
                figury.emplace_back(pole[0], x, y);
            }
        }
    }
}
figura* plansza::znajdzFigure(int x, int y)
{
    for (auto& f : figury)
    {
        if (f.pozycjaX() == x && f.pozycjaY() == y)
        {
            return &f;
        }
    }
    return nullptr;
}//zastanowić się czy nie można zrobić tego lepiej
bool plansza::czySzach(int gracz) const
{
    int kingX,kingY;
    string flagaKrola = (gracz == 1) ? "K" : "k";

    for (int y = 0; y < SIZE; ++y)
        {
        for (int x = 0; x < SIZE; ++x)
        {
            if (tablicaPlanszy[y][x] == flagaKrola)
            {
                kingX = x;
                kingY = y;
                break;
            }
        }
    }

    int przeciwnik = (gracz == 1) ? 2 : 1;
    for (int y = 0; y < SIZE; ++y) {
        for (int x = 0; x < SIZE; ++x) {
            string pole = tablicaPlanszy[y][x];
            if (pole != "." && ((gracz == 1 && isLower(pole)) || (gracz == 2 && isUpper(pole)))) {
                if (isMoveValid(*this, x, y, kingX, kingY, przeciwnik)) {
                    return true;
                }
            }
        }
    }

    return false;
}
bool plansza::czyMat(int gracz) {
    if (!czySzach(gracz)) return false;

    for (int fromY = 0; fromY < SIZE; ++fromY) {
        for (int fromX = 0; fromX < SIZE; ++fromX) {
            string pole = tablicaPlanszy[fromY][fromX];
            if (pole != "." && ((gracz == 1 && isUpper(pole)) || (gracz == 2 && isLower(pole)))) {

                for (int toY = 0; toY < SIZE; ++toY) {
                    for (int toX = 0; toX < SIZE; ++toX) {
                        if (isMoveValid(*this, fromX, fromY, toX, toY, gracz)) {

                            string originalFrom = tablicaPlanszy[fromY][fromX];
                            string originalTo = tablicaPlanszy[toY][toX];
                            tablicaPlanszy[toY][toX] = originalFrom;
                            tablicaPlanszy[fromY][fromX] = ".";

                            bool szachPoRuchu = czySzach(gracz);


                            tablicaPlanszy[fromY][fromX] = originalFrom;
                            tablicaPlanszy[toY][toX] = originalTo;

                            if (!szachPoRuchu) {
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }

    return true;
}
void plansza::setPole(int x, int y, const std::string& val, int currentPlayer)
{

    if (currentPlayer != 0 && canPromote(val))
        {
        if (mustPromote(val, y, currentPlayer))
            {
            tablicaPlanszy[y][x] = promotePiece(val);
            figura* f = znajdzFigure(x, y);
            if (f) f->promuj();
            return;
        }
    }


    tablicaPlanszy[y][x] = val;
}

// GRACZ_________________________________________
gracz::gracz() { currentPlayer = 1; }
gracz::~gracz() = default;
void gracz::setCurrent(int i) { currentPlayer = i; }
int gracz::getCurrent() const { return currentPlayer; }
