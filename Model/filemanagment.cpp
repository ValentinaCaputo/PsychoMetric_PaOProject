#include "filemanagment.h"

FileManagment::FileManagment(const std::string &pth): path(pth) {}

Variable *FileManagment::loadVariable()
{
    QFile file(QString::fromStdString(path));

    if(!file.exists()){
        throw new std::ios_base::failure("File non esiste");
    }

    if(!file.open(QIODevice::ReadOnly)){
        throw new std::ios_base::failure("Errore nell'apertura del file");
    }

    //apertura andata a buon fine

    QXmlStreamReader elements(&file);


    Variable* var = nullptr;
    std::string varName;
    int varScale = -1; //inizializzato con valore di default
    std::vector<std::string> att;
    std::vector<double> numberValue;


    if (elements.readNextStartElement())
        if(elements.name()=="Variable")
        {
            while(elements.readNextStartElement()){
                const QXmlStreamAttributes attributes = elements.attributes();

                if (elements.name()=="Name")
                {
                   varName = attributes.hasAttribute("title") ? attributes.value("title").toString().toStdString() : "";
                }

                if (elements.name()=="Scale")
                {
                    varScale = attributes.hasAttribute("type") ? attributes.value("type").toInt() : -1;
                    if (varScale <0 || varScale >=4){
                                throw new std::runtime_error("Scala di misura letta non valida");
                    }
                }

                if (elements.name()=="Data")
                {
                    std::string varAtt = attributes.hasAttribute("attribute") ? attributes.value("attribute").toString().toStdString() : "";
                    double varNum = attributes.hasAttribute("numberValue") ? attributes.value("numberValue").toDouble() : 0;
                    att.push_back(varAtt);
                    numberValue.push_back(varNum);
                }

                if(!elements.isEndDocument())
                     elements.skipCurrentElement();
            }
        }

    switch (varScale) {
    case 0:
        //nominale
        var = new NominalVariable(varName);
        break;
    case 1:
        //ordinale
        var = new OrdinalVariable(varName);
        break;
    case 2:
        //a intervalli
        var = new IntervalVariable(varName);
        break;
    case 3:
        //a rapporti
        var = new RatioVariable(varName);
        break;
    }

    if (!att.empty())
        var->createData(att,numberValue);
    else
        throw std::runtime_error("Nessuna variabile trovata");

    file.close();

    return var;
}

void FileManagment::saveVariable(Variable *var)
{
    QSaveFile file(QString::fromStdString(path));
    if(!file.open(QIODevice::WriteOnly)){
        throw new std::runtime_error("File non aperto");
    }

    QXmlStreamWriter dataCreator(&file);

    //formattazione dati con indentazione di default
    dataCreator.setAutoFormatting(true);

    //inizio documento
    dataCreator.writeStartDocument();
    dataCreator.writeComment("Scale type: 0-nominal, 1-ordinal, 2-interval, 3-ratio");

    dataCreator.writeStartElement("Variable");

    dataCreator.writeStartElement("Name");
    dataCreator.writeAttribute("title", QString::fromStdString(var->getName()));
    dataCreator.writeEndElement();

    dataCreator.writeStartElement("Scale");
    dataCreator.writeAttribute("type", QString::number(var->getScale()));
    dataCreator.writeEndElement();

    std::list<MisureScale*> rd = var->getData();
    for(auto it:rd){
        dataCreator.writeStartElement("Data");
        dataCreator.writeAttribute("attribute", QString::fromStdString(it->getAttribute()));
        dataCreator.writeAttribute("numberValue", QString::number(it->getNumberValue()));
        dataCreator.writeEndElement();
    }

    dataCreator.writeEndDocument();

    file.commit();
}

