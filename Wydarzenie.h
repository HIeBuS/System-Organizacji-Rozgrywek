#ifndef WYDARZENIE_H
#define WYDARZENIE_H

#include <string>

class Wydarzenie {
private:
    std::string dataWydarzenia;

public:
    void ustawDate(std::string data);
    virtual void rozegraj() = 0;
    virtual std::string pobierzSzczegoly();
    virtual ~Wydarzenie() {}
};

#endif