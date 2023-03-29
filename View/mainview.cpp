#include "mainview.h"

#include "Controller/controller.h"

void mainView::addMenu(QVBoxLayout *mainLayout)
{
    //imposto la barra del menù
    QMenuBar* menuBar = new QMenuBar(this);

    file = new QMenu("File",menuBar);
    data = new QMenu("Dati",menuBar);
    QMenu* freq = new QMenu("Frequenze",menuBar);
    chart = new QMenu("Grafici",menuBar);
    help = new QMenu("Guida",menuBar);

    menuBar->addMenu(file);
    menuBar->addMenu(data);
    menuBar->addMenu(freq);
    menuBar->addMenu(chart);
    menuBar->addMenu(help);

    //definisco il menù per "File"
    file->addAction(new QAction("Crea nuova variabile"));
    file->addAction(new QAction("Importa dati variabile"));
    file->addAction(new QAction("Salva dati variabile"));

    file->addSeparator();

    file->addAction("Esci");
    connect(file->actions()[4],SIGNAL(triggered(bool)),this,SLOT(close()));

    //definisco il menù per "Dati"
    data->addAction(new QAction("Cerca attributo"));
    data->addAction(new QAction("Sostituisci attributo"));
    data->addAction(new QAction("Reset dei dati"));
    data->addAction(new QAction("Converti in variabile ordinale"));

    //definisco il menù per "Frequenze"
    freqCalculated = new QMenu("Calcola...", freq);
    freqShowed = new QMenu("Mostra...", freq);
    freq->addMenu(freqCalculated);
    freq->addMenu(freqShowed);

        //sottomenù per "Calcola..."
    freqCalculated->addAction(new QAction("frequenza semplice"));
    freqCalculated->addAction(new QAction("frequenza relativa"));
    freqCalculated->addAction(new QAction("frequenza percentuale"));
    freqCalculated->addSeparator();
    freqCalculated->addAction(new QAction("frequenza cumulata"));
    freqCalculated->addAction(new QAction("frequenza cumulata relativa"));
    freqCalculated->addAction(new QAction("frequenza percentuale cumulata"));

        //sottomenù per "Mostra..."
    freqShowed->addAction(new QAction("frequenza semplice"));
    freqShowed->addAction(new QAction("frequenza relativa"));
    freqShowed->addAction(new QAction("frequenza percentuale"));
    freqShowed->addSeparator();
    freqShowed->addAction(new QAction("frequenza cumulata"));
    freqShowed->addAction(new QAction("frequenza cumulata relativa"));
    freqShowed->addAction(new QAction("frequenza percentuale cumulata"));

    //definisco il menù per "Grafici"
    chart->addAction(new QAction("grafico a torta"));
    chart->addAction(new QAction("grafico a barre"));
    chart->addAction(new QAction("poligono di frequenza"));

    //definisco il menù per "Guida"
    help->addAction(new QAction("PsychoMetric"));
    help->addAction(new QAction("Perchè proprio a noi?!"));
    help->addAction(new QAction("La variabile e le scale di misura"));
    help->addAction(new QAction("Distribuzione di frequenza"));
    help->addAction(new QAction("Rappresentazione grafica"));


    setMinimumSize(680,540);

    mainLayout->addWidget(menuBar);
}

void mainView::addIconMenu(QVBoxLayout *mainLayout)
{
    menuIcon = new QToolBar(this);

    menuIcon->addAction(QIcon(":/resources/icons/new.png"),"Crea nuova variabile");         // 0
    menuIcon->addAction(QIcon(":/resources/icons/import.png"),"Importa dati variabile");    // 1
    menuIcon->addAction(QIcon(":/resources/icons/save.png"),"Salva");                       // 2

    menuIcon->addSeparator();

    menuIcon->addAction(QIcon(":/resources/icons/search.png"),"Cerca");                     // 4
    menuIcon->addAction(QIcon(":/resources/icons/replace.png"),"Sostituisci");              // 5
    menuIcon->addAction(QIcon(":/resources/icons/reset.png"),"Reset dati");                 // 6
    menuIcon->addAction(QIcon(":/resources/icons/convert.png"),"Converti variabile");       // 7

    menuIcon->addSeparator();

    menuIcon->addAction(QIcon(":/resources/icons/freqCalc.png"),"Calcola frequenza");       // 9
    menuIcon->addAction(QIcon(":/resources/icons/freqShow.png"),"Mostra frequenza");        // 10


    menuIcon->addSeparator();

    menuIcon->addAction(QIcon(":/resources/icons/pie.png"),"Grafico a torta");              // 12
    menuIcon->addAction(QIcon(":/resources/icons/bar.png"),"Grafico a barre");              // 13
    menuIcon->addAction(QIcon(":/resources/icons/linear.png"),"Poligono di frequenza");     // 14

    mainLayout->addWidget(menuIcon);
}

