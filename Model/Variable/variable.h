#ifndef VARIABLE_H
#define VARIABLE_H


#include "Model/MisureScale/misurescale.h"
#include "Model/MisureScale/nominalscale.h"
#include "Model/MisureScale/ordinalscale.h"
#include "Model/MisureScale/intervalscale.h"
#include "Model/MisureScale/ratioscale.h"

#include <string>
#include <list>
#include <vector>


enum scaleType{nominal, ordinal, interval, ratio};

using std::string;
using std::list;
using std::vector;

class Variable
{
protected:
    string name;
    scaleType scale;
    list<MisureScale*> rawData; //tutti i dati devono appartenere alla stessa scala di misura come indicata da scale

    /**
     * @brief checkCoerency         controlla se toCheck appartiene alla stessa scala di misura della variabile;
     * @param toCheck               toCheck puntatore al dato della variabile che deve essere controllato;
     * @return                      true sse toCheck punta alla scala di misura uguale a quella della variabile.
     */
    bool checkCoerency(MisureScale *toCheck) const;

    /**
     * @brief checkScaleCoerency    controlla che tutta la variabile sia coerente e quindi tutti gli elementi di rawData puntino ad oggetti appartenenti alla stessa scala di misura;
     * @return                      true sse c'è coerenza tra dati e scala di misura della variabile.
     */
    virtual bool checkScaleCoerency() const;

    /**
     * @brief deepCopy      assegna a rawData una copia profonda di list;
     * @param list          lista dati da copiare.
     */
    virtual void deepCopy(list<MisureScale*> data) =0;

    /**
     * @brief findIterator          funzione ausiliaria, consente ti trovare l'iteratore corrispondente alla posizione pos;
     * @param pos                   posizione in cui si cerca il dato;
     * @return                      restituisce il puntatore corrispondente.
     */
    list<MisureScale*>::iterator findIterator(unsigned int pos);



public:

    Variable();
    Variable(const string& n, scaleType s);
    virtual ~Variable();
    Variable(const Variable& other);
    virtual Variable& operator= (const Variable& other);


// ***************************************** Selettori **************************************************************

    /**
     * @brief getName       selettore del nome della variabile;
     * @return              restituisce il nome assegnato.
     */
    string getName() const;

    /**
     * @brief getScale      selettore della scala di misura della variabile;
     * @return              restituisce la scala di misura assegnata alla variabile.
     */
    scaleType getScale() const;

    /**
     * @brief getData       selettore dei dati della variabile;
     * @return              restituisce i dati della variabile.
     */
    list<MisureScale*> getData() const;


//***************************************** Modifica Variabile ***************************************************************

    /**
     * @brief renameVariable        rinomina la variabile;
     * @param newName               nuovo nome da assegnare alla variabile.
     */
    void renameVariable(const string& newName);

    /**
     * @brief createData            a partire da attributi e valori numerici costruisce e assegna i dati alla variabile;
     * @param attributes            attributi dei dati da assegnare alla variabile;
     * @param numberValues          valori numerici da assegnare alla variabile.
     */
    virtual void createData(const vector<string>& attributes, const vector<double> &numberValues = vector<double>());

    /**
     * @brief replaceData       sostituisce TUTTI i dati della variabile uguali a oldValue con un nuovo dato;
     * @param oldValue          dato da sostituire;
     * @param newValue          dato nuovo che sostituisce oldValue.
     */
    virtual void replaceData(MisureScale* oldValue, MisureScale* newValue);

    /**
     * @brief replaceAttribute      sostituisce TUTTI gli attributi della variabile uguali a oldAtt con newAtt;
     * @param oldAtt                attributo da sostituire;
     * @param newAtt                nuovo attributo da assegnare.
     */
    virtual void replaceAttribute(const string& oldAtt, const string& newAtt);

    /**
     * @brief replaceNumberValue    sostituisce TUTTI i valori numerici della variabile uguali a oldNV con newNV;
     * @param oldNV                 valore numerico da sostituire;
     * @param newNV                 nuovo valore numerico da assegnare.
     */
    virtual void replaceNumberValue(double oldNV, double newNV);

