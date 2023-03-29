#ifndef INSERTPAGE_H
#define INSERTPAGE_H



#include <QWidget>
#include <QWizardPage>

#include <QList>
#include <QLineEdit>

#include "View/ConvertWizard/intropage.h"

class InsertPage: public QWizardPage
{
    Q_OBJECT
private:
    int numberAtt;

    QFormLayout* layout;

    std::vector<QLineEdit*> attribute;
    std::vector<QLineEdit*> maxValue;

   // std::vector<std::string> attributes;
   // std::vector<int> maxValues;

public:
    InsertPage(QWidget* parent = nullptr);

    void initializePage();

    //overloading per quando torna indietro
    void cleanupPage();
};

#endif // INSERTPAGE_H

