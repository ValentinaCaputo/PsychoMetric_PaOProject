#ifndef RATIOSCALE_H
#define RATIOSCALE_H



#include "Model/MisureScale/quantitativescale.h"

class RatioScale: public QuantitativeScale
{
protected:
    //l'attributo della scala a rapporti coincide con il valore numerico per cui può essere omesso
    double numberValue; //numero discreto o continuo che può assumere soltanto valori >=0

public:
    RatioScale();
    RatioScale(double nv);
    ~RatioScale() =default;

    string getAttribute() const override;

    void changeAttribute(const string & att) override;

    double getNumberValue() const override;

    void changeNumberValue(double nv) override;


    /**
     * @brief operator *    overloading dell'operazione di moltiplicazione;
     * @param obj           moltiplicatore;
     * @return              risultato della moltiplicazione.
     */
    virtual RatioScale operator * (const RatioScale & obj) const;

    /**
     * @brief operator /    overloading dell'operazione di divisione;
     * @param obj           divisore;
     * @return              risultato della divisione.
     */
    virtual RatioScale operator / (const RatioScale & obj) const;
};

#endif // RATIOSCALE_H
