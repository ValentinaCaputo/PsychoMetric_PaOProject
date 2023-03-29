#include "inputwizard.h"

InputWizard::InputWizard (QWidget *parent): QWizard(parent)
{
    addPage(new IntroPage);
    addPage(new InsertPage);
    addPage(new ConclusionPage);

    connect(this, &InputWizard::accepted,[=]() {
        int numAtt = field("numAtt").toInt();
        for (int i=0; i<numAtt; i++){
            std::string att = field(tr("attribute" + i)).toString().toStdString();
            attributes.push_back(att);
            int max = field(tr("maxValue" + i)).toInt();
            maxValues.push_back(max);
        }
        emit createOrdinalVariable(attributes, maxValues);
    });

    //setMinimumSize(700,480);
    setFixedSize(750,550);

}

/*
void InputWizard::accept()
{
    int numAtt = field("numAtt").toInt();
    for (int i=0; i<numAtt; i++){
        std::string att = field(tr("attribute" + i)).toString().toStdString();
        attributes.push_back(att);
        int max = field(tr("maxValue" + i)).toInt();
        maxValues.push_back(max);
    }

    QDialog::accept();
}
*/
