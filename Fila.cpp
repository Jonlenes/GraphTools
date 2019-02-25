#ifndef FILA_CPP
#define FILA_CPP

#include "Fila.h"
#include <iostream>
using namespace std;

template <typename Type>
Fila<Type>::Fila()
{
    inicio = NULL;
    final = NULL;
}

template <typename Type>
Fila<Type>::~Fila()
{
    Node<Type> *aux;
    while(inicio != NULL){
        aux = inicio;
        inicio = inicio->prox;
        delete aux;
    }
}

template <typename Type> bool Fila<Type>::Empty()
{
    return (inicio == NULL);
}

template <typename Type> void Fila<Type>::Add(Type num)
{
    Node<Type> *no = new Node<Type>;
    no->x = num;
    no->prox = NULL;

    if(Empty()){
        inicio = no;
    }else
        final->prox = no;
    final = no;
}

template <typename Type> bool Fila<Type>::Remove(Type &num)
{
    if(Empty())
        return false;
    Node<Type> *no = inicio;
    num = no->x;
    inicio = inicio->prox;
    if(Empty())
        final = NULL;
    delete no;
    return true;
}

template <typename Type> bool Fila<Type>::Remove()
{
    if(Empty())
        return false;
    Node<Type> *no = inicio;
    inicio = inicio->prox;
    if(Empty())
        final = NULL;
    delete no;
    return true;
}

template <typename Type> Type Fila<Type>::GetInicio()
{
    if(!Empty())
        return (inicio->x);
    return -1;
}

template <typename Type> void Fila<Type>::Clear()
{
    Node<Type> *no;
    while(inicio != NULL){
        no = inicio;
        inicio = inicio->prox;
        delete no;
    }
    inicio = NULL;
    final = NULL;
}
template <typename Type> int Fila<Type>::Size()
{
    int cont = 0;
    for(Node<Type> *aux = inicio; aux != NULL; aux = aux->prox)
        cont++;
    return cont;
}

template <typename Type> Type Fila<Type>::RetornaElemento(int index)
{
    Node<Type> *aux = inicio;
    for(int i = 0; (i != index && aux != NULL); i++)
        aux = aux->prox;
    if(aux == NULL)
        throw string("Index fora do intervalo.");
    return aux->x;
}
#endif
