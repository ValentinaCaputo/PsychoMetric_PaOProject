#include "nominalvariable.h"

bool NominalVariable::checkScaleCoerency() const
{

    unsigned int dimension = searchNumberValue(-99).size(); //numero di dati della variabile con valore numerico non definito

    if(dimension == rawData.size())
        return Variable::checkScaleCoerency();
    else{

        return QualitativeVariable::checkScaleCoerency();
    }

}

bool NominalVariable::checkConsistency(MisureScale *toCheck) const
{
    if (toCheck->getNumberValue()== -99){
        return true;
    }
    else
       return QualitativeVariable::checkConsistency(toCheck);
}

NominalVariable::NominalVariable()
{

}

NominalVariable::NominalVariable(std::string n, list<NominalScale *> rd): QualitativeVariable(n, nominal)
{
    for (auto it:rd)
        rawData.push_back(it);

    if(!checkScaleCoerency()){
        rawData.clear();
        throw std::logic_error("Impossibile definire la variabile con i dati inseriti");
    }
}

NominalVariable::NominalVariable(const NominalVariable &other): QualitativeVariable(other)
{
    deepCopy(other.rawData);
}


void NominalVariable::createData(const vector<std::string> &attributes, const vector<double> &numberValues)
{
    list<MisureScale*> data = list<MisureScale*>();
    Variable::createData(attributes,numberValues);

    if(numberValues.empty()){
        for(auto it:attributes){
            data.push_back(new NominalScale(it));
        }
    } else {
        for(unsigned int i=0; i<attributes.size(); ++i){
            data.push_back(new NominalScale(attributes[i], numberValues[i]));
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

void NominalVariable::deepCopy(list<MisureScale *> data)
{
    for (auto it = data.begin(); it != data.end(); ++it){
        if(dynamic_cast<NominalScale*>(*it)){

            NominalScale* clone = static_cast<NominalScale*>(*it);
            rawData.push_back(new NominalScale(*clone));

            if(!checkScaleCoerency()){
                clearData();
                throw std::logic_error("Errore: impossibile procedere per incoerenza nei dati");
            }
        }
        else
            throw std::logic_error("Errore: I dati che si vogliono copiare appartengono a scale di misura diverse");
    }
}

void NominalVariable::resetData()
{
    for (auto it = rawData.begin(); it != rawData.end(); ++it){
        delete *it;
        *it = new NominalScale("");
    }
}

