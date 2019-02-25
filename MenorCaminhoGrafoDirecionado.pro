#-------------------------------------------------
#
# Project created by QtCreator 2014-09-26T11:12:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MenorCaminhoGrafoDirecionado
TEMPLATE = app

SOURCES += main.cpp\
        MainWindow.cpp \
        Vertice.cpp\
        Aresta.cpp\
        Node.cpp\
        WidgetGrafo.cpp\
        Pilha.cpp\
        Fila.cpp\
        GrafoDirecionado.cpp \
    Index.cpp

HEADERS  += MainWindow.h \
    Vertice.h\
    Aresta.h\
    Node.h\
    WidgetGrafo.h\
    Pilha.h\
    Fila.h\
    GrafoDirecionado.h \
    Index.h

FORMS    += MainWindow.ui
