#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QInputDialog>

#include "Model/model.h"
#include "View/mainview.h"

#include "View/piechartview.h"
#include "View/barchartview.h"
#include "View/linearchartview.h"

class Controller : public QObject
{
    Q_OBJECT
private:
    mainView* view;
    Model* model;

    bool frequency_choose; // 0 se calcolata
                           // 1 se mostrata

    FrequencyType frequencyType;

public:
    explicit Controller(QObject *parent = nullptr);

    void setModel(Model* m);
    void setView (mainView* v);

    FrequencyType translateFT(QString toTranslate);
    MisureScale* defineQualitativeData(std::string att, int numbVal) const;


    void coerencyCheck(int column, int row, QTableWidgetItem* toChange) const;

public slots:
    //file
    void newVariable(QLineEdit* name,QComboBox* scale,QLineEdit* tot);
    void create() const;
    void open() const;
    void save() const;

    //data
    void updateVariable(QTableWidgetItem* toChange, int row, int column) const;
    void find() const;
    void replace() const;
    void doReplaceWords(QLineEdit *prevWord, QLineEdit *newWord) const;
    void reset() const;
    void rowToInsert(int pos);
    void rowToRemove(int pos);
    void convertSignal();
    void convert(std::vector<std::string> att, std::vector<int> max);

    //frequency
    void calculateFrequency(FrequencyType freqType);
    void calculateFrequency_button();

    void showFrequency(FrequencyType freqType);
    void showFrequency_button();

    void doCheckFrequencies(QString freqType, std::vector<std::string> calculated_sortedData, std::vector<double> calculated_frequencies);

    void updateFrequencyTable();


    //chart
    void doOpenChart(unsigned int chartType);
};

#endif // CONTROLLER_H
