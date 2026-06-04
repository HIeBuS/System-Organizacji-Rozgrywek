#ifndef DRUZYNA_H
#define DRUZYNA_H

#include <string>

class Druzyna {
private:
    std::string nazwa;
    int punkty;
    int bramkiStrzelone;
    int bramkiStracone;

public:
    Druzyna();
    void ustawNazwe(std::string nowaNazwa);
    std::string pobierzNazwe() const; 
    void dodajWynik(int strzelone, int stracone);
    int pobierzPunkty() const;
    int obliczBilans() const;
    bool operatorWyzszy(Druzyna inna) const;
    int pobierzBramkiStrzelone() const;
    int pobierzBramkiStracone() const;
    void ustawStatystyki(int pkt, int strzelone, int stracone);
};

#endif