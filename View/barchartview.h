#ifndef BARCHARTVIEW_H
#define BARCHARTVIEW_H

#include <QObject>
#include <QWidget>
#include <QString>

#include "View/chartview.h"

class BarChartView : public ChartView
{
    Q_OBJECT
public:
    explicit BarChartView(QString title, QString fType, std::vector<std::string> x, std::vector<double> y, QWidget *parent = nullptr);

    QChart* createChart() const override;

signals:

public slots:
};

#endif // BARCHARTVIEW_H
