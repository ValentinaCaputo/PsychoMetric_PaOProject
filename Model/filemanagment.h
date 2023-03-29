#ifndef FILEMANAGMENT_H
#define FILEMANAGMENT_H

#include "Model/Variable/nominalvariable.h"
#include "Model/Variable/ordinalvariable.h"
#include "Model/Variable/intervalvariable.h"
#include "Model/Variable/ratiovariable.h"

#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QTextStream>
#include <QSaveFile>

#include <string>
#include <vector>
#include <stdexcept>



class FileManagment
{
private:
    std::string path;
public:
    FileManagment(const std::string &pth);
    ~FileManagment() =default;

    /**
     * @brief loadVariable      importa da file xml i dati della variabile;
     * @return                  restituisce in output la variabile creata con i dati letti dal file.
     */
    Variable* loadVariable();

    /**
     * @brief saveVariable      salva i dati della variabile su file xml;
     * @param var               variabile da salvare.
     */
    void saveVariable(Variable* var);
};

#endif // FILEMANAGMENT_H
