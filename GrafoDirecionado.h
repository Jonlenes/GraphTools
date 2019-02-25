#ifndef GRAFODIRECIONADO_H
#define GRAFODIRECIONADO_H

#include "Fila.h"
#include "Pilha.h"
#include <iostream>
#include <fstream>
#include "Index.h"
using namespace std;

class GrafoDirecionado
{
public:
    GrafoDirecionado(int qtdeVertice);
    ~GrafoDirecionado();

    bool AdcionarAresta(int origem, int destino);
    bool BuscarMenorCaminho();
    void LimpaDadosCalculo();

    void SetObjetivo(int Origem, int destino);
    Pilha<int>* GetCaminho();
    int GetQtdeVertice(){return this->qtdeVert;}
    Fila<Index *>* GetArestas(int &QtdeArestas);

private:
    Fila<int> *FilaVert;
    Pilha<int> *caminho;
    int qtdeVert;
    int **mtzGrafo;
    int Origem, destino;
    int *visitados;
};

#endif // GRAFODIRECIONADO_H
