#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <string>
#include "Mecz.h"

using namespace std;

//domyślny konstruktor resetujący wartości początkowe
Mecz::Mecz() {
    gospodarz = nullptr;
    gosc = nullptr;
    goleGospodarza = 0;
    goleGoscia = 0;
    czyRozegrany = false;
}

//Ustawianie danych poczatkowych
void Mecz::ustawWynik(int goleGosp, int goleGosc) {
    goleGospodarza = goleGosp;
    goleGoscia = goleGosc;
    czyRozegrany = true; 
}

void Mecz::ustawDruzyny(Druzyna* gosp, Druzyna* goscZespol){
    this->gospodarz = gosp;
    this->gosc = goscZespol;  
}

//Logika fizycznego rozegrania meczu
void Mecz::rozegraj() {
    if (gospodarz != nullptr && gosc != nullptr) {
        gospodarz->dodajWynik(goleGospodarza, goleGoscia);
        gosc->dodajWynik(goleGoscia, goleGospodarza);
    }
}

//Polimorfizm - nadpisywanie szczegółów meczu
string Mecz::pobierzSzczegoly() {
    string infoOData = Wydarzenie::pobierzSzczegoly(); 

    if (czyRozegrany) {
        return gospodarz->pobierzNazwe() + " " + to_string(goleGospodarza) + ":" + to_string(goleGoscia) + " " + gosc->pobierzNazwe() + " (" + infoOData + ")";
    } else {
        return gospodarz->pobierzNazwe() + " vs " + gosc->pobierzNazwe() + " [Zaplanowany | " + infoOData + "]";
    }
}