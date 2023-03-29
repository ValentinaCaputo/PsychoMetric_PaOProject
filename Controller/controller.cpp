#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{

}


void Controller::setModel(Model* m) { model = m; }

void Controller::setView(mainView* v) { view = v; }

FrequencyType Controller::translateFT(QString toTranslate)
{
    if(toTranslate == "semplice")
        return simple;
    if(toTranslate =="relativa")
        return relative;
    if(toTranslate =="percentuale")
        return percentage;
    if(toTranslate =="cumulata")
        return cumulative;
    if(toTranslate =="cumulata relativa")
        return cumulativeRelative;
    if(toTranslate =="percentuale cumulata")
        return cumulativePercentage;

    throw std::logic_error("La stringa indicata non si riferisce a nessuna frequenza");

}

MisureScale *Controller::defineQualitativeData(std::string att, int numbVal) const
{
    scaleType scale = model->getVariable()->getScale();

    if(scale==nominal)
        return new NominalScale(att,numbVal);
    if(scale == ordinal)
        return new OrdinalScale(att,numbVal);

    throw std::runtime_error("La variabile non è qualitativa");
}



void Controller::newVariable(QLineEdit *name, QComboBox *scale, QLineEdit *tot)
{
    try{
        std::string variable_name = name->text().toStdString();
        int scaleIndex = scale->currentIndex();
        int size = tot->text().toInt();

        switch (scaleIndex){
        case 0:
            model->createVariable(variable_name, nominal,size);
            break;
        case 1:
            model->createVariable(variable_name, ordinal,size);
            break;
        case 2:
            model->createVariable(variable_name, interval,size);
            break;
        case 3:
            model->createVariable(variable_name, ratio,size);
            break;
        }


        view->showVariableTable(model->getVariable());
    }
    catch(std::runtime_error exc){
        view->showErrorMessage(exc.what());
    }

}


void Controller::open() const
{
    try{
    QString path = view->showOpenFileDialog();
    model->openVariable(path.toStdString());
    view->showVariableTable(model->getVariable());

    }

    catch (std::runtime_error exc) {
        view->showErrorMessage(exc.what());
    }
    catch (std::logic_error exc){
        view->showErrorMessage(exc.what());
    }

}

void Controller::save() const
{
    try{
        if(model->isEmpty())
            throw std::runtime_error("Non c'è nessuna variabile da salvare! Importa i dati di una variabile o creane una nuova!");
        QString path = view->showSaveVariableDialog();
        model->saveVariable(path.toStdString());
    }
    catch (std::runtime_error exc){
        view->showErrorMessage(exc.what());
    }

    catch (std::logic_error exc){
        view->showErrorMessage(exc.what());
    }

}

void Controller::coerencyCheck(int column, int row, QTableWidgetItem* toChange) const
{
    try{
        if(column==0){
            int other = QInputDialog::getInt(view,"","Cambia etichetta associata a "+toChange->text());
            model->changeQualitativeData(row,defineQualitativeData(toChange->text().toStdString(),other));
            view->showVariableTable(model->getVariable());
        }
        else{
            QString other = QInputDialog::getText(view,"","Cambia attributo associato a "+toChange->text());
            model->changeQualitativeData(row,defineQualitativeData(other.toStdString(),toChange->text().toInt()));
            view->showVariableTable(model->getVariable());
        }
    }
    catch (std::logic_error exc){
        view->showErrorMessage(exc.what());

        view->showVariableTable(model->getVariable());
    }
    catch(std::runtime_error exc){
        view->showErrorMessage(exc.what());
    }

}

void Controller::updateVariable(QTableWidgetItem* toChange,int row, int column) const
{
    try{
        if(column>=0){
            QString item = toChange->text();
            if(column==0)
               model->changeData(row,item.toStdString());
            else{
                //deve essere un numero!
                bool success;
                double numb = item.toDouble(&success);
                if(success)
                    model->changeData(row,"",numb);
                else throw std::invalid_argument("Sono ammessi solo valori numerici");

            }
            view->updateVariableTable(model->getVariable());
        }
    }
    catch(std::invalid_argument exc){
        view->showErrorMessage(exc.what());
        view->updateVariableTable(model->getVariable());
    }

    catch(std::runtime_error exc){
       // view->showVariableTable(model->getVariable());
        view->showErrorMessage(exc.what());
    }

    catch(std::logic_error exc){
        //se variabile qualitativa do la possibilità all'utente di correggere l'incoerenza nei dati
        if(dynamic_cast<QualitativeVariable*>(model->getVariable())){
            int reply = view->showWarningMessage(exc.what(),"Si vuole modificare anche l'attributo/etichetta?");

            if (reply== QMessageBox::Ok)
            {
                coerencyCheck(column, row, toChange);

            }
            else
            {
                view->updateVariableTable(model->getVariable());
            }
        }
        else {
            //se variabile quantitativa deve soltanto ritornare l'errore
            view->showErrorMessage(exc.what());
            view->updateVariableTable(model->getVariable());
        }

    }

}


