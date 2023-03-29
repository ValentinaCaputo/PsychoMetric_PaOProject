#include "ordinalscale.h"

OrdinalScale::OrdinalScale()
{
    attribute = "";
    numberLevel = -1;
}

OrdinalScale::OrdinalScale(const std::string &att, double lev): attribute(checkDigit(att)? "":att), numberLevel(lev) {
    //devo assicurarmi che non venga inserito un valore numerico al posto dell'attributo
    if(checkDigit(att))
        throw std::invalid_argument("Attenzione: L'attributo non può avere valore numerico");
}

std::string OrdinalScale::getAttribute() const
{
    return attribute;
}

void OrdinalScale::changeAttribute(const std::string &att)
{
    //controllo prima se att non è un numero
    if(checkDigit(att))
        throw std::invalid_argument("Attenzione: L'attributo non può avere valore numerico");

    //se att non è un numero posso procedere con la riassegnazione
    attribute = att;
}

double OrdinalScale::getNumberValue() const
{
 return numberLevel;
}

void OrdinalScale::changeNumberValue(double nv)
{
    numberLevel = nv;
}

bool OrdinalScale::operator==(const OrdinalScale &os) const
{
    if(attribute != os.attribute)
        return false;
    else
    {
        if(numberLevel != os.numberLevel)
            throw std::logic_error("Attenzione incoerenza tra i dati: rivedere le etichette assegnate!");
    }
    return true;
}

bool OrdinalScale::operator!=(const OrdinalScale &os) const
{
    if(attribute == os.attribute){
        if(numberLevel == os.numberLevel)
            return false;
        else
            throw std::logic_error ("Attenzione incoerenza tra i dati: rivedere le etichette assegnate!");
    }
    else
        if (numberLevel == os.numberLevel)
            throw std::logic_error ("Attenzione incoerenza tra i dati: rivedere le etichette assegnate!");

    return true;
}
