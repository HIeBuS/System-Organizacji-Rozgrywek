#include <iostream>
#include <cstdlib>
#include <windows.h>
#include "Liga.h"

using namespace std;

void Liga::dodajDruzyne(Druzyna d) {
    listaDruzyn.push_back(d);
}

void Liga::usunDruzyne(string nazwa) {
    for(auto it = listaDruzyn.begin(); it != listaDruzyn.end(); ++it){
        if(it->pobierzNazwe() == nazwa){
            listaDruzyn.erase(it);
            break;
        }
    }
}

void Liga::generujTerminarz() {
}

void Liga::posortujTabele() {
}

vector<Druzyna> Liga::pobierzTabele() {
    return vector<Druzyna>();
}