    /**
     * @brief changeData            modifica il dato nella posizione pos;
     * @param pos                   posizione in cui si trova il dato da modificare;
     * @param newData               dato che andrà a sostituire il precedente.
     */
    virtual void changeData(unsigned int pos, MisureScale* newData);

    /**
     * @brief changeAttribute       modifica l'attributo del dato nella posizione pos;
     * @param pos                   posizione in cui si trova l'atributo da modificare;
     * @param newAttribute          attributo che andrà a sostituire il precedente.
     */
    virtual void changeAttribute(unsigned int pos, const string& newAttribute);

    /**
     * @brief changeNumberValue     modifica il valore numerico del dato nella posizione pos;
     * @param pos                   posizione in cui si trova il valore da modificare;
     * @param newNumberValue        valore numerico che andrà a sostituire il precedente.
     */
    virtual void changeNumberValue(unsigned int pos, double newNumberValue);

    /**
     * @brief sortData          ordina i dati delle variabili costituite da scala di misura ordinabile.
     */
    virtual void sortData();

//******************************************** Ricerca dato/i ***********************************************************************

    /**
     * @brief searchData                cerca tutti i dati uguali a toFind;
     * @param toFind                    dato che si vuole cercare all'interno dei dati della variabile;
     * @return                          restituisce una lista con le posizioni dei dati uguali a toFind.
     */
    vector<unsigned int> searchData(MisureScale* toFind) const;

    /**
     * @brief searchAttribute           cerca tutti i dati che hanno l'attributo uguale a toFind;
     * @param toFind                    attributo che si vuole cercare all'interno dei dati della variabile;
     * @return                          restituisce una lista con le posizioni dei dati con attributo toFind.
     */
    vector<unsigned int> searchAttribute(const string& toFind) const;

    /**
     * @brief searchNumberValue         cerca tutti i dati che hanno il valore numerico uguale a toFind;
     * @param toFind                    valore numerico che si vuole cercare all'interno dei dati della variabile;
     * @return                          restituisce una lista con le posizioni dei dati con valore numerico toFind.
     */
    vector<unsigned int> searchNumberValue(double toFind) const;

//******************************************** Aggiungi/Inserisci *******************************************************************

    /**
     * @brief addData                   aggiunge in coda un nuovo dato;
     * @param toAdd                     dato da aggiungere.
     */
    virtual void addData(MisureScale* toAdd);

    /**
     * @brief insertData                inserisce nella posizione pos il nuovo dato toInsert;
     * @param pos                       posizione dove inserire il nuovo dato;
     * @param toInsert                  nuovo dato da inserire.
     */
    virtual void insertData(unsigned int pos, MisureScale* toInsert);

//******************************************** Elimina dato/i ***********************************************************************
    /**
     * @brief clearData     elimina tutti i dati della variabile.
     */
    void clearData();

    /**
     * @brief resetData     resetta tutti i dati, questo significa che tutti i dati della variabile verranno azzerati e in base alla scala di misura di appartenenza assumeranno valori standard diversi;
     *                      il numero di dati presenti nella variabile rimane invariato.
     */
    virtual void resetData() =0;

    /**
     * @brief eraseByData       elimina il dato uguale a toErase;
     * @param toErase           oggetto che si vuole eliminare.
     */
    void eraseByData(MisureScale* toErase);

    /**
     * @brief eraseByAttribute      elimina il dato con attributo uguale a toErase
     * @param toErase               valore dell'attributo che si vuole eliminare
     */
    void eraseByAttribute(const string& toErase);

    /**
     * @brief eraseByNumberValue    elimina il dato con valore numerico uguale a toErase
     * @param toErase               valore numerico che si vuole eliminare
     */
    void eraseByNumberValue(double toErase);

    /**
     * @brief eraseByPosition       elimina il dato nella posizione pos
     * @param pos                   posizione del dato che si vuole rimuovere dalla lista
     */
     void eraseByPosition(unsigned int pos);

};

#endif // VARIABLE_H
