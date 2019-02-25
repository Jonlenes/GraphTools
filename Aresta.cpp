#include <math.h>
#include <QPainter>
#include "Aresta.h"
#include "Vertice.h"

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

Aresta::Aresta(Vertice *origem, Vertice *final, bool cor) : TamSeta(10)
{
    setAcceptedMouseButtons(0);
    this->origem = origem;
    this->final = final;
    this->origem->AdicionarAresta(this);
    this->final->AdicionarAresta(this);
    this->cor = cor;
    ajustar();
}

Aresta::~Aresta(){}

void Aresta::ajustar()
{
    if(!origem || !final)
        return;
    QLineF line(mapFromItem(origem, 0, 0), mapFromItem(final, 0, 0));
    qreal TamLinha = line.length();

    prepareGeometryChange();

    if(TamLinha > qreal(20.)){
        QPointF arestaDeslo((line.dx() * 10) / TamLinha, (line.dy() * 10) / TamLinha);
        PtOrigem = line.p1() + arestaDeslo;
        PtFinal = line.p2() - arestaDeslo;
    }else{
        PtOrigem = PtFinal = line.p1();
    }
}

QRectF Aresta::boundingRect() const
{
    if(!origem || !final)
        return QRectF();
    qreal larguraCaneta = 1;
    qreal extra = (larguraCaneta + TamSeta) / 2.0;

    return QRectF(PtOrigem, QSizeF(PtFinal.x() - PtOrigem.x(), PtFinal.y() - PtOrigem.y()))
            .normalized()
            .adjusted(-extra, -extra, extra, extra);
}

void Aresta::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!origem || !final)
        return;
    QLineF line(PtOrigem, PtFinal);
    if(qFuzzyCompare(line.length(), qreal(0.)))
        return;

    if(cor){
        painter->setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->setBrush(Qt::red);
    }
    else{
        painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->setBrush(Qt::black);
    }

    painter->drawLine(line);

    double angulo = ::acos(line.dx() / line.length());
    if(line.dy() >= 0)
        angulo = TwoPi - angulo;

    QPointF FinalSetaP1 = PtFinal + QPointF(sin(angulo - Pi / 3) * TamSeta,
                                              cos(angulo - Pi / 3) * TamSeta);
    QPointF FinalSetaP2 = PtFinal + QPointF(sin(angulo - Pi + Pi / 3) * TamSeta,
                                            cos(angulo - Pi + Pi / 3) * TamSeta);

    painter->drawPolygon(QPolygonF() << line.p2() << FinalSetaP1 << FinalSetaP2);
}

