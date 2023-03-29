#include "quantitativescale.h"

QuantitativeScale::QuantitativeScale()
{

}

double QuantitativeScale::operator+(const QuantitativeScale &obj) const
{
    if (typeid(obj)!= typeid(*this))
        throw std::runtime_error("Impossibile confrontare oggetti di scala diversa");

    return getNumberValue()+obj.getNumberValue();
}

double QuantitativeScale::operator-(const QuantitativeScale &obj) const
{
    if (typeid(obj)!= typeid(*this))
        throw std::runtime_error("Impossibile confrontare oggetti di scala diversa");

    return getNumberValue()-obj.getNumberValue();
}
