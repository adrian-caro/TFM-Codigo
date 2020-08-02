#ifndef EXPLORATION_H
#define EXPLORATION_H
#include "Node.h"
#include "Tunnel.h"

class Node;

class Exploration
{
private:
    //vec<vec<float>> difference; //Pi,dH,dC,dAlpha,dBeta;
    //float Pnode;

    //float K;
    Node explorationnodes[10];

public:
    Exploration();
    void explorationalgorithm(Node *nodos, vector<int> solutionpath, Tunnel *tuneles, int numtuneles);
    void sensoreadings(int nodenumber, Node *nodos);
    float nodecomparison(int realnode, int mapnode, Node *nodos);
};

#endif // EXPLORATION_H
