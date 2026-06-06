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
    return listaDruzyn;
}

void Liga::rozegrajSpotkanie(string nazwaGosp, string nazwaGosc, int goleGosp, int goleGosc) {
    Druzyna* wskaznikGosp = nullptr;
    Druzyna* wskaznikGosc = nullptr;

    // Przeszukujemy liste druzyn
    for (int i = 0; i < listaDruzyn.size(); i++) {
        if (listaDruzyn[i].pobierzNazwe() == nazwaGosp) {
            wskaznikGosp = &listaDruzyn[i]; // zapisujemy gospodarza
        }
        if (listaDruzyn[i].pobierzNazwe() == nazwaGosc) {
            wskaznikGosc = &listaDruzyn[i]; // zapisujemy goscia
        }
    }

    if (wskaznikGosp != nullptr && wskaznikGosc != nullptr) {
        Mecz spotkanie;
        spotkanie.ustawDruzyny(wskaznikGosp, wskaznikGosc);
        spotkanie.ustawWynik(goleGosp, goleGosc);
        spotkanie.rozegraj(); 
        
        cout << "Wynik meczu zostal pomyslnie dopisany!" << endl;
    } else {
        cout << "Blad: Przynajmniej jedna z druzyn nie istnieje w lidze." << endl;
    }
}

void Liga::wyswietlTerminarz() {
    if (terminarz.size() == 0) {
        cout << "Terminarz jest pusty. Wygeneruj go najpierw." << endl;
        return;
    }

    cout << "--- TERMINARZ ROZGRYWEK ---" << endl;
    
    int numer = 1; // numeracja
    
    // wypisywanie terminarzu
    for (int i = 0; i < terminarz.size(); i++) {
        cout << numer << ". " << terminarz[i].pobierzSzczegoly() << endl;
        numer++;
    }
}