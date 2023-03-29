#include "chartview.h"

ChartView::ChartView(QString title, QString fType, std::vector<std::string> x, std::vector<double> y, QWidget *parent) :
    QWidget(parent),
    variableName(title),
    freqType(fType),
    sortedData(x),
    frequency(y)

{

}


void ChartView::showChartDialog(QChart *chartType) const
{
    QDialog* dialog = new QDialog();
    QVBoxLayout* dialogLayout = new QVBoxLayout;

    QChartView* chart = new QChartView(chartType);
    dialogLayout->addWidget(chart);

    dialog->setMinimumSize(640,480);
    dialog->setStyleSheet("background-color: #3587A4;"
                          "color: white;");

    dialog->setLayout(dialogLayout);
    dialog->show();
}


