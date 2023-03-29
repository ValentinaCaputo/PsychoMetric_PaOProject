#include "conclusionpage.h"

ConclusionPage::ConclusionPage(QWidget *parent): QWizardPage(parent)
{
    setTitle("Esito procedura:");

    layout = new QHBoxLayout;

    setLayout(layout);
}

bool ConclusionPage::checkConsistency(std::vector<std::string> attributes, std::vector<int> maxValues)
{
    //controlli per procedere con la conversione dei dati
    if(attributes.empty() && maxValues.empty()) return false;
    for(unsigned int i=0; i<attributes.size()-1; i++){
        if(maxValues[i+1]<=maxValues[i])
            return false;
        for(unsigned int j=i+1; j<attributes.size(); j++){
            if(attributes[i]==attributes[j])
                return false;
        }
    }
    return true;
}

bool ConclusionPage::check() const
{
    int numAtt = field("numAtt").toInt();
    std::vector<std::string> attributes;
    std::vector<int> maxValues;
    for (int i=0; i<numAtt; i++){
        std::string att = field(tr("attribute" + i)).toString().toStdString();
        attributes.push_back(att);
        int max = field(tr("maxValue" + i)).toInt();
        maxValues.push_back(max);
    }
    return checkConsistency(attributes, maxValues);

}


void ConclusionPage::initializePage()
{
    exitus = new QLabel;
    if(check()){
        exitusIcon = QIcon(":/resources/icons/ok.png");
        exitus->setPixmap(exitusIcon.pixmap(30,30));
        message = new QLabel("La procedura è andata a buon fine!"
                         "Premi il tasto ""Finish"" per creare la tua nuova variabile");
        message->setWordWrap(true);
        setFinalPage(true);

    }
    else {
        exitusIcon = QIcon(":/resources/icons/wrong.png");
        message = new QLabel("Mi dispiace, la procedura non è andata a buon fine! "
                             "Torna indietro e ricontrolla i valori inseriti: attenzione alle ripetizioni, all'ordine con "
                             "con cui sono stati indicati i valori massimi");
        exitus->setPixmap(exitusIcon.pixmap(30,30));
        message->setWordWrap(true);
    }

    layout->addWidget(exitus);
    layout->addWidget(message);

}

bool ConclusionPage::isComplete() const
{
    if(check())
        return true;
    else
        return false;
}


void ConclusionPage::cleanupPage()
{
    layout->removeWidget(exitus);
    layout->removeWidget(message);
    delete exitus;
    delete message;
}
