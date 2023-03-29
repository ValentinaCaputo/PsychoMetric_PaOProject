#ifndef FREQUENCYANALYSIS_H
#define FREQUENCYANALYSIS_H

#include "Model/Variable/variable.h"
#include "Model/Variable/nominalvariable.h"
#include "Model/Variable/ordinalvariable.h"
#include "Model/Variable/intervalvariable.h"
#include "Model/Variable/ratiovariable.h"



class FrequencyAnalysis
{
private:
    Variable* variable;

    static bool isInVector(MisureScale* obj, std::vector<MisureScale*> vector);

public:
    FrequencyAnalysis(Variable* var);
    ~FrequencyAnalysis();

    /**
     * @brief extractAttributes     estrae gli "attributi unici" dai dati della variabile (prima colonna per il calcolo delle frequenze);
     * @return                      restituisce gli attributi unici dai dati della variabile.
     */
    std::vector<MisureScale *> extractAttributes() const;

    /**
     * @brief simpleFrequency       calcola la frequenza semplice a partire dai dati della variabile;
     * @return                      restituisce il vettore con i valori della frequenza semplice.
     */
    std::vector<unsigned int> simpleFrequency() const;

    /**
     * @brief relativeFrequency     calcola la frequenza relativa a partire dai dati della variabile;
     * @return                      restituisce il vettore con i valori della frequenza relativa.
     */
    std::vector<double> relativeFrequency() const;

    /**
     * @brief percentageFrequency   calcola la frequenza percentuale a partire dai dati della variabile;
     * @return                      restituisce il vettore con i valori della frequenza percentuale.
     */
    std::vector<double> percentageFrequency() const;

    /**
     * @brief cumulativeFrequency   calcola la frequenza cumulata a partire dai dati della variabile, sse variabile è costituita da dati ordinabili;
     * @return                      restituisce il vettore con i valori della frequenza cumulata.
     */
    std::vector<unsigned int> cumulativeFrequency() const;

    /**
     * @brief cumulativeRelativeFrequency   calcola la frequenza cumulata relativa a partire dai dati della variabile, sse variabile è costituita da dati ordinabili;
     * @return                              restituisce il vettore con i valori della frequenza cumulata relativa.
     */
    std::vector<double> cumulativeRelativeFrequency() const;

    /**
     * @brief cumulativePercentageFrequency     calcola la frequenza percentuale cumulata a partire dai dati della variabile, sse variabile è costituita da dati ordinabili;
     * @return                                  restituisce il vettore con i valori della frequenza percentuale cumulata.
     */
    std::vector<double> cumulativePercentageFrequency() const;

};

#endif // FREQUENCYANALYSIS_H
