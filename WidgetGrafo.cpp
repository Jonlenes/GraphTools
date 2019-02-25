#include "widgetgrafo.h"
#include "Aresta.h"
#include "Vertice.h"
#include "GrafoDirecionado.h"
#include <math.h>
#include <QLabel>
#include <QInputDialog>
#include <QMessageBox>
#include <fstream>
#include <QFileDialog>
#include "Index.h"
#include <QScrollBar>
using namespace std;

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

WidgetGrafo::WidgetGrafo(QWidget *p)
    : QGraphicsView(p), timerId(0)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    setScene(scene);
    setCacheMode(CacheBackground);
    FilaVertice = new Fila<Vertice*>;
    GrafoInstanciado = 0;
    Salvo = 0;
    NumDoVertice = 0;
    this->scene = scene;
    Caminho = NULL;
    VerticesMelhorCaminho = NULL;
    ArestasMelhorCaminho = NULL;

    connect(this->verticalScrollBar(), SIGNAL(actionTriggered(int)), this, SLOT(SlotScrollBar()));
    connect(this->horizontalScrollBar(), SIGNAL(actionTriggered(int)), this, SLOT(SlotScrollBar()));
}

WidgetGrafo::~WidgetGrafo()
{
    if(GrafoInstanciado && !Salvo)
        if(QMessageBox::question(this, "Aviso", "Salvar? ",
                                 QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
            Salvar();

    delete FilaVertice;
    if(GrafoInstanciado) delete Grafo;
    if(VerticesMelhorCaminho) delete VerticesMelhorCaminho;
    if(ArestasMelhorCaminho) delete ArestasMelhorCaminho;
}

void WidgetGrafo::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *)
{
    this->scene->update();
}

void WidgetGrafo::SlotScrollBar()
{
    this->scene->update();
}

void WidgetGrafo::mousePressEvent(QMouseEvent *eventPress)
{
    if(!GrafoInstanciado){
        Vertice *no = new Vertice(this, 0, NumDoVertice);
        this->scene->addItem(no);
        no->setPos(qreal(eventPress->windowPos().x()), qreal(eventPress->windowPos().y()));
        FilaVertice->Add(no);
        NumDoVertice++;
        this->scene->update();
    }else
        QMessageBox::information(this, "Aviso", "Todos os vertices devem ser colocados antes das arestas.");
}

void WidgetGrafo::DeseAresta(int Origem, int Final)
{
    Vertice *Ori = FilaVertice->RetornaElemento(Origem);
    Vertice *Fin = FilaVertice->RetornaElemento(Final);
    scene->addItem(new Aresta(Ori, Fin));
    this->scene->update();
}

void WidgetGrafo::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Space:
        int Origem = QInputDialog::getInt(this, "Aresta - Origem",
                                          "Vertice de origem da aresta:");

        int Final = QInputDialog::getInt(this, "Aresta - Destino",
                                         "Vertice de destino da aresta:");

        if(!GrafoInstanciado){
            int qtdeVertices = FilaVertice->Size();
            Grafo = new GrafoDirecionado(qtdeVertices);
            GrafoInstanciado = 1;
        }
        if(Grafo->AdcionarAresta(Origem - 1, Final - 1)){
            this->DeseAresta(Origem - 1, Final - 1);
            Salvo = false;
        }else
            QMessageBox::information(this, "Aviso", "Vertice desejada não existe.");
    }
}

void WidgetGrafo::MenorCaminho(int Origem, int Final)
{
    try{
        if(GrafoInstanciado){
            Grafo->SetObjetivo(Origem - 1, Final - 1);
            if(Grafo->BuscarMenorCaminho())
            {
                Caminho = Grafo->GetCaminho();
                DesenhaMenorCaminho();
            }else
                throw QString("Não há caminho entre os vertices.");
        }
        else
            throw QString("Não existe aresta.");
    }catch(QString e){
        QMessageBox::information(this, "Aviso", e);
    }
}

void WidgetGrafo::DesenhaMenorCaminho()
{
    LimpaMenorCaminho();
    VerticesMelhorCaminho = new Fila<Vertice*>;
    ArestasMelhorCaminho = new Fila<Aresta*>;

    int vertice;
    Vertice *vert, *vertAux;
    Fila<Vertice*> *f = new Fila<Vertice*>;
    Aresta *AreAux;

    while(!Caminho->Empty()){
        Caminho->Desempilhar(vertice);
        vert = FilaVertice->RetornaElemento(vertice);
        vertAux = new Vertice(this, 1);
        vertAux->setPos(vert->pos());

        f->Add(vertAux);
        VerticesMelhorCaminho->Add(vertAux);

        this->scene->addItem(vertAux);
    }

    Vertice *OriA, *desA;
    while(!f->Empty()){
        f->Remove(OriA);
        if(!f->Empty()){
            desA = f->RetornaElemento(0);
            AreAux = new Aresta(OriA, desA, 1);
            ArestasMelhorCaminho->Add(AreAux);
            this->scene->addItem(AreAux);
        }
    }
    delete f;
}

