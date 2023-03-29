#ifndef INPUTWIZARD_H
#define INPUTWIZARD_H

#include <QObject>

#include <QWidget>
#include <QWizard>

#include <QPushButton>

#include "View/ConvertWizard/intropage.h"
#include "View/ConvertWizard/insertpage.h"
#include "View/ConvertWizard/conclusionpage.h"

class Controller;

class InputWizard: public QWizard
{
    Q_OBJECT
private:
    std::vector<std::string> attributes;
    std::vector<int> maxValues;
public:
    InputWizard(QWidget *parent = nullptr);

signals:
    void createOrdinalVariable(std::vector<std::string>, std::vector<int>);
};

#endif // INPUTWIZARD_H
