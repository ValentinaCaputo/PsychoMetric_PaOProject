#include "variableview.h"

void VariableView::starter()
{
    //immagine
    img = new QLabel(this);
    QPixmap pic = QPixmap(":/resources/step1.png");
    pic = pic.scaledToHeight(80);
    img->setPixmap(pic);
    VariableLayout->addWidget(img,0,Qt::AlignHCenter);

    //testo
    indications = new QTextEdit(this);
    indications->setHtml("<p>Per iniziare a prendere confidenza con la psicometria e capire cosa è e come è fatta una variabile, "
                         "inizia con il tasto <img src="":/resources/icons/import.png"" width=""20"" height=""20""> <strong>&#34;Importa dati variabile&#34;</strong> e seleziona il file di esempio.</p>"
                         "<p>Se invece sei già esperto di PsychoMetric, non perdere altro tempo! Crea o importa i tuoi dati ed inizia "
                         "a fare pratica!</p>");

    //indications->setFont(QFont("OldEnglish", 12));
    indications->setReadOnly(true);

    VariableLayout->addWidget(indications,0,Qt::AlignJustify);
}

void VariableView::setDataTable()
{
    dataTable = new QTableWidget();
    dataTable->setContextMenuPolicy(Qt::ActionsContextMenu);

    connect(dataTable, &QTableWidget::itemChanged, [this](){
        QTableWidgetItem* itemToChange = dataTable->currentItem();
        emit changeData(itemToChange,dataTable->currentRow(),dataTable->currentColumn());
    });




    QAction* addItem= new QAction(QIcon(":/resources/icons/add.png"),"Aggiungi riga");
    QAction* deleteItem= new QAction(QIcon(":/resources/icons/remove.png"),"Elimina riga");

    connect(addItem, &QAction::triggered, [this](){
        emit insertData(dataTable->currentRow());
    });


    connect(deleteItem, &QAction::triggered, [this](){
        emit removeData(dataTable->currentRow());
    });

    dataTable->addAction(addItem);
    dataTable->addAction(deleteItem);

}

VariableView::VariableView(QWidget *parent): QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout();

    QGroupBox* variableBox = new QGroupBox();
    VariableLayout = new QVBoxLayout();

    // imposto l'heading
    QPushButton* help = new QPushButton(QIcon(":/resources/icons/help.png"),"");
    help->setCursor(QCursor(Qt::PointingHandCursor));
    help->setMaximumSize(40,40);
    help->setIconSize(QSize(25,25));
   // help->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    connect(help, SIGNAL(clicked(bool)), this, SIGNAL(openHelp_variable()));

    QLabel* title = new QLabel("Dati grezzi");

    QHBoxLayout* heading = new QHBoxLayout();
    heading->addWidget(help);
    heading->addWidget(title);

    VariableLayout->addLayout(heading);

    //imposto schermata di apertura
    starter();

    //preimposto la tabella
    setDataTable();

    variableBox->setLayout(VariableLayout);
    layout->addWidget(variableBox);
    setLayout(layout);
}

