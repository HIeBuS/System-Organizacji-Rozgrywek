#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <windows.h>
#include "Liga.h"

using namespace std;

void Liga::dodajDruzyne(Druzyna d) {
    // unikniecie dodania druzyny o tej samej nazwie
    for (int i = 0; i < listaDruzyn.size(); i++) {
        if (listaDruzyn[i].pobierzNazwe() == d.pobierzNazwe()) {
            throw invalid_argument("Druzyna o takiej nazwie juz istnieje w lidze!");
        }
    }

    listaDruzyn.push_back(d);
    terminarz.clear();
}

void Liga::usunDruzyne(string nazwa) {
    for(auto it = listaDruzyn.begin(); it != listaDruzyn.end(); ++it){
        if(it->pobierzNazwe() == nazwa){
            listaDruzyn.erase(it);
            terminarz.clear();
            break;
        }
    }
}

void Liga::generujTerminarz() {
    terminarz.clear();

    int liczbaDruzyn = listaDruzyn.size();
    if (liczbaDruzyn < 2) return; // za malo druzyn na lige

    //ustalenie startu rozgrywek
    int rok, miesiac, dzien;

    cout << "\n--- USTAWIENIA STARTU ROZGRYWEK ---" << endl;
    while (true) {
        cout << "Podaj rok startu: ";
        cin >> rok;
        if(cin.fail() || rok < 1900 || rok > 2100) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "Blad: Niepoprawny rok! Sprobuj ponownie.\n"; 
            continue;
        }
        
        cout << "Podaj miesiac (1-12): ";
        cin >> miesiac;
        if(cin.fail() || miesiac < 1 || miesiac > 12) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "Blad: Miesiac musi byc liczba od 1 do 12!\n"; 
            continue;
        }

        cout << "Podaj dzien (1-30): ";
        cin >> dzien;
        if(cin.fail() || dzien < 1 || dzien > 30) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "Blad: Dzien musi byc liczba od 1 do 30!\n"; 
            continue;
        }
        
        cin.ignore(10000, '\n'); 
        break;
    }

    for (int i = 0; i < liczbaDruzyn; ++i) {
        dzien += 7; // Przeskok o tydzien dla calej kolejki
        
        if (dzien > 30) { //jesli kolejny miesiac
            dzien -= 30;
            miesiac++;
            if (miesiac > 12) { //jesli kolejny rok
                miesiac = 1;
                rok++;
            }
        }

        for (int j = i + 1; j < liczbaDruzyn; ++j) {
            //zroznicowanie meczy w ramach kolejki (przesunięcie o jeden dzien)
            int przesuniecie = (j % 3); 
            int ostatecznyDzien = dzien + przesuniecie;
            int ostatecznyMiesiac = miesiac;
            int ostatecznyRok = rok;

            //ewentualne przesuniecie na kolejny miesiac
            if (ostatecznyDzien > 30) {
                ostatecznyDzien -= 30;
                ostatecznyMiesiac++;
                if (ostatecznyMiesiac > 12) { 
                    ostatecznyMiesiac = 1; 
                    ostatecznyRok++; 
                }
            }

            //zlozenie stringa (YYYY-MM-DD)
            string dataTekst = to_string(ostatecznyRok) + "-";
            if (ostatecznyMiesiac < 10) dataTekst += "0";
            dataTekst += to_string(ostatecznyMiesiac) + "-";
            if (ostatecznyDzien < 10) dataTekst += "0";
            dataTekst += to_string(ostatecznyDzien);

            Mecz nowyMecz;
            nowyMecz.ustawDruzyny(&listaDruzyn[i], &listaDruzyn[j]);
            nowyMecz.ustawDate(dataTekst);
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
    if (nazwaGosp == nazwaGosc) {
        cout << "Blad: Druzyna nie moze grac sama ze soba!" << endl;
        return;
    }
    
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