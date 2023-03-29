#include "ordinalvariable.h"

OrdinalVariable::OrdinalVariable()
{

}

OrdinalVariable::OrdinalVariable(std::string n, list<OrdinalScale *> rd): QualitativeVariable(n, ordinal)
{
    for (auto it:rd)
        rawData.push_back(it);

    if(!checkScaleCoerency()){
        rawData.clear();
        throw std::logic_error("Impossibile definire la variabile con i dati inseriti");
    }
}

OrdinalVariable::OrdinalVariable(const OrdinalVariable &other): QualitativeVariable(other)
{
    deepCopy(other.rawData);
}



void OrdinalVariable::createData(const vector<std::string> &attributes, const vector<double> &numberValues)
{
    list<MisureScale*> data = list<MisureScale*>();
    Variable::createData(attributes,numberValues);

    if(numberValues.empty() && !attributes.empty()){
        throw std::logic_error("La scala ordinale deve avere un valore numerico associato");
    } else {
        for(unsigned int i=0; i<attributes.size(); ++i){
            data.push_back(new OrdinalScale(attributes[i], numberValues[i]));
        }
    }
    if(!rawData.empty())
        rawData.clear();
    rawData = data;

    if(!checkScaleCoerency()){
        rawData.clear();
        throw std::logic_error("Impossibile definire la variabile con i dati inseriti");
    }
}

void OrdinalVariable::deepCopy(list<MisureScale *> data)
{
    for (auto it = data.begin(); it != data.end(); ++it){
        if(dynamic_cast<OrdinalScale*>(*it)){
            OrdinalScale* clone = static_cast<OrdinalScale*>(*it);
            rawData.push_back(new OrdinalScale(*clone));
        }
        else
            throw std::logic_error("Errore: I dati che si vogliono copiare appartengono a scale di misura diverse");
    }
}

void OrdinalVariable::resetData()
{
    for (auto it = rawData.begin(); it != rawData.end(); ++it){
        delete *it;
        *it = new OrdinalScale("",-1);
    }
}

