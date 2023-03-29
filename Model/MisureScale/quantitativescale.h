#ifndef QUANTITATIVESCALE_H
#define QUANTITATIVESCALE_H

#include "Model/MisureScale/ordinablescale.h"

class QuantitativeScale: public OrdinableScale
{
public:
    QuantitativeScale();
    ~QuantitativeScale() =default;

    /**
     * @brief operator +    somma i valori numerici di this e obj;
     * @param obj           addendo dell'operazione di somma;
     * @return              restituisce il risultato della somma.
     */
    virtual double operator+(const QuantitativeScale & obj) const;

    /**
     * @brief operator -    sottrae i valori numerici di this e obj;
     * @param obj           sottraendo dell'operazione di sottrazione;
     * @return              restituisce il risultato della sottrazione.
     */
    virtual double operator-(const QuantitativeScale & obj) const;
};

#endif // QUANTITATIVESCALE_H
