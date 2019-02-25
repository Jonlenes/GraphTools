#ifndef PILHA_H
#define PILHA_H

#include "Node.h"
#include<iostream>
using namespace std;

template<typename Type>
class Pilha
{
public:
    Pilha();
    ~Pilha();
    bool Empty();
    bool Empilhar(Type x);
    bool Desempilhar(Type &removido);
    bool GetTopo(Type &topo);
    int Size();
    void Clear();
private:
    Node<Type> **topo;
};
#include "Pilha.cpp"
#endif // PILHA_H
