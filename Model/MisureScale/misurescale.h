#ifndef MISURESCALE_H
#define MISURESCALE_H

#include <cmath>
#include <stdexcept>
#include <typeinfo>
#include <string>

using std::string;


class MisureScale
{
protected:
    /**
     * @brief checkDigit    controlla se i caratteri forniti sottoforma di stringa di caratteri corrispondono a numeri;
     * @param digit         stringa di caratteri da controllare;
     * @return              true sse i caratteri digitati corrispondono ad un numero (reale).
     */
    static bool checkDigit(const string& digit);

public:
    MisureScale();
    virtual ~MisureScale() =default;

    /**
     * @brief getAttribute          selettore dell'attributo associato all'oggetto della misurazione, a seconda della scala di misura andrà letto in maniera diversa;
     * @return                      restituisce l'attributo assegnato all'oggetto.
     */
    virtual string getAttribute() const =0;

    /**
     * @brief changeAttribute        modifica l'attributo che era stato assegnato all'oggetto della misurazione;
     * @param att                    attributo nuovo che andrà a sostituire l'attributo assegnato in precedenza;
     *                               ATTENZIONE: necessario garantire la "coerenza" di att con la scala di misura.
     */
    virtual void changeAttribute(const string & att) =0;

    /**
     * @brief getNumberValue         selettore del valore numerico associato all'oggetto di misurazione, esso prende un significato diverso a seconda della scala di misura scelta;
     * @return                       in output il valore numerico assegnato all'oggetto.
     */
    virtual double getNumberValue() const =0;

    /**
     * @brief changeNumberValue      modifica il valore numerico assegnato all'oggetto della misurazione;
     * @param nv                     valore numerico che deve andare a sostituire il valore precedente;
     *                               ATTENZIONE: necessario verificare la "coerenza" di nv con la scala di misura.
     */
    virtual void changeNumberValue(double nv) =0;


    virtual bool operator==(const MisureScale & ms) const;

    virtual bool operator!=(const MisureScale & ms) const;
};

#endif // MISURESCALE_H
