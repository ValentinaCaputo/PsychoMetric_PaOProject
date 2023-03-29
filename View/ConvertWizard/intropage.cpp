#include "intropage.h"

IntroPage::IntroPage(QWidget *parent): QWizardPage(parent)
{
    setTitle("Converti la tua variabile quantitativa in una variabile Ordinale");


    QFormLayout* layout = new QFormLayout;

    QLabel* spiegazione = new QLabel("Trasformare una variabile quantitativa in una variabile qualitativa (nello specifico ordinale) significa "
                               "definire gli attributi della nuova variabile e individuare le soglie massime attraverso cui assegnare ciascun "
                               "dato della variabile quantitativa al valore equivalente della variabile qualitativa");
    spiegazione->setWordWrap(true);

    QTextEdit* esempio = new QTextEdit;
    esempio->setHtml("<p><strong>Esempio</strong>: se la variabile quantitativa da convertire fosse &ldquo;età&rdquo;, "
                     "i corrispettivi attributi che definiscono la variabile ordinale potrebbero essere: <em>adolescente</em>, <em>giovane adulto</em>, <em>adulto</em> e <em>anziano</em>.</p>"
                     "<p>Sulla base delle convenzioni adottate si definisce:</p>"
                     "<ul>"
                        "<li>adolescente: chi ha meno di 19 anni;</li>"
                        "<li>giovane adulto: chi ha tra i 19 e i 30 anni;</li>"
                        "<li>adulto: chi ha tra i 31 e i 60 anni;</li>"
                        "<li>anziano: chi ha più di 60 anni.</li>"
                     "</ul>"
                     "<p>Per cui, si definiscono le seguenti soglie massime: 18,30,60,130.</p>"
                     "<p>In questo modo, a partire dal valore della variabile si crea un corrispettivo valore della variabile ordinale. "
                     "Per esempio, se nella nostra variabile abbiamo il valore 25, questo è minore del limite 30 e quindi può essere convertito in <em>giovane adulto</em> della scala ordinale."
                     "<p>N.B. L'ultimo valore massimo non corrisponde ad un valore possibile. Questo, infatti, è pensato come limite massimo <em>accettabile</em>, "
                     "in quanto nessun uomo può raggiungere tale età. Un valore massimo basso, come poteva essere 95, poteva compromettere l'esito della procedura: "
                     "se nei dati registrati ci fosse stato un valore superiore (es.100), questo non rientrerebbe in nessun attributo definito e quindi genererebbe errore.</p>"
                     );
    esempio->setReadOnly(true);
    esempio->setMinimumSize(400,280);
    esempio->setStyleSheet("background-color: #3587A4;"
                           "color: white;"
                           "border: none;");


    QSpinBox* numAttributes = new QSpinBox();
    numAttributes->setMinimum(0);


    registerField("numAtt*",numAttributes);


    layout->addWidget(spiegazione);
    layout->addItem(new QSpacerItem(0,10));
    layout->addWidget(esempio);
    layout->addItem(new QSpacerItem(0,10));

    layout->addRow(tr("Inserisci numero massimo di attributi: "),numAttributes);

    setLayout(layout);

}

