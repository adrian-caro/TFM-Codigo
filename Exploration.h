#ifndef EXPLORATION_H
#define EXPLORATION_H
#include "Node.h"
#include "Tunnel.h"

class Node;

class Exploration
{
private:
    float dH,dC,dAlpha,dBeta;
    float P;
    float K;
    Node explorationnodes[10];

public:
    Exploration();
    //void explorationalgorithm(int nodoini,Node *nodos,vector<int> solutionpath);
    void sensoreadings(int nodenumber,Node *nodos);
};

#endif // EXPLORATION_H
