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
char figura::getSymbol() const { return  symbol; }
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

const int* figura::aktualnaPozycja() const
{
    return pozycja;
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
    tura = true;
    inicjalizujFigury();
}
plansza::~plansza() = default;

bool plansza::wczytajIWalidujRuch(int& toX, int& toY, int fromX, int fromY, int currentPlayer) const
{
     {
        if (!wczytajPozycjeDocelowa(toX, toY, currentPlayer)) {
            return false;
        }
        if (!isMoveValid(*this, fromX, fromY, toX, toY, currentPlayer)) {
            cout << "Nieprawidłowy ruch dla tej bierki!\n";
            return false;
        }
        return true;
    }
}
bool plansza::wczytajPozycjeDocelowa(int &toX, int &toY, int currentPlayer) const
{
    string input;
    cout << "Podaj docelową pozycję (x y) lub 'q' aby anulować: ";
    getline(cin, input);

    if (input == "q") {
        return false;
    }

    istringstream iss(input);
    if (!(iss >> toX >> toY)) {
        cerr << "Nieprawidłowy format! Wprowadź dwie liczby (np. '3 5').\n";
        return false;
    }

    toX--;
    toY--;

    if (!isValidPosition(toX, toY)) {
        cout << "Nieprawidłowa pozycja docelowa!\n";
        return false;
    }

    string target = getPole(toX, toY);
    if (target != ".") {
        if ((isUpper(target) && currentPlayer == 1) ||
            (isLower(target) && currentPlayer == 2)) {
            cout << "Nie możesz zbić własnej bierki!\n";
            return false;
            }
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
}


// GRACZ_________________________________________
gracz::gracz() { currentPlayer = 1; }
gracz::~gracz() = default;
void gracz::setCurrent(int i) { currentPlayer = i; }
int gracz::getCurrent() const { return currentPlayer; }
