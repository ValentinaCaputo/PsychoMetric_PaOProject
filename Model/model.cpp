#include "model.h"

Model::Model()
{

}

Model::~Model()
{
}


Variable *Model::getVariable() const
{
    return variable;
}

void Model::createVariable(std::string name, scaleType scale, int size)
{
    switch (scale) {
    case nominal:{
        std::list<NominalScale*> emptyData;
        for(int i=0; i<size; i++)
            emptyData.push_back(new NominalScale());
        variable = new NominalVariable(name,emptyData);
        break;
    }
    case ordinal:
    {
        std::list<OrdinalScale*> emptyData;
        for(int i=0; i<size; i++)
            emptyData.push_back(new OrdinalScale());
        variable = new OrdinalVariable(name,emptyData);
        break;
    }
    case interval:
    {
        std::list<IntervalScale*> emptyData;
        for(int i=0; i<size; i++)
            emptyData.push_back(new IntervalScale());
        variable = new IntervalVariable(name,emptyData);
        break;
    }
    case ratio:
    {
        std::list<RatioScale*> emptyData;
        for(int i=0; i<size; i++)
            emptyData.push_back(new RatioScale());
        variable = new RatioVariable(name,emptyData);
        break;
    }
    }


    empty = false;
}

bool Model::isEmpty() const
{
    return empty;
}

void Model::openVariable(std::string path)
{
    FileManagment file(path);

    variable = file.loadVariable();

    empty = false;
}

void Model::saveVariable(std::string path)
{
    FileManagment file(path);

    file.saveVariable(variable);
}

void Model::resetVariable()
{
    variable->resetData();
}



void Model::convertToOrdinal(std::vector<std::string> attributes, std::vector<int> max)
{
    if(dynamic_cast<QuantitativeVariable*>(variable)){
        QuantitativeVariable* toConvert = static_cast<QuantitativeVariable*>(variable);
        variable = toConvert->turnInToOrdinal(attributes,max);
    }
}

void Model::addData(std::string att, double numVal)
{

    scaleType scale = variable->getScale();

    switch(scale){
    case nominal:
    {
        MisureScale* toAdd = new NominalScale(att,numVal);
        variable->addData(toAdd);
        break;
    }
    case ordinal:
    {
        MisureScale* toAdd = new OrdinalScale(att,numVal==-99? -1:numVal);
        variable->addData(toAdd);
        break;
    }
    case interval:
    {
        MisureScale* toAdd = new IntervalScale(numVal==-99? 0:numVal);
        variable->addData(toAdd);
        break;
    }
    case ratio:
    {
        MisureScale* toAdd = new RatioScale(numVal==-99?0:numVal);
        variable->addData(toAdd);
        break;
    }
    }


}

void Model::insertData(unsigned int pos, std::string att, double numVal)
{

    //devo costruire il dato con i valori forniti e inserirlo nella variabile

    scaleType scale = variable->getScale();

    switch(scale){
    case nominal:
    {
        MisureScale* toInsert = new NominalScale(att,numVal);
        variable->insertData(pos,toInsert);
        break;
    }
    case ordinal:
    {
        MisureScale* toInsert = new OrdinalScale(att,numVal==-99? -1:numVal);
        variable->insertData(pos,toInsert);
        break;
    }
    case interval:
    {
        MisureScale* toInsert = new IntervalScale(numVal==-99? 0:numVal);
        variable->insertData(pos,toInsert);
        break;
    }
    case ratio:
    {
        MisureScale* toInsert = new RatioScale(numVal==-99?0:numVal);
        variable->insertData(pos,toInsert);
        break;
    }
    }




}

void Model::changeData(unsigned int pos, std::string att, double numVal)
{
    if(att=="")
        variable->changeNumberValue(pos, numVal);
    else
        variable->changeAttribute(pos,att);

}

void Model::changeQualitativeData(int pos, MisureScale *newValue)
{
    static_cast<QualitativeVariable*>(variable)->changeData(pos,newValue);
}

