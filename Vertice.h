#ifndef VERTICE_H
#define VERTICE_H

#include <QGraphicsItem>
#include <QList>


class Aresta;
class WidgetGrafo;

class Vertice : public QGraphicsItem
{
public:
    Vertice(WidgetGrafo *widgetGrafo, int cor = 0, int i = 0);
    void AdicionarAresta(Aresta *aresta);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QList <Aresta *> ListaAresta;
    WidgetGrafo *grafico;
    int cor;
    int i;
};

#endif // VERTICE_H
