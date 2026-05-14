#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>
#include "Liga.h"
#include "Dane.h"

class Interface {
private:
    Liga aktualnaLiga;
    Dane obslugaDanych;

public:
    void uruchomMenuGlowne();
    int wczytajWyborUzytkownika();
    void wyswietlTabeleLigowa();
    void pokazKomunikat(std::string wiadomosc);
};

#endif