void Model::replaceData(std::string oldValue, std::string newValue)
{
    variable->replaceAttribute(oldValue,newValue);

    std::string::const_iterator it = oldValue.begin();
    while (it != oldValue.end() && std::isdigit(*it)) ++it;
    if(!oldValue.empty() && it == oldValue.end())
        variable->replaceNumberValue(std::stod(oldValue),std::stod(newValue));
}

std::vector<unsigned int> Model::findData(std::string att, double numVal)
{
    if(att != "")
        return variable->searchAttribute(att);
    return variable->searchNumberValue(numVal);
}

void Model::eraseData(unsigned int pos)
{
    variable->eraseByPosition(pos);
}

std::vector<std::string> Model::getSortedData() const
{
    FrequencyAnalysis f = FrequencyAnalysis(variable);
    std::vector<MisureScale*> sortedData = f.extractAttributes();
    std::vector<std::string> toReturn;

    for(auto it = sortedData.begin(); it != sortedData.end(); it++)
        toReturn.push_back((*it)->getAttribute());

    return toReturn;
}

bool Model::checkSortedData(std::vector<std::string> dataToCheck) const
{
    std::vector<std::string> sortedData = getSortedData();

    if(sortedData.size() != dataToCheck.size())
        return false;

    for(unsigned int i=0; i<dataToCheck.size(); i++){
        if (dataToCheck[i] != sortedData[i])
            return false;
    }

    return true;
}

bool Model::checkFrequencyAnalysis(FrequencyType freqType,std::vector<double> freqToCheck) const
{
    std::vector<double> freq = frequency_toShow(freqType);

    if(freq.size() != freqToCheck.size())
        return false;

    for(unsigned int i=0; i<freqToCheck.size(); i++){
        double EPSILON = 0.0005;
        /*
         * devo confrontare valori che possono avere valori oltre la virgola approssimati in maniera diversa,
        * piuttosto che confrontare la frequenza calcolata dall'utente con quella calcolata tramite algoritmo con operatore ==
        * si cerca di verificare quanto |freq_calc - freq_alg| < EPSILON, dove EPSILON è un valore molto piccolo
        * se la differenza è piccola significa che la frequenza calcolata è corretta, altrimenti è considerata sbagliata
        */
        if (std::fabs(freqToCheck[i] - freq[i]) > EPSILON)
            return false;
    }

    return true;
}

std::vector<double> Model::frequency_toCalculate(FrequencyType freqType) const
{
    switch (freqType) {
    case simple:{
        std::vector<unsigned int> simpleF = FrequencyAnalysis(variable).simpleFrequency();
        std::vector<double> toReturn;
        for(auto it:simpleF)
        {
            toReturn.push_back(static_cast<double>(it));
        }
        return toReturn;
    }
    case relative:{
        return FrequencyAnalysis(variable).relativeFrequency();
    }

    case percentage:{
        return FrequencyAnalysis(variable).percentageFrequency();
    }
    case cumulative:{
        std::vector<double> toReturn;
        std::vector<unsigned int> cumulativeF_toAdapt = FrequencyAnalysis(variable).cumulativeFrequency();

        for(auto it:cumulativeF_toAdapt)
        {
            toReturn.push_back(static_cast<double>(it));
        }
        return toReturn;
    }
    case cumulativeRelative:{
        return FrequencyAnalysis(variable).cumulativeRelativeFrequency();
    }
    case cumulativePercentage:{
        return FrequencyAnalysis(variable).cumulativePercentageFrequency();
    }
    }

    //se sono qua è perchè freqType non è valido
    throw std::runtime_error("Impossibile calcolare la frequenza richiesta: tipo di frequenza non esiste");
}

