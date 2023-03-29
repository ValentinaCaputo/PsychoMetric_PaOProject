#ifndef FREQUENCYVIEW_H
#define FREQUENCYVIEW_H

#include <QObject>
#include <QWidget>

#include <QVBoxLayout>
#include <QTableWidget>
#include <QLabel>
#include <QTextEdit>
#include <QTextBrowser>
#include <QGroupBox>
#include <QPushButton>
#include <QDialog>
#include <QHeaderView>

#include "Model/model.h" //lo uso per accedere a enum freqType

//enum FrequencyType {simple, relative, percentage, cumulative, cumulativeRelative, cumulativePercentage};

using std::string;
using std::vector;


class FrequencyView : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout* FrequencyLayout;
    QTableWidget* frequencyTable;

    QLabel* img;
    QTextEdit* indications;

    QPushButton* checkButton;


    /**
     * @brief starter       Imposta la schermata iniziale del box dedicato alla visualizzazione della variabile
     * @param boxLayout     layout su cui verrà aggiunta la schermata iniziale definita dalla funzione
     */
    void starter();

    void setCheckButtonStyle();


public:
    explicit FrequencyView(QWidget *parent = nullptr);

    bool isEmpty() const;

    void reset();
    void createTable(int row, FrequencyType freqType, bool userCalc);

    void showFrequency(FrequencyType freqType, vector<string> sortedData, vector<double> freq);

    void deselectFrequency();



signals:
    void check_frequencies(QString, std::vector<std::string>, std::vector<double>);
    void errorSignal(QString);
    void openHelp_frequency() const;

};

#endif // FREQUENCYVIEW_H
