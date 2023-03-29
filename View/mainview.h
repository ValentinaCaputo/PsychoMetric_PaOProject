#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QObject>
#include <QWidget>

#include <QVBoxLayout>

#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QFile>
#include <QFileDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QInputDialog>
#include <QDialogButtonBox>
#include <QMessageBox>

#include "View/variableview.h"
#include "View/frequencyview.h"
#include "View/chartview.h"
#include "View/ConvertWizard/inputwizard.h"

class Controller;

class mainView : public QWidget
{
    Q_OBJECT
private:
    Controller* controller;

    //barra menù
    QMenu* file;
    QMenu* data;
    QMenu* freqCalculated;
    QMenu* freqShowed;
    QMenu* chart;
    QMenu* help;

    QToolBar* menuIcon;

    VariableView* dataTable; //per gestire la parte dedicata ai dati della variabile

    FrequencyView* freqTable;   //per gestire la parte dedicata alla frequenza


    void addMenu(QVBoxLayout* mainLayout);
    void addIconMenu(QVBoxLayout* mainLayout);
    void addDataSection(QHBoxLayout* sectionLayout);
    void addFreqSection(QHBoxLayout *sectionLayout);
    void setPsychoMetricStyle();

public:
    explicit mainView(QWidget *parent = nullptr);

    void setController(Controller* c);


    //funzioni dedicate a gestione "File"
    void showCreateVariableDialog();
    QString showOpenFileDialog();
    QString showSaveVariableDialog();

    void showVariableTable(Variable* variable);
    void updateVariableTable(Variable* variable);

    //funzioni dedicate a gestione "Dati"

    QString searchAttributeDialog();
    void findData(std::vector<unsigned int> finded); //cerca sia nella tabella dati sia nella tabella frequenza
    void replaceDataDialog();
    void convertVariable();

    void insertRow();
    void removeRow();



    //funzioni dedicate a gestione "Frequenze"
    QString showFreqDialog();
    void calcFreq(int row, FrequencyType freqType);
    void showFreq(FrequencyType freqType, vector<std::string> sortedData, vector<double> freq);
    void showCheckMessage(bool goodJob);


    //funzione dedicata a gestione "Grafici"
    void showChartDialog(ChartView *chart);


    //messaggi all'utente
    int showWarningMessage(const QString &text, const QString& infoText);
    void showErrorMessage(const QString& msg);

    void deselectAll();

signals:
    void createVariable(QLineEdit*,QComboBox*,QLineEdit*);
    void replaceWords(QLineEdit*,QLineEdit*);
    void vectorsForConversion(std::vector<std::string>,std::vector<int>);

    void freqType_calculate(FrequencyType);
    void freqType_toShow(FrequencyType);

    void openChart(unsigned int typeChart);

public slots:
    void showFrequencyErrorSignal(QString errorMessage);

    void openGuidePage(QString title, QUrl url);

};

#endif // MAINVIEW_H