void Controller::create() const
{
    try{
        view->showCreateVariableDialog();
    }
    catch(std::runtime_error exc){
        view->showErrorMessage(exc.what());
    }
}

void Controller::find() const
{
    try{
        if(model->isEmpty())
            throw std::runtime_error("Necessario prima definire una variabile");
        view->deselectAll();
        QString toSearch = view->searchAttributeDialog();
        std::vector<unsigned int> finded;
        std::vector<unsigned int> findedNV;
        finded = model->findData(toSearch.toStdString());

        bool success;
        double nv = toSearch.toDouble(&success);
        if(success)
            findedNV = model->findData("",nv);
        finded.insert(finded.end(), findedNV.begin(),findedNV.end());

        if(finded.size()==0)
            view->showErrorMessage("Non è stato trovato alcun valore uguale a "+toSearch);
        view->findData(finded);
    }
    catch(std::runtime_error exc){
        view->showErrorMessage(exc.what());
    }
}

void Controller::replace() const
{
    try{
        if(model->isEmpty())
            throw std::runtime_error("Necessario prima definire una variabile");
        view->replaceDataDialog();
    }
    catch(std::runtime_error exc){
        view->showErrorMessage(exc.what());
    }
}

void Controller::doReplaceWords(QLineEdit*prevWord, QLineEdit*newWord) const
{
    try{
        model->replaceData(prevWord->text().toStdString(), newWord->text().toStdString());
        view->updateVariableTable(model->getVariable());
    }
    catch(std::runtime_error exc){
        view->showErrorMessage(exc.what());
    }
    catch(std::logic_error exc){
        view->showErrorMessage(exc.what());
    }

}

void Controller::reset() const
{
    try{
        if(model->isEmpty())
            throw std::runtime_error("Necessario prima definire una variabile");
        int reply = view->showWarningMessage("Proseguendo con questa operazione tutti i dati verranno cancellati.", "Si desidera continuare con il reset dei dati?");
        if(reply == QMessageBox::Ok){
            model->resetVariable();
            view->updateVariableTable(model->getVariable());
        }
    }
    catch(std::runtime_error exc){
        view->showErrorMessage(exc.what());
    }

}

void Controller::rowToInsert(int pos)
{
    try{
        model->insertData(pos);
        view->updateVariableTable(model->getVariable());
    }
    catch(std::runtime_error exc){
        view->showErrorMessage(exc.what());
    }
    catch(std::logic_error){
        //se sono qui è perché la tabella è vuota
        model->addData();
        view->updateVariableTable(model->getVariable());
    }
}

void Controller::rowToRemove(int pos)
{
    try{
        model->eraseData(pos);
        view->updateVariableTable(model->getVariable());
    }
    catch(std::runtime_error exc){
        view->showErrorMessage(exc.what());
    }
    catch(std::logic_error){
        view->showErrorMessage("Impossibile cancellare la riga: nessuna riga presente");
    }

}

void Controller::convertSignal()
{
    try{
        if(model->isEmpty())
            throw std::runtime_error("Definire prima una variabile quantitativa!");
        if(!dynamic_cast<QuantitativeVariable*>(model->getVariable()))
            throw std::runtime_error("La variabile non è quantitativa!");

        view->convertVariable();
    }
    catch(std::runtime_error exc){
        view->showErrorMessage(exc.what());
    }
}

void Controller::convert(std::vector<std::string> att, std::vector<int> max)
{
    try{
        model->convertToOrdinal(att,max);
        view->showVariableTable(model->getVariable());
    }
    catch(std::runtime_error exc){
        view->showErrorMessage(exc.what());
    }
}

