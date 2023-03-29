#include "frequencyview.h"

void FrequencyView::starter()
{
    //immagine
    img = new QLabel(this);
    QPixmap pic = QPixmap(":/resources/step2.png");
    pic = pic.scaledToHeight(80);
    img->setPixmap(pic);
    FrequencyLayout->addWidget(img,0,Qt::AlignHCenter);

    //testo
    indications = new QTextEdit(this);
    indications->setHtml("<p>Dopo aver definito la tua variabile o aver importato i dati necessari, inizia a ricavare le prime informazioni calcolando la distribuzione di frequenza.</p>"
                         "<p>Se vuoi fare esercizio su come si calcola la frequenza clicca su <img src="":/resources/icons/freqCalc.png"" width=""20"" height=""20""> <strong>&#34;Calcola frequenza&#34;</strong> e seleziona il tipo di frequenza che desideri calcolare.</p>"
                         "<p>Se invece vuoi arrivare direttamente alla soluzione, clicca su <img src="":/resources/icons/freqShow.png"" width=""20"" height=""20""> <strong>&#34;Mostra frequenza&#34;</strong> e seleziona il tipo di frequenza. </p>"
                         );

    //indications->setFont(QFont("OldEnglish", 12));
    indications->setReadOnly(true);

    FrequencyLayout->addWidget(indications,0,Qt::AlignJustify);
}

void FrequencyView::setCheckButtonStyle()
{
    checkButton->setStyleSheet("padding: 3px;"
            "min-width: 8em;"
            "background-color: #EBEBFF;"
            "color: black;"
            "border: 1px solid #6A7A8A;"
            "border-radius: 1px;"
            "border-style: outset;"
            "color: black;");

}



FrequencyView::FrequencyView(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout();

    QGroupBox* frequencyBox = new QGroupBox();
    FrequencyLayout = new QVBoxLayout();

    // imposto l'heading
    QPushButton* help = new QPushButton(QIcon(":/resources/icons/help.png"),"");
    help->setCursor(QCursor(Qt::PointingHandCursor));
    help->setMaximumSize(40,40);
    help->setIconSize(QSize(25,25));
    connect(help, SIGNAL(clicked(bool)), this, SIGNAL(openHelp_frequency()));

    QLabel* title = new QLabel("Distribuzione di frequenza");

    QHBoxLayout* heading = new QHBoxLayout();
    heading->addWidget(help);
    heading->addWidget(title);

    FrequencyLayout->addLayout(heading);

    //imposto schermata di apertura
    starter();

    //definisco il bottone check in caso di richiesta calcolo
    checkButton = new QPushButton("Controlla");

    connect(checkButton, &QPushButton::clicked,[this](){
        int rowNumb = frequencyTable->rowCount();
        int columnNumb = frequencyTable->columnCount();
        std::vector<std::string> givenSortedData;
        std::vector<double> calculated_frequencies;
        bool everythingOK = true;

        for(int row = 0; row<rowNumb; row++){
            QString data = frequencyTable->item(row,0)->text();
            bool success;
            double quantitativeData = data.toDouble(&success);
            if(success)
                //standardizzo la precisione, altrimenti confronto fatto su string di valori di diversa precisione
                givenSortedData.push_back(std::to_string(quantitativeData));
            else
                givenSortedData.push_back(data.toStdString());
        }

        for(int col=1; col<columnNumb && everythingOK; col++){
            for(int row=0; row<rowNumb && everythingOK; row++){
                bool ok;
                QString item = frequencyTable->item(row,col)->text(); //cella con frequenza da catturare
                double f = item.toDouble(&ok);
                if(ok){
                    calculated_frequencies.push_back(f);
                }
                else
                    everythingOK = false;
            }
        }

        if(everythingOK)
        {
            QString freqType = (frequencyTable->horizontalHeaderItem(columnNumb-1))->text();
            emit check_frequencies(freqType, givenSortedData,calculated_frequencies);
        }
        else
            emit errorSignal("Ops ti deve essere sfuggita qualche frequenza! Controlla che siano stati inseriti tutti i numeri al loro posto...");

    });

    FrequencyLayout->addWidget(checkButton);
    checkButton->setHidden(true);

    //definisco la tabella delle frequenze
    frequencyTable = new QTableWidget();

    frequencyBox->setLayout(FrequencyLayout);
    layout->addWidget(frequencyBox);
    setLayout(layout);

    setCheckButtonStyle();

}

bool FrequencyView::isEmpty() const
{
    return frequencyTable->isHidden();
}

void FrequencyView::reset()
{
    //rimuovo la tabella che ormai non serve più
    FrequencyLayout->removeWidget(frequencyTable);
    frequencyTable->setHidden(true);
    checkButton->setHidden(true);

    //riporta allo stato iniziale la vista della sezione frequenza
    if(img->isHidden() && indications->isHidden()){
        img->setHidden(false);
        indications->setHidden(false);
    }
}

