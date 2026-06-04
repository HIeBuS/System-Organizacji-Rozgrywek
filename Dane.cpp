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
        plik << d.pobierzPunkty() << endl;
        plik << d.pobierzBramkiStrzelone() << endl;
        plik << d.pobierzBramkiStracone() << endl;
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
    
    string nazwa, pktStr, strzStr, stracStr;
    while (getline(plik, nazwa)) {
        if (nazwa.empty()) continue; 
        if (nazwa.back() == '\r') nazwa.pop_back(); 
        
        getline(plik, pktStr);
        getline(plik, strzStr);
        getline(plik, stracStr);
        
        Druzyna d;
        d.ustawNazwe(nazwa);
        d.ustawStatystyki(stoi(pktStr), stoi(strzStr), stoi(stracStr));
        nowaLiga.dodajDruzyne(d);
    }
    
    plik.close();
    return nowaLiga;
}