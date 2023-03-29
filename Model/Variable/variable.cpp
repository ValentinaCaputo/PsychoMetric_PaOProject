#include "variable.h"

bool Variable::checkScaleCoerency() const
{
    if (rawData.empty()) return true;

    for (auto it:rawData){
        if(!checkCoerency(it))
            return false;
    }
    return true;
}

bool Variable::checkCoerency(MisureScale *toCheck) const
{
    switch (scale) {
    case nominal:
    {
        if(!dynamic_cast<NominalScale*>(toCheck))
            return false;
        break;
    }
    case ordinal:
    {
        if(!dynamic_cast<OrdinalScale*>(toCheck))
            return false;
        break;
    }
    case interval:
    {
        if(!dynamic_cast<IntervalScale*>(toCheck))
            return false;
        break;
    }
    case ratio:
    {
        if(!dynamic_cast<RatioScale*>(toCheck))
            return false;
        break;
    }
    }
    return true;
}

list<MisureScale*>::iterator Variable::findIterator(unsigned int pos)
{
    if(pos<rawData.size()){
        auto it = rawData.begin();
        while(pos>0){
            pos--;
            it++;
        }
        return it;
    }
    else
        throw std::logic_error("La posizione indicata non è corretta");
}

Variable::Variable() {}

Variable::Variable(const std::string &n, scaleType s):
    name(n),
    scale(s)
{
    if(!checkScaleCoerency())
        throw std::invalid_argument("Attenzione i dati che si vogliono inserire non appartengono alla scala di misura della variabile");
}

Variable::~Variable()
{
    clearData();
}

Variable::Variable(const Variable &other): name(other.name), scale(other.scale),rawData(list<MisureScale*>())
{

}

Variable &Variable::operator=(const Variable &other)
{
    if(this != &other){
        name = other.name;
        scale = other.scale;
        if(!other.rawData.empty())
            clearData();
        deepCopy(other.rawData);
    }
    return *this;
}

std::string Variable::getName() const
{
    return name;
}

scaleType Variable::getScale() const
{
    return scale;
}

list<MisureScale *> Variable::getData() const
{
    return rawData;
}

void Variable::renameVariable(const std::string& newName)
{
    name = newName;
}

void Variable::createData(const vector<std::string> &attributes, const vector<double> &numberValues)
{
    /*
     * verifica condizioni di base PER TUTTE le scale di misura:
     * i vettori con i dati non devono essere vuoti e devono avere le stesse dimensioni
    */

    if((!attributes.empty() && !numberValues.empty()) && attributes.size() != numberValues.size())
        throw std::logic_error("Errore nella creazione dei dati: I dati forniti non sono corretti");
}

void Variable::replaceData(MisureScale *oldValue, MisureScale *newValue)
{
    if (typeid(*oldValue) == typeid(*newValue)){
        for (auto it = rawData.begin(); it != rawData.end(); ++it){
            if (*it == oldValue)
                *it = newValue;
        }
    }
    else
        throw std::logic_error("Impossibile sostituire il valore: scale di misura diverse");
}

void Variable::replaceAttribute(const string& oldAtt, const string& newAtt)
{
    std::vector<unsigned int> finded = searchAttribute(oldAtt);
    if(finded.empty())
        throw std::runtime_error("Il valore "+oldAtt+" che si vuole sostituire non è presente nella variabile");
    for(auto pos:finded){
        list<MisureScale*>::iterator iter = findIterator(pos);
        (*iter)->changeAttribute(newAtt);
    }

}

void Variable::replaceNumberValue(double oldNV, double newNV)
{
    std::vector<unsigned int> finded = searchNumberValue(oldNV);
    if(finded.empty())
        throw std::runtime_error("Il valore "+std::to_string(oldNV)+" che si vuole sostituire non è presente nella variabile");
    for(auto pos:finded){
        list<MisureScale*>::iterator iter = findIterator(pos);
        (*iter)->changeNumberValue(newNV);
    }
}


void Variable::changeData(unsigned int pos, MisureScale *newData)
{     
    list<MisureScale*>::iterator it = findIterator(pos);

    if (typeid(*(*it)) == typeid(*newData)){
         (*it) = newData;
    }
    else
        throw std::invalid_argument("Impossibile cambiare il valore: scale di misura diverse");

}

