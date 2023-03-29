#include "ratiovariable.h"

RatioVariable::RatioVariable()
{

}

RatioVariable::RatioVariable(std::string n, list<RatioScale*> rd): QuantitativeVariable(n,ratio)
{
    for (auto it:rd)
        rawData.push_back(it);
}

RatioVariable::RatioVariable(const RatioVariable &other): QuantitativeVariable(other)
{
    deepCopy(other.rawData);
}

void RatioVariable::createData(const vector<std::string> &attributes, const vector<double> &numberValues)
{
    list<MisureScale*> data = list<MisureScale*>();
    QuantitativeVariable::createData(attributes,numberValues);
    if(numberValues.empty())
        for(auto it:attributes){
            data.push_back(new RatioScale(std::stod(it)));
        }
    else
        for(auto it:numberValues){
            data.push_back(new RatioScale(it));
        }

    if(!rawData.empty())
        rawData.clear();
    rawData = data;

}

void RatioVariable::deepCopy(list<MisureScale *> data)
{
    for (auto it = data.begin(); it != data.end(); ++it){
        if(dynamic_cast<RatioScale*>(*it)){
            RatioScale* clone = static_cast<RatioScale*>(*it);
            rawData.push_back(new RatioScale(*clone));
        }
        else
            throw std::logic_error("Errore: I dati che si vogliono copiare appartengono a scale di misura diverse");
    }
}

void RatioVariable::resetData()
{
    for (auto it = rawData.begin(); it != rawData.end(); ++it){
        delete *it;
        *it = new RatioScale(0);
    }
}



