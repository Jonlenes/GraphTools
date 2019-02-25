#ifndef FILA_H
#define FILA_H

#include "Node.h"

template <typename Type>
class Fila
{
public:
    Fila();
    ~Fila();
    bool Empty();
    void Add(Type num);
    bool Remove(Type &num);
    bool Remove();
    Type GetInicio();
    int Size();
    void Clear();
    Type RetornaElemento(int index);
private:
    Node<Type> *inicio, *final;

};
#include "Fila.cpp"
#endif // FILA_H
