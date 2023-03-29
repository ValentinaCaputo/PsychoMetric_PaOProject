#ifndef INTROPAGE_H
#define INTROPAGE_H

#include <QObject>
#include <QWidget>

#include <QWidget>
#include <QWizardPage>

#include <QFormLayout>
#include <QLabel>
#include <QTextEdit>
#include <QSpinBox>

#include <QLineEdit>

class IntroPage: public QWizardPage
{
    Q_OBJECT

public:
    IntroPage(QWidget* parent = nullptr);
};


#endif // INTROPAGE_H
