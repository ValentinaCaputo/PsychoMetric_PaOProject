#ifndef ORDINALVARIABLE_H
#define ORDINALVARIABLE_H

#include "Model/Variable/qualitativevariable.h"
#include "Model/MisureScale/ordinalscale.h"

class OrdinalVariable: public QualitativeVariable
{
protected:
    void deepCopy(list<MisureScale*> data) override;
public:
    OrdinalVariable();
    OrdinalVariable(string n, list<OrdinalScale *> rd = list<OrdinalScale*>());
    OrdinalVariable(const OrdinalVariable &other);


    void createData(const vector<string>& attributes, const vector<double> &numberValues = vector<double>()) override;

    void resetData() override;

  };

#endif // ORDINALVARIABLE_H
