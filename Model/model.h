#ifndef MODEL_H
#define MODEL_H

#include "Model/filemanagment.h"
#include "Model/frequencyanalysis.h"

#include <math.h>

enum FrequencyType {simple, relative, percentage, cumulative, cumulativeRelative, cumulativePercentage};

class Model
{
private:
    Variable* variable;
    bool empty = true;

public:
    Model();
    ~Model();

//**************************************** GESTIONE DELLA VARIABILE ******************************************************************


    /**
     * @brief getVariable       selettore della variabile che costituisce il model
     * @return
     */
    Variable* getVariable() const;

    /**
      * @brief isEmpty          verifica se la variabile del modello è vuota;
      * @return                 true sse non è stata ancora definita la variabile.
      */
    bool isEmpty() const;

    /**
     * @brief createVariable        A partire dai dati forniti dall'utente crea una nuova variabile;
     * @param name                  nome della nuova variabile;
     * @param scale                 scala di misura della nuova variabile;
     * @param size                  numero di dati che l'utente vuole inserire.
     */
    void createVariable(std::string name, scaleType scale, int size=0);


    /**
     * @brief openVariable          Importa la variabile da file;
     * @param path                  percorso del file da cui estrarre i dati della variabile.
     */
    void openVariable(std::string path);

    /**
     * @brief saveVariable          Salva la variabile su file;
     * @param path                  percorso del file da scrivere.
     */
    void saveVariable(std::string path);

    /**
     * @brief resetVariable         mantiene intatto il numero di dati della variabile ma ne cancella i valori portandoli a valori di default per la scala di misura
     */
    void resetVariable();


    /**
     * @brief convertToOrdinal      se quantitativa, converte la variabile in Ordinale sostituendola;
     * @param attributes            vettore con attributi che andranno a sostituire i valori numerici;
     * @param max                   limite massimo che determina il criterio per la sostituzione del valore numerico con l'attributo.
     */
    void convertToOrdinal(std::vector<std::string> attributes, std::vector<int> max);


//***************************************** GESTIONE DEI DATI DELLA VARIABILE ********************************************************

    /**
     * @brief addData       aggiunge un nuovo dato in coda alla variabile;
     * @param att           attributo che avrà il nuovo dato;
     * @param numVal        valore numerico del nuovo dato.
     */
    void addData(std::string att ="", double numVal = -99);

    /**
     * @brief insertData    inserisce nella posizione pos un nuovo dato;
     * @param pos           posizione in cui inserire il nuovo dato;
     * @param att           attributo del nuovo dato;
     * @param numVal        valore numerico del nuovo dato.
     */
    void insertData(unsigned int pos, std::string att = "", double numVal = -99);

    /**
     * @brief changeData    modifica il dato della variabile in posizione pos;
     * @param pos           posizione del dato dato da modificare;
     * @param att           eventuale attributo che andrà a sostituire il precedente;
     * @param numVal        eventuale nuovo valore che sostituirà il precedente;
     *
     *                      i valori di default sono indicati perchè a seconda del valore di default si andrà a modificare l'attributo o il valore numerico.
     */
    void changeData(unsigned int pos, std::string att ="", double numVal=0); //SINGOLO DATO

    /**
     * @brief changeQualitativeData     specifica per variabile qualitativa, cambia il dato in posizione pos con il nuovo dato newValue
     * @param pos
     * @param newValue
     */
    void changeQualitativeData(int pos, MisureScale* newValue);

    /**
     * @brief replaceData       Sostituisce tutti gli attributi della variabile==oldValue con l'attributo == newValue
     * @param oldValue          attributo da sostituire
     * @param newValue          attributo nuovo che sostituisce il precedente
     */
    void replaceData(std::string oldValue, std::string newValue); //PIù DATI

    /**
     * @brief findData      cerca tra i dati della variabile i valori con attributo == att oppure con valore numerico == numVal;
     * @param att           parola o carattere che si vuole ricercare all'interno della variabile;
     * @param numVal        numero che si vuole cercare all'interno della variabile;
     * @return              restituisce le posizioni di tutti i dati che contengono l'attributo o il valore numerico richiesto.
     */
    std::vector<unsigned int> findData(std::string att ="", double numVal=0);

    /**
     * @brief eraseData     elimina il dato che si trova nella posizione pos
     * @param pos
     */
    void eraseData(unsigned int pos);

//*******************************************  ANALISI DELLE FREQUENZE ************************************************************

    /**
     * @brief getSortedData     estrae gli attributi "unici" e ordinati che definiscono la variabile;
     * @return                  vettore con gli attributi richiesti.
     */
    std::vector<std::string> getSortedData() const;

    /**
     * @brief checkSortedData   controlla se gli attributi individuati nel vettore dataToCheck corrispondono agli stessi attributi estratti dalla variabile;
     * @param dataToCheck       vettore con gli attributi da controllare;
     * @return                  true sse i due vettori contengono gli stessi valori.
     */
    bool checkSortedData(std::vector<std::string> dataToCheck) const;

    /**
     * @brief checkFrequencyAnalysis        controlla che la frequenza calcolata dall'utente sia corretta;
     * @param freqType                      tipo di frequenza calcolata;
     * @param freqToCheck                   frequenza calcolata dall'utente;
     * @return                              true sse la frequenza calcolata dall'utente è corretta.
     */
    bool checkFrequencyAnalysis(FrequencyType freqType, std::vector<double> freqToCheck) const;

    /**
     * @brief calculateFrequency            calcola esclusivamente il tipo di frequenza richiesto;
     * @param freqType                      tipo di frequenza da calcolare;
     * @return                              restituisce il calcolo della frequenza desiderata.
     */
    std::vector<double> frequency_toCalculate(FrequencyType freqType) const;

    /**
     * @brief frequency_toShow              crea un unico vettore con tutte le frequenze che devono essere mostrate;
     * @param freqType                      tipo di frequenza richiesta;
     * @return                              vettore unico contenente l'unione dei vettori con relative frequenze necessarie al calcolo della frequenza richiesta.
     */
    std::vector<double> frequency_toShow(FrequencyType freqType) const;

};

#endif // MODEL_H
