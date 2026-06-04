#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <stdexcept> 
#include "Druzyna.h"

using namespace std;

Druzyna::Druzyna() {
    nazwa = "Nieznana";
    punkty = 0; 
    bramkiStrzelone = 0;
    bramkiStracone = 0;
}

//Zarzadzanie nazwa z zabezpieczeniem
void Druzyna::ustawNazwe(string nowaNazwa) {
    if (nowaNazwa.empty()) { 
        throw invalid_argument("Nazwa druzyny nie moze byc pusta!");
    }
    nazwa = nowaNazwa;
}

string Druzyna::pobierzNazwe() const {
    return nazwa;
}

//Logika meczowa i matematyka ligowa
void Druzyna::dodajWynik(int strzelone, int stracone) {
    if (strzelone < 0 || stracone < 0) { 
        throw invalid_argument("Liczba bramek nie moze byc ujemna!");
    }

    bramkiStrzelone += strzelone;
    bramkiStracone += stracone;

    if(strzelone > stracone) {
        punkty += 3; //wygrana
    } else if (strzelone == stracone){
        punkty += 1; //remis
    }
    //przegrana
}

int Druzyna::pobierzPunkty() const {
    return punkty;
}

int Druzyna::obliczBilans() const {
    return bramkiStrzelone - bramkiStracone;
}

//Kryteria sortowania w tabeli
bool Druzyna::operatorWyzszy(Druzyna inna) const {
    if(punkty != inna.pobierzPunkty()) {
        return punkty > inna.pobierzPunkty();
    }
    return obliczBilans() > inna.obliczBilans();
}

int Druzyna::pobierzBramkiStrzelone() const {
    return bramkiStrzelone;
}

int Druzyna::pobierzBramkiStracone() const {
    return bramkiStracone;
}

void Druzyna::ustawStatystyki(int pkt, int strzelone, int stracone) {
    punkty = pkt;
    bramkiStrzelone = strzelone;
    bramkiStracone = stracone;
}