void WidgetGrafo::LimpaMenorCaminho()
{
    if(VerticesMelhorCaminho && ArestasMelhorCaminho){
        Vertice *Vert;
        Aresta *Arest;

        while(!VerticesMelhorCaminho->Empty()){
            VerticesMelhorCaminho->Remove(Vert);
            this->scene->removeItem(Vert);
        }
        while(!ArestasMelhorCaminho->Empty()){
            ArestasMelhorCaminho->Remove(Arest);
            this->scene->removeItem(Arest);
        }
        delete VerticesMelhorCaminho;
        delete ArestasMelhorCaminho;
        VerticesMelhorCaminho = NULL;
        ArestasMelhorCaminho = NULL;
        this->scene->update();
    }
}

void WidgetGrafo::CarregaPeloTxt()
{
    string Diret = QFileDialog::getOpenFileName(this, "Selecione o .txt do grafo.", "arquivo_grafo.txt", "Arquivo de texto(*.txt)").toStdString();

    char* aux = new char[Diret.size() + 1];
    int TamStr = Diret.size();;
    for(int i = 0; i < TamStr; i++)
        aux[i] = Diret[i];
    aux[Diret.size()] = '\0';

    ifstream *entrada = new ifstream;
    int QtdeVertice, QtdeArestas, AreOrigem, AreDestino;

    entrada->open(aux);
    if(entrada->is_open()){
        *entrada >> QtdeVertice;
        *entrada >> QtdeArestas;

        this->scene->clear();

        if(GrafoInstanciado) delete Grafo;
        Grafo = new GrafoDirecionado(QtdeVertice);
        GrafoInstanciado = 1;

        QPoint *CentroCirculo = new QPoint(this->width()/2.0, this->height()/2.0);
        double Raio = 5 * (this->height()/12.0);

        if(QtdeVertice > 20){
            /*Com esse raio fixo (5/6 da metade da tela) a visualização só fica legal
             * ate uns 20 vertices, então se essa qtde ultrapassar
             * esse valor, é conveniente que o raio também aumente.
             * E para fazer esse calculo, considero que o comprimento
             * do arco entre cada vertice quando temos 20 vertices
             * é ideal (visualização com "clareza"), então vou garantir
             * que o comprimento desse arco seja fixo (for > 20), aumentar assim o Raio.
             * O comprimento desse arco pode ser calculado por:
             *
             * CompriArco = (AnguloCom20Vertices/2PI) * (2*PI*Raio)
             * AnguloCom20Vertices = 2PI / 20 = PI/10
             * CompriArco = ((PI/10) / 2PI) * (2*PI*Raio)
             * CompriArco = (1/20) * (2*PI*Raio)
             * CompriArco = (2*PI*Raio) / 20
             * CompriArco = (PI*Raio) / 10
             *
             * Isolando o Raio em [CompriArco = (AnguloCom20Vertices/2PI) * (2*PI*Raio)],
             * temos:
             *
             * 2*PI*RaioNovo = CompriAcrco/(AnguloCorrespondente/2PI)
             * 2*PI*RaioNovo = ((2*PI) * CompriAcrco)/(AnguloCorrespondente)
             * RaioNovo = (CompriAcrco)/(AnguloCorrespondente)
             * AnguloCorrespondente = (2*PI) / QtdeVertice
             * RaioNovo = ((PI*Raio) / 10)/((2*PI) / QtdeVertice)
             * RaioNovo = ((PI*Raio) / 10)*(QtdeVertice /(2*PI))
             * RaioNovo = ((Raio) / 10)*(QtdeVertice /(2))
             * RaioNovo = (Raio * QtdeVertice / 20)
             *
             * Portanto, encontrei que o RaioNovo = (Raio * QtdeVertice / 20)*/
            Raio = (Raio * QtdeVertice) / 20.0;
        }

        for(int i = 0; i < QtdeVertice; i++){
            Vertice *no = new Vertice(this, 0, i);
            this->scene->addItem(no);
            no->setPos(qreal(CentroCirculo->x() + Raio * cos(i * (TwoPi/QtdeVertice))), qreal(CentroCirculo->y() - Raio * sin(i * (TwoPi/QtdeVertice))));
            FilaVertice->Add(no);
            this->scene->update();
        }

        for(int i = 0; i < QtdeArestas; i++){
            *entrada >> AreOrigem;
            *entrada >> AreDestino;

            if(Grafo->AdcionarAresta(AreOrigem, AreDestino))
                this->DeseAresta(AreOrigem, AreDestino);
            else
                QMessageBox::information(this, "Aviso", "Vertice (" +  QString::number(AreOrigem) + ", " +  QString::number(AreDestino) + ") do .txt não existe.");
        }
    }else{
        QString s = "Endereço do arquivo inválido.\nObs.: Certifique-se";
        s = s + " de que o endereço do caminho não tem caracter especial";
        s = s + ", isso pode fazer com que o arquivo não seja carregado.";

        QMessageBox::information(this, "Aviso", s);
    }
    entrada->close();
    delete entrada;
}

