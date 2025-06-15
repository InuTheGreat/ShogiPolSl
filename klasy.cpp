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
bool plansza::usunFigure(int x, int y) {
    for (auto it = figury.begin(); it != figury.end(); ++it) {
        if (it->pozycjaX() == x && it->pozycjaY() == y) {
            figury.erase(it);
            return true;
        }
    }
    return false;
}
bool plansza::polozBierkeZReki(gracz& g, int x, int y) {
    if (g.czyRekaPusta()) {
        return false;
    }

    cout << "Wybierz bierkę do położenia (lub 'q' aby anulować): ";

    string bierka;
    getline(cin, bierka);

    if (bierka == "q") {
        return false;
    }

    if (!isValidPosition(x, y)) {
        cout << "Nieprawidłowa pozycja!\n";
        return false;
    }

    if (getPole(x, y) != ".") {
        cout << "Pozycja jest już zajęta!\n";
        return false;
    }

    if (!g.usunZReki(bierka)) {
        cout << "Nie masz tej bierki w ręce!\n";
        return false;
    }

    // Sprawdź specjalne zasady dla pionków, lance i skoczków
    char typ = tolower(bierka[0]);
    int graczNr = g.getCurrent();

    if (typ == 'p') {
        if ((graczNr == 1 && y == 0) || (graczNr == 2 && y == SIZE-1)) {
            cout << "Pion nie może być postawiony w ostatnim rzędzie!\n";
            g.dodajDoReki(bierka); // Zwróć bierkę do ręki
            return false;
        }

        for (int i = 0; i < SIZE; i++) {
            string pole = getPole(x, i);
            if (pole == (graczNr == 1 ? "P" : "p")) {
                cout << "Nie możesz mieć dwóch pionków w tej samej kolumnie!\n";
                g.dodajDoReki(bierka); // Zwróć bierkę do ręki
                return false;
            }
        }
    }
    else if (typ == 'l') {
        if ((graczNr == 1 && y == 0) || (graczNr == 2 && y == SIZE-1)) {
            cout << "Lanca nie może być postawiona w ostatnim rzędzie!\n";
            g.dodajDoReki(bierka); // Zwróć bierkę do ręki
            return false;
        }
    }
    else if (typ == 'n') {
        if ((graczNr == 1 && (y == 0 || y == 1)) ||
            (graczNr == 2 && (y == SIZE-1 || y == SIZE-2))) {
            cout << "Skoczek nie może być postawiony w dwóch ostatnich rzędach!\n";
            g.dodajDoReki(bierka); // Zwróć bierkę do ręki
            return false;
        }
    }

    // Wszystkie warunki spełnione - połóż bierkę
    setPole(x, y, bierka);
    figury.emplace_back(bierka[0], x, y);

    return true;
}


// GRACZ_________________________________________
gracz::gracz() { currentPlayer = 1; }
gracz::~gracz() = default;
void gracz::setCurrent(int i) { currentPlayer = i; }
int gracz::getCurrent() const { return currentPlayer; }
void gracz::dodajDoReki(string& figura) {

    reka[currentPlayer-1].push_back(figura);
}

void gracz::wyswietlReke() const {
    cout << "Reka gracza " << currentPlayer << ": ";
    if (reka[currentPlayer-1].empty()) {
        cout << "pusta";
    } else {
        for (const auto& f : reka[currentPlayer-1]) {
            cout << f << " ";
        }
    }
    cout << endl;
}
const vector<string>& gracz::getReka() const {
    return reka[currentPlayer-1];
}

bool gracz::czyRekaPusta() const {
    return reka[currentPlayer-1].empty();
}

bool gracz::usunZReki(const string& bierka) {
    auto& graczReka = reka[currentPlayer-1];
    auto it = find(graczReka.begin(), graczReka.end(), bierka);
    if (it != graczReka.end()) {
        graczReka.erase(it);
        return true;
    }
    return false;
}
void gracz::procesujBierkeDoReki(string &bierka)
{
    if (!bierka.empty() && bierka[0] == '+') {
        bierka.erase(0, 1);
    }

    // Zamień wielkość liter w zależności od gracza
    if (currentPlayer == 1) {
        transform(bierka.begin(), bierka.end(), bierka.begin(), ::toupper);
    } else {
        transform(bierka.begin(), bierka.end(), bierka.begin(), ::tolower);
    }
}