void mainView::addFreqSection(QHBoxLayout *sectionLayout)
{
    freqTable = new FrequencyView(this);
    sectionLayout->addWidget(freqTable);
}

void mainView::addDataSection(QHBoxLayout *sectionLayout)
{
    dataTable = new VariableView(this);
    sectionLayout->addWidget(dataTable);
}

void mainView::setPsychoMetricStyle()
{
    QFile file(":/resources/style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    setStyleSheet(styleSheet);
}

mainView::mainView(QWidget *parent) : QWidget(parent)
{
    setWindowIcon(QIcon(":/resources/icons/logo.jpg"));

    QVBoxLayout* mainLayout = new QVBoxLayout;
    addMenu(mainLayout);
    addIconMenu(mainLayout);

    QHBoxLayout* sectionLayout = new QHBoxLayout;
    addDataSection(sectionLayout);
    addFreqSection(sectionLayout);


    mainLayout->addLayout(sectionLayout);

    setPsychoMetricStyle();

    setLayout(mainLayout);

}

void mainView::setController(Controller *c)
{
    controller = c;


    //FILE
    connect(this, SIGNAL(createVariable(QLineEdit*,QComboBox*,QLineEdit*)),controller, SLOT(newVariable(QLineEdit*,QComboBox*,QLineEdit*)));

    connect(file->actions()[0], SIGNAL(triggered(bool)),controller, SLOT(create()));
    connect(file->actions()[1], SIGNAL(triggered(bool)),controller, SLOT(open()));
    connect(file->actions()[2], SIGNAL(triggered(bool)),controller, SLOT(save()));

    connect(menuIcon->actions()[0], SIGNAL(triggered(bool)),controller, SLOT(create()));
    connect(menuIcon->actions()[1], SIGNAL(triggered(bool)),controller, SLOT(open()));
    connect(menuIcon->actions()[2], SIGNAL(triggered(bool)),controller, SLOT(save()));

    connect(dataTable, SIGNAL(changeData(QTableWidgetItem*,int,int)),controller,SLOT(updateVariable(QTableWidgetItem*,int,int)));

    //DATA
    connect(data->actions()[0], SIGNAL(triggered(bool)),controller, SLOT(find()));
    connect(data->actions()[1], SIGNAL(triggered(bool)),controller, SLOT(replace()));
    connect(data->actions()[2], SIGNAL(triggered(bool)),controller, SLOT(reset()));
    connect(data->actions()[3], SIGNAL(triggered(bool)),controller, SLOT(convertSignal()));

    connect(menuIcon->actions()[4], SIGNAL(triggered(bool)),controller, SLOT(find()));
    connect(menuIcon->actions()[5], SIGNAL(triggered(bool)),controller, SLOT(replace()));
    connect(menuIcon->actions()[6], SIGNAL(triggered(bool)),controller, SLOT(reset()));
    connect(menuIcon->actions()[7], SIGNAL(triggered(bool)),controller, SLOT(convertSignal()));

    connect(this, SIGNAL(replaceWords(QLineEdit*,QLineEdit*)),controller, SLOT(doReplaceWords(QLineEdit*,QLineEdit*)));
    connect(dataTable, SIGNAL(insertData(int)), controller, SLOT(rowToInsert(int)));
    connect(dataTable, SIGNAL(removeData(int)), controller, SLOT(rowToRemove(int)));
    connect(this, SIGNAL(vectorsForConversion(std::vector<std::string>,std::vector<int>)),controller, SLOT(convert(std::vector<std::string>,std::vector<int>)));


    //FREQUENCY
    connect(freqCalculated->actions()[0], &QAction::triggered, [this](){emit freqType_calculate(simple);});
    connect(freqCalculated->actions()[1], &QAction::triggered, [this](){emit freqType_calculate(relative);});
    connect(freqCalculated->actions()[2], &QAction::triggered, [this](){emit freqType_calculate(percentage);});
    connect(freqCalculated->actions()[4], &QAction::triggered, [this](){emit freqType_calculate(cumulative);});
    connect(freqCalculated->actions()[5], &QAction::triggered, [this](){emit freqType_calculate(cumulativeRelative);});
    connect(freqCalculated->actions()[6], &QAction::triggered, [this](){emit freqType_calculate(cumulativePercentage);});

    connect(this, SIGNAL(freqType_calculate(FrequencyType)), controller, SLOT(calculateFrequency(FrequencyType)));
    connect(menuIcon->actions()[9], SIGNAL(triggered(bool)), controller, SLOT(calculateFrequency_button()));

    connect(freqShowed->actions()[0], &QAction::triggered, [this](){emit freqType_toShow(simple);});
    connect(freqShowed->actions()[1], &QAction::triggered, [this](){emit freqType_toShow(relative);});
    connect(freqShowed->actions()[2], &QAction::triggered, [this](){emit freqType_toShow(percentage);});
    connect(freqShowed->actions()[4], &QAction::triggered, [this](){emit freqType_toShow(cumulative);});
    connect(freqShowed->actions()[5], &QAction::triggered, [this](){emit freqType_toShow(cumulativeRelative);});
    connect(freqShowed->actions()[6], &QAction::triggered, [this](){emit freqType_toShow(cumulativePercentage);});

    connect(this, SIGNAL(freqType_toShow(FrequencyType)), controller, SLOT(showFrequency(FrequencyType)));
    connect(menuIcon->actions()[10], SIGNAL(triggered(bool)), controller, SLOT(showFrequency_button()));

    connect(freqTable, SIGNAL(check_frequencies(QString,std::vector<std::string>,std::vector<double>)),controller,SLOT(doCheckFrequencies(QString,std::vector<std::string>,std::vector<double>)));
    connect(freqTable, SIGNAL(errorSignal(QString)),this, SLOT(showFrequencyErrorSignal(QString)));

    //CHARTS
    connect(chart->actions()[0], &QAction::triggered, [this](){emit openChart(0);});
    connect(chart->actions()[1], &QAction::triggered, [this](){emit openChart(1);});
    connect(chart->actions()[2], &QAction::triggered, [this](){emit openChart(2);});

    connect(menuIcon->actions()[12], &QAction::triggered, [this](){emit openChart(0);});
    connect(menuIcon->actions()[13], &QAction::triggered, [this](){emit openChart(1);});
    connect(menuIcon->actions()[14], &QAction::triggered, [this](){emit openChart(2);});

    connect(this, SIGNAL(openChart(uint)),controller, SLOT(doOpenChart(uint)));

    //GUIDA
    connect(help->actions()[0], &QAction::triggered, [this](){openGuidePage(QString("PsychoMetric"), QUrl("home.html"));});
    connect(help->actions()[1], &QAction::triggered, [this](){openGuidePage(QString("Perché proprio a noi?!"), QUrl("why.html"));});
    connect(help->actions()[2], &QAction::triggered, [this](){openGuidePage(QString("La variabile e le scale di misura"), QUrl("variable.html"));});
    connect(help->actions()[3], &QAction::triggered, [this](){openGuidePage(QString("La distribuzione di frequenza"), QUrl("frequency.html"));});
    connect(help->actions()[4], &QAction::triggered, [this](){openGuidePage(QString("La rappresentazione grafica"), QUrl("chart.html"));});

    connect(dataTable, &VariableView::openHelp_variable, [this](){openGuidePage(QString("La variabile e le scale di misura"), QUrl("variable.html"));});
    connect(freqTable, &FrequencyView::openHelp_frequency, [this](){openGuidePage(QString("La distribuzione di frequenza"), QUrl("frequency.html"));});
}

void mainView::deselectAll()
{
    dataTable->deselectData();
    freqTable->deselectFrequency();
}


void mainView::showCreateVariableDialog()
{
    QDialog* defineVariable = new QDialog(this);

    defineVariable->setWindowTitle("Crea nuova variabile");
    defineVariable->setWindowIcon(QIcon(":/resources/icons/new.png"));
    defineVariable->setFixedSize(400,150);

    QVBoxLayout* layoutDialog = new QVBoxLayout;
    QFormLayout* layoutInsert = new QFormLayout;

    QLineEdit* name = new QLineEdit(defineVariable);
    name->setPlaceholderText("Inserisci nome della variabile");
    name->setMaxLength(20);
    QRegExpValidator* nameValidator = new QRegExpValidator(QRegExp( "^[a-zA-Zàèòùì]+$"));
    name->setValidator(nameValidator);
    name->setToolTip("Il nome della variabile può essere indicata con una sola parola composta unicamente da lettere");


    QComboBox* scale = new QComboBox (defineVariable);
    scale->addItem(QIcon(":/resources/icons/nominal.png"), "scala nominale");
    scale->addItem(QIcon(":/resources/icons/ordinal.png"), "scala ordinale");
    scale->addItem(QIcon(":/resources/icons/interval.png"), "scala a intervalli");
    scale->addItem(QIcon(":/resources/icons/ratio.png"), "scala a rapporti");


    QLineEdit* tot = new QLineEdit(defineVariable);
    tot->setPlaceholderText("max 3 cifre");
    tot->setMaxLength(3);
    tot->setValidator(new QIntValidator());

    layoutInsert->addRow(tr("&Nome della Variabile: "),name);
    layoutInsert->addRow(tr("&Scala di misura"),scale);
    layoutInsert->addRow(tr("&Totale dati"),tot);

    QPushButton* create = new QPushButton("Crea Variabile");
    //connetto il pulsante Crea Variabile
    connect(create, &QPushButton::clicked,
            [this, name,scale,tot]() {
        if(!name->isModified() || !tot->isModified())
            showErrorMessage("Inserire tutti i valori per poter proseguire!");
        else
            emit createVariable(name,scale,tot);
    });
    connect(create,SIGNAL(clicked(bool)),defineVariable,SLOT(accept()));

    QHBoxLayout* layoutButtons = new QHBoxLayout;
    layoutButtons->addWidget(create);

    layoutDialog->addLayout(layoutInsert);
    layoutDialog->addLayout(layoutButtons);


    defineVariable->setLayout(layoutDialog);

    defineVariable->exec();
}

QString mainView::showOpenFileDialog()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Apri file"),":/resources/esempi_PsychoMetric",tr("XML files(*.xml)"));
    if (fileName == "")
        throw std::runtime_error("Nessun file scelto: operazione annullata");
    return fileName;
}

