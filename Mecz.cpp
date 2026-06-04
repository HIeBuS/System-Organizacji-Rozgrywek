#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <string>
#include "Mecz.h"

using namespace std;

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
    // TODO: wywolac dodajWynik() dla gospodarza i goscia
}

//Polimorfizm - nadpisywanie szczegółów meczu
string Mecz::pobierzSzczegoly() {
    if (czyRozegrany) {
        return gospodarz->pobierzNazwe() + " " + to_string(goleGospodarza) + ":" + to_string(goleGoscia) + " " + gosc->pobierzNazwe();
    } else {
        return gospodarz->pobierzNazwe() + " vs " + gosc->pobierzNazwe() + " (Zaplanowany)";
    }
}