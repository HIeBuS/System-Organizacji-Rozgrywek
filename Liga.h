#ifndef LIGA_H
#define LIGA_H

#include <vector>
#include <string>
#include "Druzyna.h"
#include "Mecz.h"

class Liga {
private:
    std::vector<Druzyna> listaDruzyn;
    std::vector<Mecz> terminarz;

public:
    void dodajDruzyne(Druzyna d);
    void usunDruzyne(std::string nazwa);
    void generujTerminarz();
    void posortujTabele();
    std::vector<Druzyna> pobierzTabele();
    void rozegrajSpotkanie(std::string nazwaGosp, std::string nazwaGosc, int goleGosp, int goleGosc);
};

#endif