void VariableView::createTable(Variable* variable)
{
    //Prima di tutto devo controllare se c'era già una variabile
    if(img->isVisible()){
        //vuol dire che ancora non è stata definita alcuna variabile e ancora è presente la schermata iniziale
        img->setHidden(true);
        indications->setHidden(true);

        VariableLayout->removeWidget(img);
        VariableLayout->removeWidget(indications);
    }
    else{
        //significa che era già stata creata una tabella dati in precedenza e deve essere ripulita per creare la nuova
        dataTable->clear();

        delete name;
        delete misureScale;

        VariableLayout->removeWidget(name);
        VariableLayout->removeWidget(misureScale);

    }


    //imposto intestazione:
    //nome della variabile

    name = new QLabel("Nome della variabile: "+QString::fromStdString(variable->getName()));

    VariableLayout->addWidget(name,0,Qt::AlignHCenter);

    //scala di misura:
    QString scale;

    switch (variable->getScale()) {
    case nominal:
    {
        icon = QIcon(":/resources/icons/nominal.png");
        scale = QString("Nominale");
        break;
    }
    case ordinal:
    {
        icon = QIcon(":/resources/icons/ordinal.png");
        scale = QString("Ordinale");
        break;
    }
    case interval:
    {
        icon = QIcon(":/resources/icons/interval.png");
        scale = QString("A intervalli");
        break;
    }
    case ratio:
    {
        icon = QIcon(":/resources/icons/ratio.png");
        scale = QString("A rapporti");
        break;
    }
    }

    misureScale = new QLabel("Scala di misura: "+scale);
    VariableLayout->addWidget(misureScale,0,Qt::AlignHCenter);

    //Imposto la tabella con i dati:

    //numero di righe pari al numero di dati da visualizzare
    std::list<MisureScale*> allData = variable->getData();
    dataTable->setRowCount(allData.size());


    if(dynamic_cast<QualitativeVariable*>(variable))
    {
        //numero colonne in caso di variabile qualitativa
        dataTable->setColumnCount(2);

        dataTable->setHorizontalHeaderItem(0,new QTableWidgetItem("Attributo"));
        dataTable->setHorizontalHeaderItem(1,new QTableWidgetItem("Etichetta numerica"));

        //dati
        int i=0;
        for(auto it:allData){
            QTableWidgetItem* dataAtt = new QTableWidgetItem(icon,QString::fromStdString(it->getAttribute()));
            QTableWidgetItem* dataNL = new QTableWidgetItem(icon,QString::number(it->getNumberValue()));

            dataTable->setItem(i,0,dataAtt);

            QFont font=QFont("Helvetica");
            font.setItalic(true);

            dataTable->item(i,0)->setFont(font);
            dataTable->setItem(i,1,dataNL);

            i++;
        }
    }
    else
    {
        //numero colonne in caso di variabile quantitativa
        dataTable->setColumnCount(1);
        dataTable->setHorizontalHeaderItem(0,new QTableWidgetItem("Valore"));

        //dati
        int i=0;
        for(auto it:allData){
            QTableWidgetItem* dataValue = new QTableWidgetItem(icon, QString::number(it->getNumberValue()));
            dataTable->setItem(i,0,dataValue);
            i++;
        }
    }


    dataTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    dataTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    VariableLayout->addWidget(dataTable);



}



void VariableView::findedData(std::vector<unsigned int> finded)
{
    for(auto it: finded){
        for(int i = 0; i<dataTable->columnCount(); i++)
            dataTable->item(it,i)->setSelected(true);
    }
}


void VariableView::deselectData()
{
    for(int i=0; i<dataTable->rowCount(); i++)
        for(int j=0; j<dataTable->columnCount(); j++)
            dataTable->item(i,j)->setSelected(false);;
}



void VariableView::insertRow_toDataTable()
{
    int row;

    //se non ci sono righe creane una nuova
    if (dataTable->rowCount()==0){
        dataTable->setRowCount(1);
        row = 1;
    }
    else {
        //altrimenti aggiungi la riga nella posizione corrente
        row=dataTable->currentRow();
        dataTable->insertRow(row);
    }

    //imposta la riga aggiunta/inserita con l'icona e i valori di default
    for(int i = 0; i<dataTable->columnCount(); i++){
        QTableWidgetItem* insertedItem = new QTableWidgetItem(icon,"");
        dataTable->setItem(row,i,insertedItem);
    }
}



void VariableView::removeRow_toDataTable()
{
    if(dataTable->rowCount()==0)
        throw std::runtime_error("Non sono presenti righe da poter eliminare");

    dataTable->removeRow(dataTable->currentRow());
}

void VariableView::updateTable(Variable *variable)
{
    dataTable->clear();

    std::list<MisureScale*> allData = variable->getData();
    dataTable->setRowCount(allData.size());


    if(dynamic_cast<QualitativeVariable*>(variable))
    {
        //numero colonne in caso di variabile qualitativa
        dataTable->setColumnCount(2);

        dataTable->setHorizontalHeaderItem(0,new QTableWidgetItem("Attributo"));
        dataTable->setHorizontalHeaderItem(1,new QTableWidgetItem("Etichetta numerica"));

        //dati
        int i=0;
        for(auto it:allData){
            QTableWidgetItem* dataAtt = new QTableWidgetItem(icon,QString::fromStdString(it->getAttribute()));
            QTableWidgetItem* dataNL = new QTableWidgetItem(icon,QString::number(it->getNumberValue()));

            dataTable->setItem(i,0,dataAtt);

            QFont font=QFont("Helvetica");
            font.setItalic(true);

            dataTable->item(i,0)->setFont(font);
            dataTable->setItem(i,1,dataNL);

            i++;
        }
    }
    else
    {
        //numero colonne in caso di variabile quantitativa
        dataTable->setColumnCount(1);
        dataTable->setHorizontalHeaderItem(0,new QTableWidgetItem("Valore"));

        //dati
        int i=0;
        for(auto it:allData){
            QTableWidgetItem* dataValue = new QTableWidgetItem(icon, QString::number(it->getNumberValue()));
            dataTable->setItem(i,0,dataValue);
            i++;
        }
    }


    dataTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    dataTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    dataTable->show();
}



