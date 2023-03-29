#include "intervalscale.h"

IntervalScale::IntervalScale()
{
    numberValue = 0;
}

IntervalScale::IntervalScale(double nv): numberValue(nv) {}

std::string IntervalScale::getAttribute() const
{
    return std::to_string(numberValue);
}

void IntervalScale::changeAttribute(const std::string &att)
{
    //deve controllare prima che i caratteri digitati corrispondano a numeri
    if (checkDigit(att))
        changeNumberValue(std::stod(att));
    else
        throw std::invalid_argument("Impossibile procedere: verificare di aver inserito un valore numerico");
}

double IntervalScale::getNumberValue() const
{
    return numberValue;
}

void IntervalScale::changeNumberValue(double nv)
{
    numberValue = nv;
}

