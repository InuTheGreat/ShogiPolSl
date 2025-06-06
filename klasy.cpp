//
// Created by Konrad Mrozowski on 01/06/2025.
//

#include "klasy.h"

figura::figura(string nazwa, int kodFigury, int x, int y):nazwa(nazwa),  kodFigury(kodFigury), pozycja(x,y){}
figura::~figura() = default;






plansza::plansza()
{
    tura = true;
    ifstream planszaFile;
    planszaFile.open("../plansza.txt");
    if(planszaFile.is_open())
        {
        for(int i = 0; i <= 8; i++)
            {
            for(int j = 0; j <= 8; j++)
            {
                planszaFile >> rozmiarPlanszy[i][j];
            }
        }
    }
    else
    {
        cerr<<"Błąd otwierania pliku!"<<endl;
        exit(1);
    }
    planszaFile.close();
}
plansza::~plansza() = default;
void plansza::wyswietlPlansze() {
    for(int i = 0; i <= 8; i++) {
        for(int j = 0; j <= 8; j++) {
            cout << rozmiarPlanszy[i][j] << " ";
        }
        cout << endl;
    }
}


/* Kody figur
 *  0 - puste pole
 *  1 - pionek
 *
 *
 *
 */