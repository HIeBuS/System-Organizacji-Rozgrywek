#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include <stdexcept>
#include "Dane.h"

using namespace std;

//obsluga wyjatkow
void Dane::rzucWyjatekBrakPliku(string sciezka) {
    throw runtime_error("Nie mozna otworzyc pliku " + sciezka);
}

//zapis do pliku
void Dane::zapiszStanLigi(Liga l, string sciezka) {
    ofstream plik(sciezka);
    if (!plik.is_open()) {
        rzucWyjatekBrakPliku(sciezka);
    }
    
    vector<Druzyna> tabela = l.pobierzTabele();
    for (Druzyna d : tabela) {
        plik << d.pobierzNazwe() << endl;
    }
    plik.close();
}

//odczyt z pliku
Liga Dane::wczytajStanLigi(string sciezka) {
    Liga nowaLiga;
    ifstream plik(sciezka);
    
    if (!plik.is_open()) {
        rzucWyjatekBrakPliku(sciezka);
    }
    
    string nazwa;
    while (getline(plik, nazwa)) {
        Druzyna d;
        d.ustawNazwe(nazwa);
        nowaLiga.dodajDruzyne(d);
    }
    
    plik.close();
    return nowaLiga;
}