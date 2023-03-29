#ifndef NOMINALSCALE_H
#define NOMINALSCALE_H

#include "Model/MisureScale/misurescale.h"

#include <stdexcept>
#include <string>
using std::string;

class NominalScale : public MisureScale
{
protected:
    string attribute; // non deve essere un numero

    int numberLabel; // nella scala nominale il valore numerico ha la sola valenza di etichetta,
                     // possibile soltanto il confronto di uguaglianza, non sono ammesse operazioni aritmetiche


public:
    NominalScale();
    NominalScale(const string& att, int lab = -99);
    ~NominalScale() =default;

    string getAttribute() const override;

    void changeAttribute(const string & att) override;

    double getNumberValue() const override;

    void changeNumberValue(double nv) override;

    bool operator==(const NominalScale & ns) const;

    bool operator!=(const NominalScale & ns) const;
};

#endif // NOMINALSCALE_H
