//
// Created by Konrad Mrozowski on 01/06/2025.
//

#include "klasy.h"

// FIGURA______________________________________
figura::figura(string nazwa, int kodFigury, int x, int y):nazwa(nazwa),  kodFigury(kodFigury), pozycja(x,y){}
figura::~figura() = default;
void figura::ruchFigury(plansza& p) {
    int a,b;
    cout <<"Podaj współrzędne na które chcesz przenieść figurę: ";
    cin >> a >> b;
    cout<<endl;
    edytujPlansze(p,a,b);
}
void figura::edytujPlansze(plansza& p,int a, int b)
{
    int c = pozycja[0];
    int d = pozycja[1];
    p.tablicaPlanszy[c][d]= 0;
    pozycja[0]=a;
    pozycja[1]=b;
    p.tablicaPlanszy[a][b]=kodFigury;
}
//--------------------------------------



// PLANSZA---------------------------------
plansza::plansza()
{
    tura = true;


    tablicaPlanszy = {{
        {-7, -6, -5, -4, -1, -4, -5, -6, -7}, // Gracz 2 (wartości ujemne)
        {0, -2, 0, 0, 0, 0, 0, -3, 0},
        {-8, -8, -8, -8, -8, -8, -8, -8, -8},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {8, 8, 8, 8, 8, 8, 8, 8, 8},         // Gracz 1 (wartości dodatnie)
        {0, 3, 0, 0, 0, 0, 0, 2, 0},
        {7, 6, 5, 4, 1, 4, 5, 6, 7}
    }};

}
plansza::~plansza() = default;
void plansza::wyswietlPlansze() const
{
    for(int i = 0; i <= 8; i++) {
        for(int j = 0; j <= 8; j++) {
            cout << setw(2)<<tablicaPlanszy[i][j] << " ";
        }
        cout << endl;
    }
}
//_______________________________________________


bool isValidPosition(int x, int y) {
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE;


}
//GRACZ_________________________
gracz::gracz() {
    currentPlayer=1;

}
void gracz::setCurrent(int i) {
    currentPlayer=i;
}
int gracz::getCurrent() const {
    return currentPlayer;
}
//___________________________________________
/* Kody figur
 *  0 - puste pole
 *  1 - pionek
 *
 *
 *
 */