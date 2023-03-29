#ifndef ORDINALSCALE_H
#define ORDINALSCALE_H

#include "Model/MisureScale/ordinablescale.h"
#include <string>
#include <stdexcept>

using std::string;

class OrdinalScale: public OrdinableScale
{
protected:
    string attribute; // non può essere un valore numerico

    double numberLevel; // il valore numerico corrisponde ad un livello,
                     // per cui sono concesse solamente le operazioni logiche (==, < o >)
public:
    OrdinalScale();
    OrdinalScale(const string& att, double lev);
    ~OrdinalScale() =default;

    string getAttribute() const override;

    void changeAttribute(const string & att) override;

    double getNumberValue() const override;

    void changeNumberValue(double nv) override;

    bool operator==(const OrdinalScale & os) const;

    bool operator!=(const OrdinalScale & os) const;
};

#endif // ORDINALSCALE_H
