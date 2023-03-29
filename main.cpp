#include "View/mainview.h"
#include "Model/model.h"
#include "Controller/controller.h"

#include <QApplication>

#include <iostream>
using std::cout; using std::endl;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainView w;
    Controller c;
    Model m;
    w.show();

    c.setModel(&m);
    c.setView(&w);
    w.setController(&c);

    w.show();

    return a.exec();
}

