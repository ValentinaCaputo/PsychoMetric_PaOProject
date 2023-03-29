#ifndef LINEARCHARTVIEW_H
#define LINEARCHARTVIEW_H

#include <QObject>
#include <QWidget>
#include <QString>

#include "View/chartview.h"


class LinearChartView : public ChartView
{
    Q_OBJECT
public:
    explicit LinearChartView(QString title, QString fType, std::vector<std::string> x, std::vector<double> y, QWidget *parent = nullptr);

    QChart* createChart() const override;

signals:

public slots:
};

#endif // LINEARCHARTVIEW_H
