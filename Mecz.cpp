#include <iostream>
#include <cstdlib>
#include <windows.h>
#include "Mecz.h"

using namespace std;

void Mecz::ustawWynik(int goleGosp, int goleGosc) {
}

void Mecz::ustawDruzyny(Druzyna* gosp, Druzyna* gosc){
    this->gospodarz = gosp;
    this->gosc = gosc;  
}

void Mecz::rozegraj() {
}

string Mecz::pobierzSzczegoly() {
    return "";
}