void FrequencyView::createTable(int row, FrequencyType freqType, bool userCalc)
{
    frequencyTable->clear();
    if(frequencyTable->isHidden())
        frequencyTable->setVisible(true);

    frequencyTable->setRowCount(row);

    //sulla base del tipo di frequenza cambia il # di colonne; la prima è sempre dedicata alla variabile ordinata (con valori unici)
    //header della tabella:

    QTableWidgetItem* sortedData = new QTableWidgetItem("Dati ordinati");
    QTableWidgetItem* simpleF = new QTableWidgetItem("semplice");
    QTableWidgetItem* relativeF = new QTableWidgetItem("relativa");
    QTableWidgetItem* percentageF = new QTableWidgetItem("percentuale");
    QTableWidgetItem* cumulativeF = new QTableWidgetItem("cumulata");
    QTableWidgetItem* cumRelF = new QTableWidgetItem("cumulata relativa");
    QTableWidgetItem* cumPerF = new QTableWidgetItem("percentuale cumulata");

    frequencyTable->setHorizontalHeaderItem(0,sortedData);


    switch (freqType) {
    case simple:
    {
        frequencyTable->setColumnCount(2);
        frequencyTable->setHorizontalHeaderItem(0,sortedData);
        frequencyTable->setHorizontalHeaderItem(1,simpleF);
        break;
    }
    case relative:
    {
        frequencyTable->setColumnCount(3);
        frequencyTable->setHorizontalHeaderItem(0,sortedData);
        frequencyTable->setHorizontalHeaderItem(1,simpleF);
        frequencyTable->setHorizontalHeaderItem(2,relativeF);
        break;
    }
    case percentage:
    {
        frequencyTable->setColumnCount(4);
        frequencyTable->setHorizontalHeaderItem(0,sortedData);
        frequencyTable->setHorizontalHeaderItem(1,simpleF);
        frequencyTable->setHorizontalHeaderItem(2,relativeF);
        frequencyTable->setHorizontalHeaderItem(3,percentageF);
        break;
    }
    case cumulative:
    {
        frequencyTable->setColumnCount(3);
        frequencyTable->setHorizontalHeaderItem(0,sortedData);
        frequencyTable->setHorizontalHeaderItem(1,simpleF);
        frequencyTable->setHorizontalHeaderItem(2,cumulativeF);
        break;
    }
    case cumulativeRelative:
    {
        frequencyTable->setColumnCount(4);
        frequencyTable->setHorizontalHeaderItem(0,sortedData);
        frequencyTable->setHorizontalHeaderItem(1,simpleF);
        frequencyTable->setHorizontalHeaderItem(2,cumulativeF);
        frequencyTable->setHorizontalHeaderItem(3,cumRelF);
        break;
    }
    case cumulativePercentage:
    {
        frequencyTable->setColumnCount(5);
        frequencyTable->setHorizontalHeaderItem(0,sortedData);
        frequencyTable->setHorizontalHeaderItem(1,simpleF);
        frequencyTable->setHorizontalHeaderItem(2,cumulativeF);
        frequencyTable->setHorizontalHeaderItem(3,cumRelF);
        frequencyTable->setHorizontalHeaderItem(4,cumPerF);
        break;
    }
    }

    for(int r=0; r<frequencyTable->rowCount(); r++)
        for(int c=0; c<frequencyTable->columnCount(); c++)
            frequencyTable->setItem(r,c,new QTableWidgetItem);

    img->setHidden(true);
    indications->setHidden(true);

    frequencyTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    frequencyTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    FrequencyLayout->addWidget(frequencyTable);

    if(userCalc){
        if(checkButton->isHidden())
            checkButton->setHidden(false);
    }
    else
        checkButton->setHidden(true);


}

void FrequencyView::showFrequency(FrequencyType freqType, vector<std::string> sortedData, vector<double> freq)
{
    //creo la struttura della tabella da completare
    int row = sortedData.size();
    createTable(row,freqType,false);

    //riempio la prima colonna con il vettore sortedData
    for(int i=0; i<row; i++)
    {
        QTableWidgetItem* label = new QTableWidgetItem(QString::fromStdString(sortedData[i]));
        label->setFlags(label->flags() &= ~Qt::ItemIsEditable);
        frequencyTable->setItem(i,0,label);
    }

    //riempio il resto della tabella con le frequenze
    int col= frequencyTable->columnCount();

    for(int c=1; c<col; c++)
        for (int r=0; r<row; r++){
            double toInsert = freq[(c-1)*row + r];
            QTableWidgetItem* label = new QTableWidgetItem(QString::number(toInsert));
            label->setFlags(label->flags() &= ~Qt::ItemIsEditable);
            frequencyTable->setItem(r,c,label);
        }


}

void FrequencyView::deselectFrequency()
{
    for(int i=0; i<frequencyTable->rowCount(); i++)
        for(int j=0; j<frequencyTable->columnCount(); j++)
            frequencyTable->item(i,j)->setSelected(false);
}

