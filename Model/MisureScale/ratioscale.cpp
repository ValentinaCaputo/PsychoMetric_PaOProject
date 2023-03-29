#include "ratioscale.h"



RatioScale::RatioScale()
{
    numberValue = 0;
}

RatioScale::RatioScale(double nv): numberValue(nv>=0 ? nv:0)
{
    if (nv<0)
        throw std::invalid_argument("Attenzione: La scala a rapporti non ammette valori negativi!");
}

std::string RatioScale::getAttribute() const
{
    return std::to_string(numberValue);
}

void RatioScale::changeAttribute(const std::string &att)
{
    if (checkDigit(att))
        changeNumberValue(std::stod(att));
    else
        throw std::invalid_argument("Impossibile procedere: verificare di aver inserito un valore numerico");
}

double RatioScale::getNumberValue() const
{
    return numberValue;
}

void RatioScale::changeNumberValue(double nv)
{
    numberValue = nv <0 ? throw std::invalid_argument("Attenzione: La scala a rapporti non ammette valori negativi!") : nv;
}

RatioScale RatioScale::operator *(const RatioScale &obj) const
{
    return numberValue * obj.numberValue;
}

RatioScale RatioScale::operator /(const RatioScale &obj) const
{
    return numberValue / obj.numberValue;
}
