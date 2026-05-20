#include <iostream>
#include <cstdlib>
#include <algorithm>
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
    terminarz.clear();

    int liczbaDruzyn = listaDruzyn.size();
    if (liczbaDruzyn < 2) return; // za malo druzyn na lige

    for (int i = 0; i < liczbaDruzyn; ++i) {
        for (int j = i + 1; j < liczbaDruzyn; ++j) {
            Mecz nowyMecz;
            nowyMecz.ustawDruzyny(&listaDruzyn[i], &listaDruzyn[j]);
            nowyMecz.ustawDate("2026-05-21");
            terminarz.push_back(nowyMecz);
        }
    }
}

void Liga::posortujTabele() {
    std::sort(listaDruzyn.begin(), listaDruzyn.end(), [](Druzyna& a, Druzyna& b) {
        return a.operatorWyzszy(b);
    });
}

vector<Druzyna> Liga::pobierzTabele() {
    return vector<Druzyna>();
}