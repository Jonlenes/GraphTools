#ifndef NODE_H
#define NODE_H

#include<iostream>
using namespace std;

template <typename Type>

class Node
{
public:
    Node ();
    Type x;
    Node *ant;
    Node *prox;
};

#include "Node.cpp"
#endif // NODE_H
