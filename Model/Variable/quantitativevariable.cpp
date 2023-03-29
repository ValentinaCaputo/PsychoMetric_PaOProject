#include "quantitativevariable.h"

bool QuantitativeVariable::isNumerical(std::string attribute) const
{
    std::string::const_iterator it = attribute.begin();
    while (it != attribute.end() && isdigit(*it))
        ++it;
    return !attribute.empty() && it == attribute.end();
}

QuantitativeVariable::QuantitativeVariable()
{

}

QuantitativeVariable::QuantitativeVariable(const std::string& n, scaleType s): Variable(n,s)
{

}

QuantitativeVariable::QuantitativeVariable(const QuantitativeVariable &other): Variable(other)
{

}

void QuantitativeVariable::replaceAttribute(const std::string &oldAtt, const std::string &newAtt)
{
    for (auto it = rawData.begin(); it != rawData.end(); ++it){
        if (std::stod((*it)->getAttribute()) == std::stod(oldAtt))
            (*it)->changeAttribute(newAtt);
    }
}

void QuantitativeVariable::createData(const vector<std::string> &attributes, const vector<double> &numberValues)
{
    /*
     * Ulteriori verifiche per le variabili quantitative:
     * se sono stati forniti soltanto gli attributi, è necessario controllare che questi siano numeri
     * se entrambi i vettori non sono vuoti i valori devono essere uguali
    */

    Variable::createData(attributes,numberValues);

    if(numberValues.empty() && !attributes.empty()){
        for (unsigned int i=0; i<attributes.size(); ++i)
        {
            if (!isNumerical(attributes[i]))
                throw std::logic_error("Errore nella creazione dei dati: I dati forniti non sono corretti");
        }
    }

    if(numberValues.size() == attributes.size())
    {
        for (unsigned int i=0; i<numberValues.size(); ++i)
        {
            if (attributes[i]== "" || std::stod(attributes[i]) != numberValues[i])
                throw std::logic_error("Errore nella creazione dei dati: I dati forniti non sono corretti");
        }
    }


}

OrdinalVariable* QuantitativeVariable::turnInToOrdinal(std::vector<std::string> attributes, std::vector<int> max) const
{
    std::list<OrdinalScale*> newRawData;
    for (auto it:rawData){
        unsigned int i=0;
        while (it->getNumberValue() > max[i]){
             i++;
             if (i >= max.size())
                throw std::runtime_error("non è stato definito un valore massimo adeguato alla variabile");
        }
        newRawData.push_back(new OrdinalScale(attributes[i],i));
    }
    return new OrdinalVariable(name, newRawData);
}

