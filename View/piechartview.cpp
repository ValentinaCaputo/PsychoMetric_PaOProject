#include "piechartview.h"

PieChartView::PieChartView(QString title, QString fType, std::vector<std::string> x, std::vector<double> y, QWidget *parent) :
    ChartView(title, fType,x,y,parent)
{

}

QChart *PieChartView::createChart() const
{
    QChart* pieChart = new QChart;
    pieChart->setTitle(variableName +" - grafico a torta");

    QPieSeries* series = new QPieSeries(pieChart);

    int n = frequency.size();
    for (int i=0; i<n; i++){
        QPieSlice* slice = new QPieSlice(QString::fromStdString(sortedData[i]),qreal(frequency[i]));
        slice->setLabel(QString::fromStdString(sortedData[i])+" - "+QString::number(frequency[i],'g',2));
        slice->setLabelVisible();
        series->append(slice);
    }

    pieChart->addSeries(series);
    return pieChart;
}
