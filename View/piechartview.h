#ifndef PIECHARTVIEW_H
#define PIECHARTVIEW_H

#include <QObject>
#include <QWidget>

#include "View/chartview.h"

class PieChartView : public ChartView
{
    Q_OBJECT
public:
    explicit PieChartView(QString title, QString fType, std::vector<std::string> x, std::vector<double> y, QWidget *parent = nullptr);

    QChart* createChart() const override;

signals:

public slots:
};

#endif // PIECHARTVIEW_H
