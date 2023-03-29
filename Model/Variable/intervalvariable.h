#ifndef INTERVALVARIABLE_H
#define INTERVALVARIABLE_H

#include "Model/Variable/quantitativevariable.h"
#include "Model/MisureScale/intervalscale.h"

class IntervalVariable: public QuantitativeVariable
{
protected:
    void deepCopy(list<MisureScale*> data) override;

public:
    IntervalVariable();
    IntervalVariable(string n, list<IntervalScale *> rd = list<IntervalScale*>());
    IntervalVariable(const IntervalVariable &other);


    void createData(const vector<string>& attributes, const vector<double> &numberValues = vector<double>()) override;

    void resetData() override;
};

#endif // INTERVALVARIABLE_H
