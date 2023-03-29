#include "qualitativevariable.h"

bool QualitativeVariable::checkScaleCoerency() const
{
    //oltre a verificare la coerenza nella scala di misura indicata, occorre verificare la corrispondenza tra attributi e valori numerici

    bool check_scale = Variable::checkScaleCoerency();
    bool check_specific = true;

    auto it = rawData.begin();

    while (check_specific && it != rawData.end()){
        check_specific = checkConsistency(*it);
        it++;
    }

    return check_scale && check_specific;
}

bool QualitativeVariable::checkConsistency(MisureScale *toCheck) const
{
    std::string att_toCheck = toCheck->getAttribute();
    int numLab_toCheck = toCheck->getNumberValue();

    for(auto it:rawData){
        if ((it->getAttribute() == att_toCheck && it->getNumberValue()!= numLab_toCheck) || (it->getAttribute() != att_toCheck && it->getNumberValue()== numLab_toCheck))
                return false;
    }

    return true;
}

QualitativeVariable::QualitativeVariable() {}

QualitativeVariable::QualitativeVariable(const std::string &n, scaleType s): Variable(n,s) {

}

QualitativeVariable::QualitativeVariable(const QualitativeVariable &other): Variable(other) {}



void QualitativeVariable::replaceData(MisureScale *oldValue, MisureScale *newValue)
{
    if(!checkCoerency(newValue))
        throw std::logic_error("Impossibile definire la variabile con i dati inseriti");

    Variable::replaceData(oldValue,newValue);
}

void QualitativeVariable::replaceAttribute(const std::string &oldAtt, const std::string &newAtt)
{
    //devo fare in modo che se la sostituzione genera errore, i dati precedenti non vengono persi
    std::vector<unsigned int> finded = searchAttribute(oldAtt);
    Variable::replaceAttribute(oldAtt,newAtt);
    if(!checkScaleCoerency()){
        for(auto pos:finded){
            list<MisureScale*>::iterator it = findIterator(pos);
            (*it)->changeAttribute(oldAtt);
        }
        throw std::logic_error("Impossibile procedere: Introdotta incoerenza nei dati");
    }
}

void QualitativeVariable::replaceNumberValue(double oldNV, double newNV)
{
    //devo fare in modo che se la sostituzione genera errore, i dati precedenti non vengono persi
    std::vector<unsigned int> finded = searchNumberValue(oldNV);
    Variable::replaceNumberValue(oldNV,newNV);
    if(!checkScaleCoerency()){
        for(auto pos:finded){
            list<MisureScale*>::iterator it = findIterator(pos);
            (*it)->changeNumberValue(oldNV);
        }
        throw std::logic_error("Impossibile procedere: Introdotta incoerenza nei dati");
    }
}

void QualitativeVariable::changeData(unsigned int pos, MisureScale *newData)
{
    if(!checkConsistency(newData))
        throw std::logic_error("Impossibile modificare il dato richiesto per incompatibilità");

    Variable::changeData(pos,newData);

}

void QualitativeVariable::changeAttribute(unsigned int pos, const std::string& newAttribute)
{
    // salvo l'attributo di partenza in modo che se non va bene ripristino il valore
    string aux = (*findIterator(pos))->getAttribute();

    Variable::changeAttribute(pos,newAttribute);

    double checkNV = (*findIterator(pos))->getNumberValue();

    if(checkNV==-99){
        //situazione di default/reset, ancora non era stato definito/ridefinito il dato
        //ATTENZIONE non vale per ordinale perchè una volta definito l'attributo questo DEVE avere una propria etichetta associata

        // controllo se ci sono altri dati con lo stesso attributo ed etichetta diversa
        bool stop=false;

        for(auto it=rawData.begin(); it!=rawData.end() && !stop; it++){
            if((*it)->getAttribute() == newAttribute && (*it)->getNumberValue() != -99)
            {
                //se ci sono, assegno a questo dato lo stesso valore di etichetta del dato trovato
                (*findIterator(pos))->changeNumberValue((*it)->getNumberValue());
                stop=true;
            }
            //altrimenti accetto la modifica perché mantiene coerenza nei dati
        }
    }
    else
        if(!checkScaleCoerency()){
            Variable::changeAttribute(pos,aux);
            throw std::logic_error("Impossibile modificare il dato: Introdotta incoerenza nei dati");
        }
}

void QualitativeVariable::changeNumberValue(unsigned int pos, double newNumberValue)
{
    // salvo il valore numerico di partenza in modo che se non va bene ripristino il valore
    double aux = (*findIterator(pos))->getNumberValue();

    Variable::changeNumberValue(pos,newNumberValue);

    if(aux == -99 || aux==-1){
        //situazione di default/reset, ancora non era stato definito/ridefinito il dato

        // controllo se ci sono altri dati con lo stesso attributo ed etichetta diversa
        string attribute = (*findIterator(pos))->getAttribute();

        for(auto it=rawData.begin(); it!=rawData.end(); it++){
            if((*it)->getAttribute() == attribute && (*it)->getNumberValue() != newNumberValue)
            {
                //se ci sono, devo controllare se è valore di default o no!
                //In particolare questo può valere soltanto per scala nominale, in quanto la scala ordinale se definito attributo deve per forza aver definito l'etichetta
                if((*it)->getNumberValue() == -99)
                    //devo aggiornare l'etichetta
                    (*it)->changeNumberValue(newNumberValue);
                else {
                    //se non è valore di default significa che sto introducendo incoerenza nei dati e quindi devo ripristinare il valore modificato dalla funzione e generare un errore
                    Variable::changeNumberValue(pos,aux);
                    throw std::logic_error("Impossibile modificare il dato: Introdotta incoerenza nei dati");
                }
            }
            //altrimenti devo anche controllare se il nuovo valore numerico entra in conflitto con altri

            if ((*it)->getAttribute() != attribute && (*it)->getNumberValue()==newNumberValue)
            {
                Variable::changeNumberValue(pos,aux);
                throw std::logic_error("Impossibile modificare il dato: Introdotta incoerenza nei dati");
            }

        }
    }
    else
        if(!checkScaleCoerency()){
            Variable::changeNumberValue(pos,aux);
            throw std::logic_error("Impossibile modificare il dato: Introdotta incoerenza nei dati");
        }
}

void QualitativeVariable::addData(MisureScale *toAdd)
{
    if(!checkConsistency(toAdd))
        throw std::runtime_error("Impossibile aggiungere il dato: incoerenza con i dati della variabile");
    Variable::addData(toAdd);
}

void QualitativeVariable::insertData(unsigned int pos, MisureScale *toInsert)
{
    if(!checkConsistency(toInsert))
        throw std::runtime_error("Impossibile inserire il dato: incoerenza con i dati della variabile");

    Variable::insertData(pos, toInsert);
}
