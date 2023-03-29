#include "intervalvariable.h"

IntervalVariable::IntervalVariable()
{

}

IntervalVariable::IntervalVariable(std::string n, list<IntervalScale *> rd): QuantitativeVariable(n, interval)
{
    for (auto it:rd)
        rawData.push_back(it);
}

IntervalVariable::IntervalVariable(const IntervalVariable &other): QuantitativeVariable(other)
{
    deepCopy(other.rawData);
}



void IntervalVariable::createData(const vector<std::string> &attributes, const vector<double> &numberValues)
{
    list<MisureScale*> data = list<MisureScale*>();
    QuantitativeVariable::createData(attributes,numberValues);
    if(numberValues.empty())
        for(auto it:attributes){
            data.push_back(new IntervalScale(std::stod(it)));
        }
    else
        for(auto it:numberValues){
            data.push_back(new IntervalScale(it));
        }

    if(!rawData.empty())
        rawData.clear();
    rawData = data;
}


void IntervalVariable::deepCopy(list<MisureScale *> data)
{
    for (auto it = data.begin(); it != data.end(); ++it){
        if(dynamic_cast<IntervalScale*>(*it)){
            IntervalScale* clone = static_cast<IntervalScale*>(*it);
            rawData.push_back(new IntervalScale(*clone));
        }
        else
            throw std::logic_error("Errore: I dati che si vogliono copiare appartengono a scale di misura diverse");
    }
}

void IntervalVariable::resetData()
{
    for (auto it = rawData.begin(); it != rawData.end(); ++it){
        delete *it;
        *it = new IntervalScale(0);
    }
}

