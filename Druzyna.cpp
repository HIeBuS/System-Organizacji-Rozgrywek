#include <iostream>
#include <cstdlib>
#include <windows.h>
#include "Druzyna.h"

using namespace std;

Druzyna::Druzyna() {
    nazwa = "Nieznana";
    punkty = 0; 
    bramkiStrzelone = 0;
    bramkiStracone = 0;
}

void Druzyna::ustawNazwe(string nowaNazwa) {
    nazwa = nowaNazwa;
}

string Druzyna::pobierzNazwe() {
    return nazwa;
}

void Druzyna::dodajWynik(int strzelone, int stracone) {
    bramkiStrzelone += strzelone;
    bramkiStracone += stracone;

    if(strzelone > stracone) {
        punkty += 3; //wygrana
    } else if (strzelone == stracone){
        punkty += 1; //remis
    }
    //przegrana
}

int Druzyna::pobierzPunkty() {
    return punkty;
}

int Druzyna::obliczBilans() {
    return bramkiStrzelone - bramkiStracone;
}

bool Druzyna::operatorWyzszy(Druzyna inna) {
    if(punkty != inna.pobierzPunkty()) {
        return punkty > inna.pobierzPunkty();
    }
    return obliczBilans() > inna.obliczBilans();
}