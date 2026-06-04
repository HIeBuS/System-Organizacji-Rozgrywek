#include <iostream>
#include <cstdlib>
#include <windows.h>
#include "Wydarzenie.h"

using namespace std;

void Wydarzenie::ustawDate(string data) {
    dataWydarzenia = data;
}

string Wydarzenie::pobierzSzczegoly() {
    return "Data wydarzenia: " + dataWydarzenia;
}