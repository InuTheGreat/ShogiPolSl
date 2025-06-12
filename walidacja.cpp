//
// Created by Konrad Mrozowski & Mateusz Pietrzak on 12/06/2025
// UPDATED 12/06/2025
//
#include "klasy.h"
// WALIDACJA POZYCJI_____________________________
bool isValidPosition(int x, int y) {
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
}

bool isUpper(const string& s) {
    if (!s.empty() && s[0] == '+')
    {
        return !s.empty() && s[1] >= 'A' && s[1] <= 'Z';
    }
    else
    {
        return !s.empty() && s[0] >= 'A' && s[0] <= 'Z';
    }

}

bool isLower(const string& s) {
    if (!s.empty() && s[0] == '+')
    {
        return !s.empty() && s[1] >= 'a' && s[1] <= 'z';
    }
    else
    {
        return !s.empty() && s[0] >= 'a' && s[0] <= 'z';
    }

}

bool pozycjaBierki(int& x, int& y,gracz g1) {
    string input;
    cout << "Podaj pozycję bierki (x y) lub 'q' aby wyjść: ";
    getline(cin, input);
    if (input == "q")
    {
        cout <<endl<< "Gracz "<<g1.getCurrent()<<" się poddał" << endl;
        cout << "Wygrał gracz: "<<3 - g1.getCurrent()<<endl;
        return false;
    }

    istringstream iss(input);

    if (iss >> x >> y) {
        string remaining;
        if (!(iss >> remaining)) {
            x--; y--;
            return true;
        }
    }
    cerr<<endl<< "Nieprawidłowe dane! Wprowadź tylko dwie liczby lub 'q'.\n";
    cin.clear();
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
    if (piece[0] == '+')  //type = tolower(piece[1]); // promowana bierka
    {
        if (tolower(piece[1]) == 'p' ||
            tolower(piece[1]) == 'l' ||
            tolower(piece[1]) == 'n' ||
            tolower(piece[1]) == 's')
        {
            type = 'g';
        }
    }

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
        case 'n': // Koń (Skoczek)
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

bool canPromote(const string& piece) {
    char c = tolower(piece[0]);
    if (piece[0] == '+') return false; // już promowana
    return c == 'p' || c == 'l' || c == 'n' || c == 's' || c == 'b' || c == 'r';
}

bool mustPromote(const string& piece, int toY, int player) {
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

string promotePiece(const string& piece) {
    if (piece[0] == '+') return piece; // już promowana
    char c = piece[0];
    return "+" + string(1, c);
}