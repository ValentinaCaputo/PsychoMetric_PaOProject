#include "misurescale.h"

bool MisureScale::checkDigit(const std::string& digit)
{
    char* end = nullptr;
    double val = strtod(digit.c_str(), &end);
    return end != digit.c_str() && *end == '\0' && val != HUGE_VAL;
}

MisureScale::MisureScale() {}

bool MisureScale::operator==(const MisureScale &ms) const
{

    if (typeid(ms)!= typeid(*this))
        throw std::runtime_error("Impossibile confrontare oggetti di scala diversa");

    return (getAttribute()==ms.getAttribute()) && (getNumberValue()==ms.getNumberValue());

}

bool MisureScale::operator!=(const MisureScale &ms) const
{
    if (typeid(ms)!= typeid(*this))
        throw std::runtime_error("Impossibile confrontare oggetti di scala diversa");

    return (getAttribute()!=ms.getAttribute()) || (getNumberValue()!=ms.getNumberValue());
}