void Variable::changeAttribute(unsigned int pos, const std::string &newAttribute)
{
    list<MisureScale*>::iterator it = findIterator(pos);
    (*it)->changeAttribute(newAttribute);

}

void Variable::changeNumberValue(unsigned int pos, double newNumberValue)
{
    list<MisureScale*>::iterator it = findIterator(pos);
    (*it)->changeNumberValue(newNumberValue);
}

vector<unsigned int> Variable::searchData(MisureScale *toFind) const
{
    vector<unsigned int> dataFinded;
    unsigned int pos=0;
    for(auto it:rawData){
        if (*it==*toFind)
            dataFinded.push_back(pos);
        pos++;
    }
    return dataFinded;
}

vector<unsigned int> Variable::searchAttribute(const std::string &toFind) const
{
    vector<unsigned int> dataFinded;
    unsigned int pos=0;
    for(auto it:rawData){
        if (it->getAttribute()==toFind)
            dataFinded.push_back(pos);
        pos++;
    }
    return dataFinded;
}

vector<unsigned int> Variable::searchNumberValue(double toFind) const
{
    vector<unsigned int> dataFinded;
    unsigned int pos=0;
    for(auto it:rawData){
        if (it->getNumberValue()==toFind)
            dataFinded.push_back(pos);
        pos++;
    }
    return dataFinded;
}


void Variable::addData(MisureScale *toAdd)
{
    if(checkCoerency(toAdd)){
        rawData.push_back(toAdd);
    }
    else
        throw std::invalid_argument("Il dato che che si vuole aggiungere non appartiene alla scala di misura della variabile");
}

void Variable::insertData(unsigned int pos, MisureScale *toInsert)
{
    if(checkCoerency(toInsert)){
        auto it = findIterator(pos);
        rawData.insert(it,toInsert);
    }
    else
        throw std::invalid_argument("Il dato che che si vuole inserire non appartiene alla scala di misura della variabile");

}

void Variable::clearData()
{
    if (!rawData.empty()){
        for (auto it = rawData.begin(); it!=rawData.end(); it++){
            delete *it;
        }
        rawData.clear();
    }
}

void Variable::eraseByData(MisureScale *toErase)
{
    bool check=false;

    for (auto it = rawData.begin(); !check && it != rawData.end(); ++it){
        if (*it == toErase){
            delete *it; //elimino oggetto puntato
            rawData.erase(it); //elimino il puntatore
            check = true;
        }
    }

    if(!check)
        throw std::runtime_error("Il dato che si vuole eliminare non è presente");
}

void Variable::eraseByAttribute(const std::string &toErase)
{
    bool check=false;

    for (auto it = rawData.begin(); !check && it != rawData.end(); ++it){
        if ((*it)->getAttribute() == toErase){
            delete *it; //elimino oggetto puntato
            rawData.erase(it); //elimino il puntatore
            check = true;
        }
    }

    if(!check)
        throw std::runtime_error("Il dato che si vuole eliminare non è presente");
}

void Variable::eraseByNumberValue(double toErase)
{
    bool check=false;

    for (auto it = rawData.begin(); !check && it != rawData.end(); ++it){
        if ((*it)->getNumberValue() == toErase){
            delete *it; //elimino l'oggetto puntato
            rawData.erase(it); //elimino il puntatore
            check = true;
        }
    }

    if(!check)
        throw std::runtime_error("Il dato che si vuole eliminare non è presente");
}

void Variable::eraseByPosition(unsigned int pos)
{
    auto it = findIterator(pos);
    if(pos<rawData.size()){
        delete *it; //elimino oggetto puntato
        rawData.erase(it); //elimino il puntatore dalla lista
    }
}

void Variable::sortData()
{
    auto it = rawData.begin();
    if(!dynamic_cast<OrdinableScale*>(*it))
        throw  std::runtime_error("La variabile che si vuole ordinare non è ordinabile");
    if(rawData.empty())
        throw  std::runtime_error("Non sono presenti dati da ordinare");

    list<OrdinableScale*> toSort;
    while(it != rawData.end()){
        OrdinableScale * toReplace = static_cast<OrdinableScale*>(*it);
        toSort.push_back(toReplace);
        it++;
    }

    toSort.sort([](OrdinableScale* prev, OrdinableScale* next){return (*prev)<(*next);});

    auto ts = toSort.begin();
    for(unsigned int i=0; i<toSort.size(); i++){
        changeData(i,*ts);
        ts++;
    }


}


