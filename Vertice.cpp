#include "Vertice.h"

#include "Vertice.h"
#include "Aresta.h"
#include "widgetgrafo.h"
#include <QGraphicsScene>
#include <QGraphicsSceneEvent>
#include <QPainter>
#include <QStyleOption>
#include <QLabel>

Vertice::Vertice(WidgetGrafo *widgetGrafo, int cor, int i)
    :grafico(widgetGrafo)
{
    this->cor = cor;
    this->i = i;
}

void Vertice::AdicionarAresta(Aresta *aresta)
{
    ListaAresta << aresta;
}

QRectF Vertice::boundingRect() const
{
    qreal ajustar = 2;
    return QRectF( -10 - ajustar, -10 - ajustar, 3 + ajustar, 3 + ajustar);

}

void Vertice::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->setBrush(QBrush(Qt::green));

    if(cor)
        painter->setPen(QPen(Qt::red, 3));
    else
        painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 20, 20);

    if(!cor){
        painter->setPen(QPen(Qt::blue, 4));
        painter->setFont(QFont(QString("Arial"), 15));
        painter->drawText(QPoint(0, -15), QString::number(i + 1));
    }
}
