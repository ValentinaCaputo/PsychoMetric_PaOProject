#ifndef VARIABLEVIEW_H
#define VARIABLEVIEW_H

#include <QObject>
#include <QWidget>

#include <QVBoxLayout>
#include <QTableWidget>

#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QTextBlock>
#include <QDialog>
#include <QTextBrowser>
#include <QTextEdit>
#include <QHeaderView>
#include <QAction>
#include <QFont>

#include "Model/Variable/variable.h"
#include "Model/Variable/qualitativevariable.h"
#include "Model/Variable/quantitativevariable.h"

#include "Model/MisureScale/misurescale.h"


class VariableView: public QWidget
{
     Q_OBJECT
private:
    QVBoxLayout* VariableLayout;

    QLabel* name;
    QLabel* misureScale;
    QTableWidget* dataTable;

    QLabel* img;
    QTextEdit* indications;

    QIcon icon;

    /**
     * @brief starter       Imposta la schermata iniziale del box dedicato alla visualizzazione della variabile
     * @param boxLayout     layout su cui verrà aggiunta la schermata iniziale definita dalla funzione
     */
    void starter();


public:
    explicit VariableView(QWidget* parent = nullptr);

    void createTable(Variable *variable);


    void findedData(std::vector<unsigned int> finded);

    void deselectData();

    void insertRow_toDataTable();
    void removeRow_toDataTable();



    void updateTable(Variable* variable);

signals:
    void changeData(QTableWidgetItem* toChange,int row, int column);

    void insertData(int pos);
    void removeData(int pos);
    void openHelp_variable() const;

protected:
    void setDataTable();
};

#endif // VARIABLEVIEW_H
