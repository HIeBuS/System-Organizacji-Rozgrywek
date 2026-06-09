#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <iomanip>
#include <sstream>
#include "Interface.h"

using namespace std;

//obsluga menu glownego
void Interface::uruchomMenuGlowne() {
    while (true) {
        system("cls");
        cout << "--- SYSTEM ORGANIZACJI ROZGRYWEK ---"<<endl;
        cout << "1. Dodaj druzyne"<<endl;
        cout << "2. Usun druzyne"<<endl;
        cout << "3. Wyswietl tabele ligowa"<<endl;
        cout << "4. Rozegraj mecz"<<endl;
        cout << "5. Generuj terminarz"<<endl;
        cout << "6. Wyswietl terminarz"<<endl;
        cout << "7. Zapisz stan ligi"<<endl;
        cout << "8. Wczytaj stan ligi"<<endl;
        cout << "0. Zakoncz"<<endl;
        
        int wybor = wczytajWyborUzytkownika();
        string pauza;
        
        //reakcja na wybor uzytkownika
        switch (wybor) {
            case 1: {
                string wpisaneNazwy;
                cout << "Podaj nazwe druzyny (lub kilka oddzielonych przecinkiem): ";
                getline(cin, wpisaneNazwy); 
                
                stringstream ss(wpisaneNazwy);
                string nazwa;

                while (getline(ss, nazwa, ',')) {
                    if (!nazwa.empty() && nazwa[0] == ' ') nazwa.erase(0, 1); 

                    try {
                        Druzyna d;
                        d.ustawNazwe(nazwa); 
                        aktualnaLiga.dodajDruzyne(d); 
                        cout << "Dodano: " << nazwa << endl;
                    } catch (const exception& e) {
                        cout << "Blad (" << nazwa << "): " << e.what() << endl;
                    }
                }
                
                cout << "\nWcisnij Enter, aby kontynuowac...";
                getline(cin, pauza);
                break;
            }

            case 2: {
                string wpisaneNazwy;
                cout << "Podaj nazwe druzyny do usuniecia (lub kilka oddzielonych przecinkiem): ";
                getline(cin, wpisaneNazwy); 
                
                stringstream ss(wpisaneNazwy);
                string nazwa;

                while (getline(ss, nazwa, ',')) {
                    if (!nazwa.empty() && nazwa[0] == ' ') nazwa.erase(0, 1); 

                    aktualnaLiga.usunDruzyne(nazwa); 
                    cout << "Usunieto: " << nazwa << endl;
                }
                
                cout << "\nWcisnij Enter, aby kontynuowac...";
                getline(cin, pauza);
                break;
            }

            case 3:
                wyswietlTabeleLigowa();
                break;

            case 4: {
                //pobieranie danych meczowych
                string gosp, gosc;
                int goleGosp, goleGosc;
                
                cout << "Podaj nazwe druzyny gospodarzy: ";
                getline(cin, gosp);
                cout << "Podaj nazwe druzyny gosci: ";
                getline(cin, gosc);
                
                //walidacja wpisanych goli
                cout << "Podaj liczbe goli gospodarzy: ";
                cin >> goleGosp;
                if(cin.fail()) { 
                    cin.clear(); 
                    cin.ignore(10000, '\n'); 
                    cout << "\nBlad! Podano nieprawidlowa wartosc" << endl;
                    cout << "Wcisnij Enter, aby kontynuowac..."; 
                    getline(cin, pauza); 
                    break; 
                }
                
                cout << "Podaj liczbe goli gosci: ";
                cin >> goleGosc;
                if(cin.fail()) { 
                    cin.clear(); 
                    cin.ignore(10000, '\n'); 
                    cout << "\nBlad! Podano nieprawidlowa wartosc" << endl;
                    cout << "Wcisnij Enter, aby kontynuowac..."; 
                    getline(cin, pauza); 
                    break; 
                }
                cin.ignore(10000, '\n');
                
                //przekazanie do silnika ligi
                aktualnaLiga.rozegrajSpotkanie(gosp, gosc, goleGosp, goleGosc);
                
                cout << "Wcisnij Enter, aby kontynuowac...";
                getline(cin, pauza);
                break;
            }

            case 5:
                aktualnaLiga.generujTerminarz();
                cout << "\nTerminarz zostal pomyslnie wygenerowany!" << endl;
                cout << "Wcisnij Enter, aby kontynuowac...";
                getline(cin, pauza);
                break;

            case 6:
                cout << endl;
                aktualnaLiga.wyswietlTerminarz();
                cout << "\nWcisnij Enter, aby kontynuowac...";
                getline(cin, pauza);
                break;

            case 7: {
                string nazwaPlikuZapisu;
                cout << "Podaj nazwe pliku do zapisu: ";
                getline(cin, nazwaPlikuZapisu);
                
                try {
                    obslugaDanych.zapiszStanLigi(aktualnaLiga, nazwaPlikuZapisu);
                    cout << "\nZapisano stan ligi do pliku: " << nazwaPlikuZapisu << endl;
                } catch (const exception& e) {
                    cout << "\nBlad zapisu: " << e.what() << endl;
                }
                
                cout << "Wcisnij Enter, aby kontynuowac...";
                getline(cin, pauza);
                break;
            }

            case 8: {
                string nazwaPliku;
                cout << "Podaj nazwe pliku: ";
                getline(cin, nazwaPliku);
                try {
                    aktualnaLiga = obslugaDanych.wczytajStanLigi(nazwaPliku);
                    cout << "\nWczytano stan ligi z pliku" << endl;
                } catch (const exception& e) {
                    cout << "\n" << e.what() << endl;
                }
                cout << "Wcisnij Enter, aby kontynuowac...";
                getline(cin, pauza);
                break;
            }

            case 0:
                exit(0);
                break;
            default:
                cout << "\nNieznana opcja, sprobuj ponownie!" << endl;
                cout << "Wcisnij Enter, aby kontynuowac...";
                getline(cin, pauza);
                break;
        }
    }
}

//zabezpieczenie przed wpisaniem zlych znakow
int Interface::wczytajWyborUzytkownika() {
    int wybor;
    cout << "Wybierz opcje: ";
    cin >> wybor;
    if(cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        return -1;
    }
    cin.ignore(10000, '\n'); // Czysci bufor po wpisaniu cyfry z menu
    return wybor;
}

//formatowanie i wyswietlanie tabeli
void Interface::wyswietlTabeleLigowa() {
    system("cls");
    aktualnaLiga.posortujTabele();
    vector<Druzyna> tabela = aktualnaLiga.pobierzTabele();
    
    cout << "---------------------------------------------------------"<<endl;
    cout << left << setw(5) << "Msc" << setw(30) << "Druzyna" << setw(10) << "Punkty" << "Bilans"<<endl;
    cout << "---------------------------------------------------------"<<endl;
    
    int pozycja = 1;
    for (Druzyna d : tabela) {
        cout << left << setw(5) << pozycja 
             << setw(30) << d.pobierzNazwe() 
             << setw(10) << d.pobierzPunkty() 
             << d.obliczBilans()<<endl;
        pozycja++;
    }
    cout << "---------------------------------------------------------"<<endl;
    
    string pauza;
    cout << "Wcisnij Enter, aby wrocic do menu...";
    getline(cin, pauza);
}