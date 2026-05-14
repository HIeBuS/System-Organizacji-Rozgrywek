#ifndef DANE_H
#define DANE_H

#include <string>
#include "Liga.h"

class Dane {
private:
    void rzucWyjatekBrakPliku(std::string sciezka);

public:
    void zapiszStanLigi(Liga l, std::string sciezka);
    Liga wczytajStanLigi(std::string sciezka);
};

#endif