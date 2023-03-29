#include "barchartview.h"

BarChartView::BarChartView(QString title, QString fType, std::vector<std::string> x, std::vector<double> y, QWidget *parent) :
    ChartView(title,fType,x,y,parent)
{

}

QChart *BarChartView::createChart() const
{
    QChart* barChart = new QChart();
    barChart->setTitle(variableName +" - grafico a barre");

    QBarSeries *series = new QBarSeries(barChart);
    QBarSet *set =new QBarSet("frequenza "+freqType);

    for (unsigned int i=0; i < frequency.size(); i++) {
        set->append(frequency[i]);
        series->append(set);
    }
    barChart->addSeries(series);

    QStringList categories;
    for(auto it:sortedData)
        categories << QString::fromStdString(it);
    QBarCategoryAxis * axisX = new QBarCategoryAxis;
    axisX->append(categories);

    barChart->createDefaultAxes();
    barChart->setAxisX(axisX,series);

    return barChart;
}