void mainView::showVariableTable(Variable *variable)
{
    dataTable->createTable(variable);
    if(!freqTable->isEmpty()){
        freqTable->reset();
    }
}

void mainView::updateVariableTable(Variable *variable)
{
    dataTable->updateTable(variable);
    if(!freqTable->isEmpty()){
        int reply = showWarningMessage("Hai modificato i dati della variabile","Si desidera aggiornare anche i dati della frequenza?");
        if (reply==QMessageBox::Ok){
            controller->updateFrequencyTable();
        }
        else{
            freqTable->reset();

        }
    }
}



QString mainView::showSaveVariableDialog()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Salva file"),":/resources/esempi_PsychoMetric",tr("XML files(*.xml)"));
    if (fileName == "")
        throw std::runtime_error("Nessun file scelto: operazione annullata");
    return fileName;
}


QString mainView::searchAttributeDialog()
{
    bool ok;
    QString toSearch = QInputDialog::getText(this, tr("Cerca dato"),
                                             tr("Attributo: "), QLineEdit::Normal, "",
                                             &ok);


    if (ok && !toSearch.isEmpty())
        return toSearch;
    else
        throw std::runtime_error("Nessun valore inserito");
}

void mainView::replaceDataDialog()
{
    QDialog* dialog = new QDialog(this);

    dialog->setWindowTitle("Sostituisci dati");
    dialog->setWindowIcon(QIcon(":/resources/icons/replace.png"));
    dialog->setFixedSize(250,120);

    QVBoxLayout* dialogLayout = new QVBoxLayout;
    QFormLayout* formLayout = new QFormLayout;

    QLineEdit* prevItem = new QLineEdit(dialog);
    prevItem->setPlaceholderText("attributo");
    prevItem->setWhatsThis("indica l'attributo della variabile che si intende sostituire");

    QLineEdit* nextItem = new QLineEdit(dialog);
    nextItem->setPlaceholderText("attributo");
    nextItem->setWhatsThis("indica il nuovo attributo che andrà a sostituire il precedente");


    formLayout->addRow(tr("Trova:"),prevItem);
    formLayout->addRow(tr("Sostituisci con:"),nextItem);


    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::accepted, [this, prevItem, nextItem](){
        if(prevItem->isModified() && nextItem->isModified())
            emit replaceWords(prevItem,nextItem);
        else
            throw std::runtime_error("Impossibile procedere: non sono stati inseriti tutti i valori richiesti");
    });
    connect(buttonBox, &QDialogButtonBox::accepted, dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, dialog, &QDialog::reject);


    dialogLayout->addLayout(formLayout);
    dialogLayout->addSpacing(15);
    dialogLayout->addWidget(buttonBox);


    dialog->setLayout(dialogLayout);
    dialog->exec();
}