std::vector<double> Model::frequency_toShow(FrequencyType freqType) const
{
        switch (freqType) {
        case simple:{
            std::vector<unsigned int> simpleF = FrequencyAnalysis(variable).simpleFrequency();
            std::vector<double> toReturn;
            for(auto it:simpleF)
            {
                toReturn.push_back(static_cast<double>(it));
            }
            return toReturn;
        }
        case relative:{
            std::vector<double> toReturn;
            std::vector<unsigned int> simpleF = FrequencyAnalysis(variable).simpleFrequency();
            for(auto it:simpleF)
            {
                toReturn.push_back(static_cast<double>(it));
            }
            std::vector<double> relativeF = FrequencyAnalysis(variable).relativeFrequency();
            toReturn.insert(toReturn.end(),relativeF.begin(),relativeF.end());
            return toReturn;
        }
        case percentage:{
            std::vector<double> toReturn;
            std::vector<unsigned int> simpleF = FrequencyAnalysis(variable).simpleFrequency();
            for(auto it:simpleF)
            {
                toReturn.push_back(static_cast<double>(it));
            }
            std::vector<double> relativeF = FrequencyAnalysis(variable).relativeFrequency();
            toReturn.insert(toReturn.end(),relativeF.begin(),relativeF.end());
            std::vector<double> percentageF = FrequencyAnalysis(variable).percentageFrequency();

            toReturn.insert(toReturn.end(),percentageF.begin(),percentageF.end());
            return toReturn;
        }
        case cumulative:{
            std::vector<double> toReturn;
            std::vector<unsigned int> simpleF_toAdapt = FrequencyAnalysis(variable).simpleFrequency();
            std::vector<unsigned int> cumulativeF_toAdapt = FrequencyAnalysis(variable).cumulativeFrequency();

            simpleF_toAdapt.insert(simpleF_toAdapt.end(),cumulativeF_toAdapt.begin(),cumulativeF_toAdapt.end());

            for(auto it:simpleF_toAdapt)
            {
                toReturn.push_back(static_cast<double>(it));
            }
            return toReturn;
        }
        case cumulativeRelative:{
            std::vector<double> toReturn;
            std::vector<unsigned int> simpleF_toAdapt = FrequencyAnalysis(variable).simpleFrequency();
            std::vector<unsigned int> cumulativeF_toAdapt = FrequencyAnalysis(variable).cumulativeFrequency();

            simpleF_toAdapt.insert(simpleF_toAdapt.end(),cumulativeF_toAdapt.begin(),cumulativeF_toAdapt.end());

            for(auto it:simpleF_toAdapt)
            {
                toReturn.push_back(static_cast<double>(it));
            }

            std::vector<double> cumulativeRF = FrequencyAnalysis(variable).cumulativeRelativeFrequency();

            toReturn.insert(toReturn.end(),cumulativeRF.begin(),cumulativeRF.end());
            return toReturn;
        }
        case cumulativePercentage:{
            std::vector<double> toReturn;
            std::vector<unsigned int> simpleF_toAdapt = FrequencyAnalysis(variable).simpleFrequency();
            std::vector<unsigned int> cumulativeF_toAdapt = FrequencyAnalysis(variable).cumulativeFrequency();

            simpleF_toAdapt.insert(simpleF_toAdapt.end(),cumulativeF_toAdapt.begin(),cumulativeF_toAdapt.end());

            for(auto it:simpleF_toAdapt)
            {
                toReturn.push_back(static_cast<double>(it));
            }

            std::vector<double> cumulativeRF = FrequencyAnalysis(variable).cumulativeRelativeFrequency();

            toReturn.insert(toReturn.end(),cumulativeRF.begin(),cumulativeRF.end());

            std::vector<double> cumPercFreq = FrequencyAnalysis(variable).cumulativePercentageFrequency();
            toReturn.insert(toReturn.end(),cumPercFreq.begin(),cumPercFreq.end());
            return toReturn;
        }
        }

        //se sono qua è perchè freqType non è valido
        throw std::runtime_error("Impossibile calcolare la frequenza richiesta: tipo di frequenza non esiste");


}



