#include "nominalscale.h"

NominalScale::NominalScale()
{
    attribute = "";
    numberLabel = -99;
}

NominalScale::NominalScale(const std::string &att, int lab): attribute(checkDigit(att)? "":att), numberLabel(lab) {
    // devo garantire il fatto che att non sia un numero
    if(checkDigit(att))
        throw std::invalid_argument("Attenzione: L'attributo non può avere valore numerico");
;}

std::string NominalScale::getAttribute() const { return attribute;}

void NominalScale::changeAttribute(const string &att)
{
    //controllo prima se att non è un numero
    if(checkDigit(att))
        throw std::invalid_argument("Attenzione: L'attributo non può avere valore numerico");

    //nessun problema di coerenza
    attribute = att;


}

double NominalScale::getNumberValue() const { return numberLabel; }

void NominalScale::changeNumberValue(double nv)
{
    numberLabel = nv;
}

bool NominalScale::operator==(const NominalScale &ns) const
{
    if(attribute != ns.attribute)
        return false;
    else
    {
        //devo controllare che, se assegnate, le etichette siano coerenti
        if(numberLabel != ns.numberLabel)
            throw std::logic_error("Attenzione incoerenza tra i dati: rivedere le etichette assegnate!");
    }
    return true;
}

bool NominalScale::operator!=(const NominalScale &ns) const
{
    //devo controllare che, se assegnate, le etichette siano coerenti
    if(attribute == ns.attribute){
        if(numberLabel == ns.numberLabel)
            return false;
        else
            throw std::logic_error ("Attenzione incoerenza tra i dati: rivedere le etichette assegnate!");
    }
    else
        if (numberLabel != -99 && numberLabel == ns.numberLabel)
            throw std::logic_error ("Attenzione incoerenza tra i dati: rivedere le etichette assegnate!");

    return true;

}
