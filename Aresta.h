#ifndef ARESTA_H
#define ARESTA_H

#include <QGraphicsItem>

class Vertice;

class Aresta : public QGraphicsItem
{
public:
    Aresta(Vertice *origem, Vertice *final, bool cor = 0);
    ~Aresta();
    void ajustar();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    Vertice *origem, *final;
    QPointF PtOrigem;
    QPointF PtFinal;
    qreal TamSeta;
    bool cor;
};

#endif // ARESTA_H
