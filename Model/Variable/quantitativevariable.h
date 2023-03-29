#ifndef QUANTITATIVEVARIABLE_H
#define QUANTITATIVEVARIABLE_H

#include "Model/Variable/variable.h"
#include "Model/Variable/ordinalvariable.h"

class QuantitativeVariable: public Variable
{
protected:
    virtual bool isNumerical(string attribute) const;
public:
    QuantitativeVariable();
    QuantitativeVariable(const string& n, scaleType s);
    QuantitativeVariable(const QuantitativeVariable& other);

    void replaceAttribute(const string& oldAtt, const string& newAtt) override;
    virtual void createData(const vector<string>& attributes, const vector<double> &numberValues = vector<double>()) override;

    /**
     * @brief turnInToOrdinal       converte la variabile quantitativa in variabile qualitativa ordinale,
     * @param attributes            vettore contenente l'insieme degli attributi che dovranno sostituire i valori numerici,
     * @param max                   vettore contenente i limiti superiori utilizzati per assegnare l'attributo al posto del valore numerico.
     *                              NOTA: per convertire la variabile serve prima definire le fasce di valori corrispondenti ai possibili attributi,
     *                                    e poi assegnare ad ogni valore il corrispettivo attributo.
     *                              Ad esempio stabilisco che tutti i valori compresi tra 0 e 10 saranno ridefiniti con l'attributo basso e ogni volta
     *                              che trovo valori compresi in questa fascia converto il valore numerico con l'attributo basso.
     * @return                      restituisce la nuova variabile ordinale.
     *                              Essendo che la variabile originaria non viene modificata, il metodo è definito costante.
     */
    virtual OrdinalVariable* turnInToOrdinal(std::vector<std::string> attributes, std::vector<int> max) const;
};

#endif // QUANTITATIVEVARIABLE_H
