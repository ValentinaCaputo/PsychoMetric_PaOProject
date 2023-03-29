#include "ordinablescale.h"

OrdinableScale::OrdinableScale() {}

bool OrdinableScale::operator<(const OrdinableScale& os) const
{

    if (typeid(os)!= typeid(*this))
        throw std::runtime_error("Impossibile confrontare oggetti di scala diversa");


    return getNumberValue()<os.getNumberValue();
}

bool OrdinableScale::operator>(const OrdinableScale& os) const
{
    if (typeid(os)!= typeid(*this))
        throw std::runtime_error("Impossibile confrontare oggetti di scala diversa");

    return getNumberValue()>os.getNumberValue();
}