void Controller::calculateFrequency(FrequencyType freqType)
{
    try{
        if(model->isEmpty())
            throw std::runtime_error("Necessario prima definire una variabile");
        std::vector<double> requiredFreq = model->frequency_toCalculate(freqType);
        view->calcFreq(requiredFreq.size(),freqType);
        frequency_choose = false;
        frequencyType = freqType;
    }
    catch(std::runtime_error exc){
        view->showErrorMessage(exc.what());
    }
    catch(std::logic_error exc){
        view->showErrorMessage(exc.what());
    }

}

void Controller::calculateFrequency_button()
{
    try{
        if(model->isEmpty())
            throw std::runtime_error("Necessario prima definire una variabile");
        QString requestedFreq = view->showFreqDialog();
        FrequencyType freqType = translateFT(requestedFreq);
        std::vector<double> requiredFreq = model->frequency_toCalculate(freqType);
        view->calcFreq(requiredFreq.size(),freqType);
        frequency_choose = false;
        frequencyType = freqType;
    }
    catch(std::logic_error exc){
        view->showErrorMessage(exc.what());
    }
    catch(std::runtime_error exc){
        view->showErrorMessage(exc.what());
    }


}

void Controller::showFrequency(FrequencyType freqType)
{
    try{
        if(model->isEmpty())
            throw std::runtime_error("Necessario prima definire una variabile");
        std::vector<double> freq = model->frequency_toShow(freqType);
        view->showFreq(freqType,model->getSortedData(),freq);
        frequency_choose = true;
        frequencyType = freqType;
    }
    catch(std::runtime_error exc){
        view->showErrorMessage(exc.what());
    }
    catch(std::logic_error exc){
        view->showErrorMessage(exc.what());
    }
}

void Controller::showFrequency_button()
{
    try{
        if(model->isEmpty())
            throw std::runtime_error("Necessario prima definire una variabile");
        QString requestedFreq = view->showFreqDialog();
        FrequencyType freqType = translateFT(requestedFreq);

        std::vector<double> freq = model->frequency_toShow(freqType);
        view->showFreq(freqType,model->getSortedData(),freq);

        frequency_choose = true;
        frequencyType = freqType;

    }
    catch(std::logic_error exc){
        view->showErrorMessage(exc.what());
    }
    catch(std::runtime_error exc){
        view->showErrorMessage(exc.what());
    }
}

void Controller::doCheckFrequencies(QString freqType, std::vector<std::string> calculated_sortedData, std::vector<double> calculated_frequencies)
{
    try{
        FrequencyType ft = translateFT(freqType);
        bool success_sortedData = model->checkSortedData(calculated_sortedData);
        bool success_freq = model->checkFrequencyAnalysis(ft, calculated_frequencies);
        view->showCheckMessage(success_sortedData && success_freq);
    }
    catch(std::runtime_error exc){
        view->showErrorMessage(exc.what());
    }
    catch(std::logic_error exc){
        view->showErrorMessage(exc.what());
    }

}

void Controller::updateFrequencyTable()
{
    if(frequency_choose)
        showFrequency(frequencyType);
    else
        calculateFrequency(frequencyType);


}

void Controller::doOpenChart(unsigned int chartType)
{
    try{
        if(model->isEmpty())
            throw std::runtime_error("Necessario prima definire una variabile");


        QString title = QString::fromStdString(model->getVariable()->getName());
        QString freqType = view->showFreqDialog();

        switch (chartType) {
        case 0:
            view->showChartDialog(new PieChartView(title,freqType,model->getSortedData(),model->frequency_toCalculate(translateFT(freqType))));
            break;
        case 1:
        {
            if(dynamic_cast<QualitativeVariable*>(model->getVariable()))
                view->showChartDialog(new BarChartView(title,freqType,model->getSortedData(),model->frequency_toCalculate(translateFT(freqType))));
            else
                view->showErrorMessage("Il grafico a barre non è adatto ad una variabile quantitativa. Prova con il poligono di frequenze!");
            break;
        }
        case 2:
        {
            if(dynamic_cast<QuantitativeVariable*>(model->getVariable()))
                view->showChartDialog(new LinearChartView(title,freqType,model->getSortedData(),model->frequency_toCalculate(translateFT(freqType))));
            else
                view->showErrorMessage("Non è possibile costruire il poligono di frequenza con una variabile qualitativa. Prova con un grafico a torta o a barre!");
            break;
        }
        default:
            break;
        }


    }
    catch(std::logic_error exc){
        view->showErrorMessage(exc.what());
    }
    catch(std::runtime_error exc){
        view->showErrorMessage(exc.what());
    }
}