void mainView::convertVariable()
{
    int reply = showWarningMessage("La conversione di una variabile comporta la perdita dei dati della variabile quantitativa che si vuole convertire.","Si vuole comunque proseguire con la conversione?");
    if(reply == QMessageBox::Ok){
        InputWizard* input = new InputWizard(this);
        connect(input,SIGNAL(createOrdinalVariable(std::vector<std::string>,std::vector<int>)), this,SIGNAL(vectorsForConversion(std::vector<std::string>,std::vector<int>)));
        input->exec();
    }

}


void mainView::insertRow()
{
    dataTable->insertRow_toDataTable();

}

void mainView::removeRow()
{
    dataTable->removeRow_toDataTable();

}



QString mainView::showFreqDialog()
{
    bool ok;
    QList<QString> options;
    options.append("semplice");
    options.append("relativa");
    options.append("percentuale");
    options.append("cumulata");
    options.append("cumulata relativa");
    options.append("percentuale cumulata");

    QStringList list = QStringList(options);

    QString freq = QInputDialog::getItem(this, tr("Seleziona il tipo di frequenza"),
                                             tr("Frequenza "), list, 0,false, &ok);


    if (ok && !freq.isEmpty()){
        return freq;
    }

    throw std::runtime_error("Impossibile proseguire: Nessuna frequenza selezionata");
}

