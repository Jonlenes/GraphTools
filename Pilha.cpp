#ifndef PILHA_CPP
#define PILHA_CPP
#include "Pilha.h"

template <typename Type>
Pilha<Type>::Pilha()
{
    topo = new Node<Type>*;
    *topo = NULL;
}

template <typename Type>
bool Pilha<Type>::Empty()
{
    return (*topo == NULL);
}

template <typename Type>
Pilha<Type>::~Pilha()
{
    Node<Type> *no;
    while(*topo != NULL){
        no = *topo;
        *topo = (*topo)->ant;
        delete no;
    }
    delete topo;
}

template <typename Type>
bool Pilha<Type>::Empilhar(Type x)
{
    Node<Type> *no = new Node<Type>;
    no->x = x;

    if(Empty()){
        no->ant = NULL;
        *topo = no;
    }else{
        no->ant = *topo;
        *topo = no;
    }
    return true;
}

template <typename Type>
bool Pilha<Type>::Desempilhar(Type &removido)
{
    if(Empty())
        return false;
    Node<Type> *no = *topo;
    *topo = (*topo)->ant;
    removido = no->x;
    delete no;
    return true;
}

template <typename Type>
bool Pilha<Type>::GetTopo(Type &topo)
{
    if(!Empty()){
        topo = (*this->topo)->x;
        return 1;
    }
    return false;
}

template <typename Type>
int Pilha<Type>::Size()
{
    int cont = 0;
    for(Node<Type> *no = *topo; no != NULL; no = no->ant)
        cont++;
    return cont;
}

template <typename Type>
void Pilha<Type>::Clear()
{
    Node<Type> *no;
    while(*topo != NULL){
        no = *topo;
        *topo = (*topo)->ant;
        delete no;
    }
    delete topo;
}

#endif
