#ifndef RATIOVARIABLE_H
#define RATIOVARIABLE_H

#include "Model/Variable/quantitativevariable.h"
#include "Model/MisureScale/ratioscale.h"

class RatioVariable: public QuantitativeVariable
{
protected:
    void deepCopy(list<MisureScale*> data) override;

public:
    RatioVariable();
    RatioVariable(string n, list<RatioScale*> rd = list<RatioScale*>());
    RatioVariable(const RatioVariable &other);


    void createData(const vector<string>& attributes, const vector<double> &numberValues = vector<double>()) override;

    void resetData() override;

};

#endif // RATIOVARIABLE_H
