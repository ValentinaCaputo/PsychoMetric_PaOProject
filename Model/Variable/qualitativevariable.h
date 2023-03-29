#ifndef QUALITATIVEVARIABLE_H
#define QUALITATIVEVARIABLE_H

#include "Model/Variable/variable.h"

class QualitativeVariable: public Variable
{
protected:
    bool checkScaleCoerency() const;
    virtual bool checkConsistency(MisureScale* toCheck) const;
public:
    QualitativeVariable();
    QualitativeVariable(const string& n, scaleType s);
    QualitativeVariable(const QualitativeVariable& other);

    void replaceData(MisureScale* oldValue, MisureScale* newValue) override;

    void replaceAttribute(const string& oldAtt, const string& newAtt) override;

    void replaceNumberValue(double oldNV, double newNV) override;

    void changeData(unsigned int pos, MisureScale* newData) override;

    void changeAttribute(unsigned int pos, const string& newAttribute) override;

    void changeNumberValue(unsigned int pos, double newNumberValue) override;

    void addData(MisureScale* toAdd) override;

    void insertData(unsigned int pos, MisureScale* toInsert) override;
};

#endif // QUALITATIVEVARIABLE_H
