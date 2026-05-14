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
    void ustawNazwe(std::string nowaNazwa);
    std::string pobierzNazwe();
    void dodajWynik(int strzelone, int stracone);
    int pobierzPunkty();
    int obliczBilans();
    bool operatorWyzszy(Druzyna inna);
};

#endif