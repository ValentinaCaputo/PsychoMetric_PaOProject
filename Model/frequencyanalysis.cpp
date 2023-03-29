#include "frequencyanalysis.h"

bool FrequencyAnalysis::isInVector(MisureScale *obj, std::vector<MisureScale *> vector)
{
    for(auto it:vector){
        if(*obj == *it)
            return true;
    }
    return false;
}

FrequencyAnalysis::FrequencyAnalysis(Variable *var): variable(var)
{

}

FrequencyAnalysis::~FrequencyAnalysis()
{
   // essendo che non fa una copia profonda della variabile, va bene l'invocazione standard del distruttore
}



std::vector<MisureScale *> FrequencyAnalysis::extractAttributes() const
{

    std::vector<MisureScale*> dataExtracted;


    // devo usare una copia della variabile, altrimenti ordina i dati quando l'utente non lo richiede!
    Variable* variable_copy = nullptr;

    switch (variable->getScale()) {
    case nominal:
        variable_copy = new NominalVariable(*(dynamic_cast<NominalVariable*>(variable)));
        break;
    case ordinal:
        variable_copy = new OrdinalVariable(*(dynamic_cast<OrdinalVariable*>(variable)));
        break;
    case interval:
        variable_copy = new IntervalVariable(*(dynamic_cast<IntervalVariable*>(variable)));
        break;
    case ratio:
        variable_copy = new RatioVariable(*(dynamic_cast<RatioVariable*>(variable)));
        break;
    default:
        break;
    }

    std::list<MisureScale*> allData = variable->getData();

    auto it = allData.begin();

    if(dynamic_cast<OrdinableScale*>(*it)){
        variable_copy->sortData();
        std::list<MisureScale*> sortedData = variable_copy->getData();
        auto it = sortedData.begin();

        //la lista dati non è vuota, è ordinata, per cui inizio ad inserire il primo elemento
        dataExtracted.push_back(*it);

        //continuo con gli elementi successivi sfruttando l'ordine dei dati
        while (it != --sortedData.end()){
            if ((*(*it)!=*(*(++it))))
                dataExtracted.push_back(*it);
        }
    }
    else {
        //dati non ordinabili
        std::list<MisureScale*> allData = variable_copy->getData();
        auto it = allData.begin();

        if(it != allData.end()){
            dataExtracted.push_back(*it);
            it++;
        }

        while (it != allData.end()--){
            if (!isInVector(*it,dataExtracted))
            dataExtracted.push_back(*it);
            it++;
        }
    }

    return dataExtracted;
}

std::vector<unsigned int> FrequencyAnalysis::simpleFrequency() const
{
    std::vector<unsigned int> simpleF;
    std::vector<MisureScale*> dataExtracted = extractAttributes();

    for(auto it:dataExtracted){
        simpleF.push_back((variable->searchData(it)).size());
    }

    return simpleF;
}

std::vector<double> FrequencyAnalysis::relativeFrequency() const
{
    std::vector<double> relativeF;
    std::vector<unsigned int> simpleF = simpleFrequency();
    unsigned int tot = variable->getData().size();

    for (auto it: simpleF){
        relativeF.push_back(static_cast<double>(it)/static_cast<double>(tot));
    }

    return relativeF;
}

std::vector<double> FrequencyAnalysis::percentageFrequency() const
{
    std::vector<double> percF;
    std::vector<double> relativeF = relativeFrequency();

    for (auto it: relativeF){
        percF.push_back(it*100);
    }

    return percF;
}
//pre condition: !rawData.empty()
std::vector<unsigned int> FrequencyAnalysis::cumulativeFrequency() const
{
    //calcolabile solo se scala di misura ordinabile
    list<MisureScale*> allData = variable->getData();
    auto it = allData.begin();
    if(!dynamic_cast<OrdinableScale*>(*it))
        throw std::runtime_error("Impossibile calcolare la frequenza richiesta: la variabile non è ordinabile");

    std::vector<unsigned int> cumulativeF;
    std::vector<unsigned int> simpleF = simpleFrequency();

    cumulativeF.push_back(simpleF[0]);
    for (unsigned int i=1; i<simpleF.size(); i++){
        cumulativeF.push_back(simpleF[i]+cumulativeF[i-1]);
    }

    return cumulativeF;
}

std::vector<double> FrequencyAnalysis::cumulativeRelativeFrequency() const
{
    std::vector<double> CumRelF;
    unsigned int tot = variable->getData().size();

    for (auto it: cumulativeFrequency()){
        CumRelF.push_back(static_cast<double>(it)/static_cast<double>(tot));
    }

    return CumRelF;
}

std::vector<double> FrequencyAnalysis::cumulativePercentageFrequency() const
{
    std::vector<double> CumPercF;

    for (auto it: cumulativeRelativeFrequency()){
        CumPercF.push_back(it*100);
    }

    return CumPercF;
}


