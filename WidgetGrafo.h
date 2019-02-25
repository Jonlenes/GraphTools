#ifndef WIDGETGRAFO_H
#define WIDGETGRAFO_H

#include <QGraphicsView>
#include <QMouseEvent>
#include "Fila.h"
#include "Pilha.h"
#include <QAction>

class Vertice;
class Aresta;
class QLabel;
class GrafoDirecionado;

class WidgetGrafo : public QGraphicsView
{
    Q_OBJECT
public:
    WidgetGrafo(QWidget *p = 0);
    ~WidgetGrafo();
    void DeseAresta(int Origem, int Final);
    void MenorCaminho(int Origem, int Final);
    void DesenhaMenorCaminho();
    void LimpaMenorCaminho();
    void CarregaPeloTxt();
    void Salvar();
    void Abrir(QString End = "");
    void CarregaRecentes(Pilha<QAction *> *&, QWidget *);

protected:
    void mousePressEvent(QMouseEvent *eventPress);
    void keyPressEvent(QKeyEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private slots:
    void SlotScrollBar();

private:
    int timerId;
    QGraphicsScene *scene;
    Fila<Vertice*> *FilaVertice;
    Pilha<int> *Caminho;
    GrafoDirecionado *Grafo;
    bool GrafoInstanciado, Salvo;
    int NumDoVertice;

    /*Será usado apenas para permitir que
     * o usuário possa "limpar" o melhor
     * caminho, ou seja, apagar as linhas
     * vermelhas*/
    Fila<Vertice*> *VerticesMelhorCaminho;
    Fila<Aresta*> *ArestasMelhorCaminho;

};
#endif // WIDGETGRAFO_H