void WidgetGrafo::Salvar()
{
    if(!GrafoInstanciado)
        QMessageBox::information(this, "Aviso", "Arquivo limpo. Não há o que salvar");
    else{
        QString Dir = QFileDialog::getSaveFileName(this, "Salvar como", "", "Arquivo de Grafo(*.Grafo)");

        if(Dir != ""){
            Dir = Dir + ".Grafo";
            string Diret = Dir.toStdString();
            char* aux = new char[Diret.size() + 1];
            int TamStr = Diret.size();;
            for(int i = 0; i < TamStr; i++)
                aux[i] = Diret[i];
            aux[Diret.size()] = '\0';


            fstream *Salvar = new fstream;
            Salvar->open(aux, ios::out | ios::binary);
            if(Salvar->is_open()){

                int QtdeVertice = Grafo->GetQtdeVertice(), QtdeArestas;
                Fila<Index*> *Arestas = Grafo->GetArestas(QtdeArestas);
                Index *aux;

                *Salvar << QtdeVertice << endl;
                *Salvar << QtdeArestas << endl;

                for(int i = 0; i < QtdeVertice; i++){
                    *Salvar << (double)FilaVertice->RetornaElemento(i)->pos().x() << endl;
                    *Salvar << (double)FilaVertice->RetornaElemento(i)->pos().y() << endl;
                }

                while(!Arestas->Empty()){
                    Arestas->Remove(aux);
                    *Salvar << aux->i << endl;
                    *Salvar << aux->j << endl;
                }
                delete Arestas;
                Salvar->close();
                delete Salvar;

                fstream Rescentes;
                Rescentes.open("recentes.Rec", ios::out | ios::app);
                Rescentes << Dir.toStdString() << endl;
                Salvo = true;
            }else
                QMessageBox::information(this, "Aviso", "Erro de diretório. Arquivo não salvo.");
        }
    }
}

void WidgetGrafo::Abrir(QString End)
{
    string Diret;
    if(End == "")
        Diret = QFileDialog::getOpenFileName(this, "Abrir", "", "Arquivo de Grafo(*.Grafo)").toStdString();
    else
        Diret = End.toStdString();

    char* aux = new char[Diret.size() + 1];
    int TamStr = Diret.size();;
    for(int i = 0; i < TamStr; i++)
        aux[i] = Diret[i];
    aux[Diret.size()] = '\0';

    fstream *entrada = new fstream(aux);

    if(entrada->is_open()){

        int QtdeVertice, QtdeArestas, AreOrigem, AreFinal;

        *entrada >> QtdeVertice;
        *entrada >> QtdeArestas;

        this->scene->clear();
        if(GrafoInstanciado) delete Grafo;
        Grafo = new GrafoDirecionado(QtdeVertice);
        GrafoInstanciado = 1;
        Salvo = 1;

        qreal x, y;
        for(int i = 0; i < QtdeVertice; i++){
            *entrada >> x;
            *entrada >> y;

            Vertice *no = new Vertice(this, 0, i);
            this->scene->addItem(no);
            no->setPos(x, y);
            FilaVertice->Add(no);
            this->scene->update();
        }

        for(int i = 0; i < QtdeArestas; i++){
            *entrada >> AreOrigem;
            *entrada >> AreFinal;

            Grafo->AdcionarAresta(AreOrigem, AreFinal);
            this->DeseAresta(AreOrigem, AreFinal);
        }
    }else if(End != "")
        QMessageBox::information(this, "Aviso", "Arquivo não encontrado. É possivel que tenha sido removido.");
    entrada->close();
    delete entrada;
}

void WidgetGrafo::CarregaRecentes(Pilha<QAction*>* &f, QWidget *MW)
{
    fstream Recentes;
    string aux;

    Recentes.open("recentes.Rec", ios::in);
    if(Recentes.is_open()){
        while(getline(Recentes, aux)){
            f->Empilhar(new QAction(QString::fromStdString(aux), MW));
        }
    }
}
