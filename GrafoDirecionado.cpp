#include "GrafoDirecionado.h"
#include <QString>

GrafoDirecionado::GrafoDirecionado(int qtdeVertice)
{
    this->qtdeVert = qtdeVertice;
    mtzGrafo = new int*[qtdeVert];

    caminho = new Pilha<int>;
    visitados = new int[qtdeVert];

    for(int i = 0; i < qtdeVert; i++){
        mtzGrafo[i] = new int[qtdeVert];
        visitados[i] = -1;
    }

    for(int i = 0; i < qtdeVert; i++)
        for(int j = 0; j < qtdeVert; j++)
            mtzGrafo[i][j] = 0;

    FilaVert = new Fila<int>;
}

GrafoDirecionado::~GrafoDirecionado()
{
    delete FilaVert;
    delete caminho;
    for(int i = 0; i < qtdeVert; i++)
        delete [] mtzGrafo[i];
    delete mtzGrafo;
    delete visitados;
}

bool GrafoDirecionado::AdcionarAresta(int origem, int destino)
{
    if(origem < 0 || origem >= qtdeVert || destino < 0 || destino >= qtdeVert)
        return false;
    mtzGrafo[origem][destino] = 1;
    return true;
}

bool GrafoDirecionado::BuscarMenorCaminho()
{
    int VertAtual = Origem;

    FilaVert->Add(VertAtual);

    while(VertAtual != destino && !(FilaVert->Empty())){
        for(int j = 0; j < qtdeVert; j++){
            if(mtzGrafo[VertAtual][j] != 0 && visitados[j] == -1){
                    FilaVert->Add(j);
                    visitados[j] = VertAtual;
                }
            }
        FilaVert->Remove();
        VertAtual = FilaVert->GetInicio();
    }
    if(VertAtual == -1){
        LimpaDadosCalculo();
        return false;
    }
    return true;
}

void GrafoDirecionado::SetObjetivo(int Origem, int destino)
{
     if(Origem >= 0 && Origem < qtdeVert && destino >= 0 && destino < qtdeVert){
        this->Origem = Origem;
        this->destino = destino;
    }else
         throw QString("Vertices desejado não existe");
}

Pilha<int> *GrafoDirecionado::GetCaminho()
{
    int valor = destino;
    caminho->Empilhar(valor);
    while(valor != Origem){
        valor = visitados[valor];
        caminho->Empilhar(valor);
    }
    LimpaDadosCalculo();
    return caminho;
}

void GrafoDirecionado::LimpaDadosCalculo()
{
    FilaVert->Clear();
    for(int i = 0; i < qtdeVert; i++)
        visitados[i] = -1;
}

Fila<Index*>* GrafoDirecionado::GetArestas(int &QtdeArestas)
{
    Fila<Index*> *Arestas = new Fila<Index*>;
    QtdeArestas = 0;

    for(int i = 0; i < this->qtdeVert; i++)
        for(int j = 0; j < this->qtdeVert; j++)
            if(mtzGrafo[i][j] == 1){
                Arestas->Add(new Index(i, j));
                QtdeArestas++;
            }
    return Arestas;
}
