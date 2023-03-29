#include "linearchartview.h"

LinearChartView::LinearChartView(QString title, QString fType, std::vector<std::string> x, std::vector<double> y, QWidget *parent) :
    ChartView(title, fType, x, y, parent)
{

}

QChart *LinearChartView::createChart() const
{
    QChart* lineChart = new QChart();
    lineChart->setTitle(variableName +" poligono di frequenza");


    QLineSeries *series = new QLineSeries(lineChart);
    series->setName(freqType);
    for (unsigned int i=0; i< sortedData.size(); i++) {
        series->append(std::stod(sortedData[i]),frequency[i]);
    }

    lineChart->addSeries(series);
    lineChart->createDefaultAxes();

    return lineChart;
}
