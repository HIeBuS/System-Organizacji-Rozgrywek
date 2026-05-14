#ifndef MECZ_H
#define MECZ_H

#include <string>
#include "Wydarzenie.h"
#include "Druzyna.h"

class Mecz : public Wydarzenie {
private:
    Druzyna* gospodarz;
    Druzyna* gosc;
    int goleGospodarza;
    int goleGoscia;
    bool czyRozegrany;

public:
    void ustawWynik(int goleGosp, int goleGosc);
    void rozegraj() override;
    std::string pobierzSzczegoly() override;
};

#endif