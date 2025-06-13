//
// Created by Konrad Mrozowski & Mateusz Pietrzak on 01/06/2025
// UPDATED 12/06/2025
//

#ifndef KLASY_H
#define KLASY_H

#include <iostream>
#include <string>
#include <array>
#include <sstream>
#include <cmath>
#include <algorithm>
using namespace std;

const int SIZE = 9;

class plansza;
class gracz;

// FIGURA____________________________________________
class figura {
private:
    string nazwa;
    char symbol;
    bool promowana;
    int gracz;
    int pozycja[2];
public:
    figura(char symbol, int x, int y);
    virtual ~figura();
    char getSymbol() const;
    int getGracz() const;
    bool isPromoted() const;
    void promuj();
    int pozycjaX() const;
    int pozycjaY() const;
    void ustawPozycje(int x, int y);
    const int* aktualnaPozycja() const;

};
//________________________________________________________




// PLANSZA______________________________________________
class plansza {
private:
    array<array<string, SIZE>, SIZE> tablicaPlanszy;
    bool tura;
    vector<figura> figury;
public:
    plansza();
    ~plansza();
    void wyswietlPlansze() const;
    string getPole(int x, int y) const;
    void setPole(int x, int y, const string& val);
    void inicjalizujFigury();
    figura* znajdzFigure(int x, int y);
    bool wczytajPozycjeDocelowa(int& toX, int& toY, int currentPlayer) const;
    bool wczytajIWalidujRuch(int& toX, int& toY, int fromX, int fromY, int currentPlayer) const;
    bool czySzach(int gracz) const;
    bool czyMat(int gracz);
    bool usunFigure(int x, int y);

    bool polozBierkeZReki(gracz &g, int x, int y);

};
//________________________________________________________




// GRACZ_________________________________________________
class gracz {
private:
    int currentPlayer;
    array<vector<string>, 2> reka;
public:
    gracz();
    ~gracz();
    int getCurrent() const;
    void setCurrent(int i);
    void dodajDoReki(string& figura);
    void wyswietlReke() const;
    const vector<string>& getReka() const;
    bool czyRekaPusta() const;
    bool usunZReki(const string& bierka);
    void procesujBierkeDoReki(string& bierka);
};







//________________
bool isValidPosition(int x, int y );
bool isUpper(const string& s);
bool isLower(const string& s);
bool pozycjaBierki(int& x, int& y,gracz g1);

// WALIDACJA RUCHU FIGUR SZOGI
bool isMoveValid(const plansza& p, int fromX, int fromY, int toX, int toY, int currentPlayer);

// PROMOCJA SZOGI
bool isPromotionZone(int y, int player);
bool canPromote(const std::string& piece);
bool mustPromote(const std::string& piece, int toY, int player);
std::string promotePiece(const std::string& piece);
#endif //KLASY_H
