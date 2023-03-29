#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QWidget>

#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>

#include <QtCharts/QChartView>
#include <QtCharts/chartsnamespace.h>
#include <QPieSeries>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>

#include <QMessageBox>

#include <QLineSeries>

#include <QDialog>

#include "Model/Variable/variable.h"


class ChartView : public QWidget
{
    Q_OBJECT
protected:
    QString variableName;
    QString freqType;
    std::vector<std::string> sortedData;
    std::vector<double> frequency;

public:
    explicit ChartView(QString title, QString freqType, std::vector<std::string> x, std::vector<double> y, QWidget *parent = nullptr);

    virtual QChart* createChart() const =0;

    void showChartDialog(QChart *chartType) const;

signals:

public slots:
};

#endif // CHARTVIEW_H
