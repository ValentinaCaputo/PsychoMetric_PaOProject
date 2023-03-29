#ifndef INTERVALSCALE_H
#define INTERVALSCALE_H

#include "Model/MisureScale/quantitativescale.h"
#include <cctype>
#include <cmath>

class IntervalScale: public QuantitativeScale
{
protected:
    //l'attributo della scala a intervalli coincide con il valore numerico per cui può essere omesso
    double numberValue; //numero discreto o continuo che può assumere qualsiasi valore

public:
    IntervalScale();
    IntervalScale(double nv);
    ~IntervalScale() =default;

    string getAttribute() const override;

    void changeAttribute(const string & att) override;

    double getNumberValue() const override;

    void changeNumberValue(double nv) override;
};

#endif // INTERVALSCALE_H
