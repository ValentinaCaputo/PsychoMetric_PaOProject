#-------------------------------------------------
#
# Project created by QtCreator 2022-08-22T09:40:32
#
#-------------------------------------------------

QT       += core
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = PsychoMetric
TEMPLATE = app


SOURCES += \
        main.cpp \
    Model/MisureScale/misurescale.cpp \
    Model/Variable/variable.cpp \
    Model/MisureScale/nominalscale.cpp \
    Model/MisureScale/ordinablescale.cpp \
    Model/MisureScale/ordinalscale.cpp \
    Model/MisureScale/quantitativescale.cpp \
    Model/MisureScale/intervalscale.cpp \
    Model/MisureScale/ratioscale.cpp \
    Model/Variable/qualitativevariable.cpp \
    Model/Variable/quantitativevariable.cpp \
    Model/Variable/nominalvariable.cpp \
    Model/Variable/ordinalvariable.cpp \
    Model/Variable/intervalvariable.cpp \
    Model/Variable/ratiovariable.cpp \
    Model/filemanagment.cpp \
    Model/frequencyanalysis.cpp \
    Model/model.cpp \
    View/mainview.cpp \
    View/variableview.cpp \
    View/ConvertWizard/inputwizard.cpp \
    View/ConvertWizard/intropage.cpp \
    View/ConvertWizard/insertpage.cpp \
    View/ConvertWizard/conclusionpage.cpp \
    View/frequencyview.cpp \
    View/chartview.cpp \
    View/piechartview.cpp \
    View/barchartview.cpp \
    View/linearchartview.cpp \
    Controller/controller.cpp

HEADERS += \
    Model/MisureScale/misurescale.h \
    Model/Variable/variable.h \
    Model/MisureScale/nominalscale.h \
    Model/MisureScale/ordinablescale.h \
    Model/MisureScale/ordinalscale.h \
    Model/MisureScale/quantitativescale.h \
    Model/MisureScale/intervalscale.h \
    Model/MisureScale/ratioscale.h \
    Model/Variable/qualitativevariable.h \
    Model/Variable/quantitativevariable.h \
    Model/Variable/nominalvariable.h \
    Model/Variable/ordinalvariable.h \
    Model/Variable/intervalvariable.h \
    Model/Variable/ratiovariable.h \
    Model/filemanagment.h \
    Model/frequencyanalysis.h \
    Model/model.h \
    View/mainview.h \
    View/variableview.h \
    View/ConvertWizard/inputwizard.h \
    View/ConvertWizard/intropage.h \
    View/ConvertWizard/insertpage.h \
    View/ConvertWizard/conclusionpage.h \
    View/frequencyview.h \
    View/chartview.h \
    View/piechartview.h \
    View/barchartview.h \
    View/linearchartview.h \
    Controller/controller.h

FORMS +=

RESOURCES += \
    resources.qrc
