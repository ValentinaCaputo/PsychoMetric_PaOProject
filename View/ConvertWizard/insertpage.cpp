#include "insertpage.h"

InsertPage::InsertPage(QWidget *parent): QWizardPage(parent)
{
    setTitle("Definisci gli attributi con i relativi valori soglia:");

    layout = new QFormLayout;

    setLayout(layout);
}

void InsertPage::initializePage()
{
    numberAtt = field("numAtt").toInt();

    for (int i=0; i<numberAtt; i++){
        QLineEdit* att = new QLineEdit;
        att->setPlaceholderText("Inserisci nome attributo");
        att->setMaxLength(20);
        QRegExpValidator* nameValidator = new QRegExpValidator(QRegExp( "^[a-zA-Zàèòùì]+$"));
        att->setValidator(nameValidator);
        att->setToolTip("Il nome dell'attributo può essere indicato con una sola parola composta unicamente da lettere");
        attribute.push_back(att);


        QLineEdit* mv = new QLineEdit;
        mv->setPlaceholderText("valore massimo dell'attributo");
        mv->setValidator(new QIntValidator());
        maxValue.push_back(mv);

        layout->addRow("Attributo: ", attribute[i]);

        layout->addRow("Valore Massimo: ", maxValue[i]);

        //layout->addItem(new QSpacerItem(0,10));

        registerField(tr("attribute*" + i), attribute[i]);
        registerField(tr("maxValue*" + i), maxValue[i]);
    }

}

void InsertPage::cleanupPage()
{
    for (int i=0; i<numberAtt; i++){
        layout->removeRow(attribute[i]);
        layout->removeRow(maxValue[i]);
    }

    attribute.clear();
    maxValue.clear();

}

