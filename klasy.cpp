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
