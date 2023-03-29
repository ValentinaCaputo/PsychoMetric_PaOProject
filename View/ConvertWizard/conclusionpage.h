#ifndef CONCLUSIONPAGE_H
#define CONCLUSIONPAGE_H

#include <QObject>
#include <QWidget>
#include <QWizardPage>
#include <QWizard>

#include <QHBoxLayout>
#include <QLabel>
#include <QIcon>

#include <vector>

#include "View/ConvertWizard/insertpage.h"

class ConclusionPage: public QWizardPage
{
    Q_OBJECT
private:
    QHBoxLayout* layout;
    QLabel* exitus;
    QIcon exitusIcon;
    QLabel* message;

    static bool checkConsistency(std::vector<std::string> attributes, std::vector<int> maxValues);


public:
    ConclusionPage(QWidget *parent = nullptr);
    bool check() const;
    void initializePage();
    //bool validatePage();
    bool isComplete() const;
    void cleanupPage();

};

#endif // CONCLUSIONPAGE_H