void mainView::calcFreq(int row, FrequencyType freqType)
{
    freqTable->createTable(row,freqType,true);
}

void mainView::showFreq(FrequencyType freqType, vector<std::string> sortedData, vector<double> freq)
{
    freqTable->showFrequency(freqType,sortedData,freq);
}

void mainView::showCheckMessage(bool goodJob)
{
    QPixmap icon;
    QString title;
    QString msg;

    if(goodJob){
        icon = QPixmap(":/resources/icons/ok.png");
        title = QString("Good job!");
        msg = QString("Tutti i valori inseriti sono corretti, per cui: Ottimo lavoro, continua così!");
    }
    else{
        icon = QPixmap(":/resources/icons/wrong.png");
        title = QString("Qualcosa non va...");
        msg = QString("Uff, deve esserci stato qualche errore, non ti arrendere può capitare! "
                     "Prova a ricontrollare i dati della variabile o verifica di aver svolto correttamente i calcoli. "
                     "Se hai dubbi sul procedimento, prova a consultare la guida!");
    }



    QMessageBox* showExitus = new QMessageBox(QMessageBox::NoIcon,title,msg);

    showExitus->setIconPixmap(icon.scaledToHeight(30));
    showExitus->exec();
}

void mainView::showChartDialog(ChartView* chart)
{
    QChart* c = chart->createChart();
    chart->showChartDialog(c);
}



int mainView::showWarningMessage(const QString& text, const QString& infoText)
{
    QMessageBox msgBox;

    msgBox.setMinimumSize(740,480);

    msgBox.setWindowIcon(QIcon(":/resources/icons/warning.png"));
    msgBox.setWindowTitle("Attenzione!");

    msgBox.setText(text);
    msgBox.setInformativeText(infoText);

    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    return msgBox.exec();
}

void mainView::showErrorMessage(const QString &msg)
{
    QMessageBox* error = new QMessageBox(this);
    error->setText(msg);
    error->setIcon(QMessageBox::Critical);
    error->show();
}

void mainView::showFrequencyErrorSignal(QString errorMessage)
{
    showErrorMessage(errorMessage);
}



void mainView::openGuidePage(QString title, QUrl url)
{
    QDialog* dialog = new QDialog();

    dialog->setWindowTitle(title);
    dialog->setWindowIcon(QIcon(":/resources/icons/help.png"));
    dialog->setWindowFlags(Qt::Window);

    QHBoxLayout* layout = new QHBoxLayout(dialog);

    QTextBrowser* text = new QTextBrowser();

    QString url_path(":/resources/guide/");
    QStringList paths;
    paths.append(url_path);

    text->setSearchPaths(paths);
    text->setSource(QUrl(url));
    text->setOpenExternalLinks(true);
    text->setStyleSheet("background-color: #FAFAFF;");

    layout->addWidget(text);


    dialog->setMinimumSize(700,480);
    dialog->setStyleSheet("background-color: #3587A4;");

    dialog->show();
}

void mainView::findData(std::vector<unsigned int> finded)
{
    dataTable->findedData(finded);
}
