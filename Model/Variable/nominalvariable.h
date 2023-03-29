#ifndef NOMINALVARIABLE_H
#define NOMINALVARIABLE_H

#include "Model/Variable/qualitativevariable.h"
#include "Model/MisureScale/nominalscale.h"

class NominalVariable: public QualitativeVariable
{
protected:
    bool checkScaleCoerency() const;
    bool checkConsistency(MisureScale* toCheck) const;

    void deepCopy(list<MisureScale*> data) override;

public:
    NominalVariable();
    NominalVariable(string n, list<NominalScale *> rd = list<NominalScale*>());
    NominalVariable(const NominalVariable &other);

    void createData(const vector<string>& attributes, const vector<double> &numberValues = vector<double>()) override;

    void resetData() override;

};

#endif // NOMINALVARIABLE_H
