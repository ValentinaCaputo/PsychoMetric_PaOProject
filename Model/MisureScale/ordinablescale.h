#ifndef ORDINABLESCALE_H
#define ORDINABLESCALE_H

#include "Model/MisureScale/misurescale.h"

#include <stdexcept>
#include <typeinfo>

class OrdinableScale: public MisureScale
{
public:
    OrdinableScale();
    ~OrdinableScale() =default;

    /**
     * @brief operator <    verifica relazione di minoranza tra l'oggetto e os;
     * @param os            oggetto di paragone;
     * @return              restituisce true sse this < os.
     */
    virtual bool operator<(const OrdinableScale& os) const;

    /**
     * @brief operator <    verifica relazione di maggioranza tra l'oggetto e os;
     * @param os            oggetto di paragone;
     * @return              restituisce true sse this > os.
     */
    virtual bool operator>(const OrdinableScale& os) const;
};

#endif // ORDINABLESCALE_H
