#ifndef EXPLORATION_H
#define EXPLORATION_H
#include "Node.h"
#include "Tunnel.h"
#include "Graph.h"

#define Pheightvariationmax 0.1
#define Pwidthvariationmax 0.1
#define PHorivariationmax 0.1
#define PVorivariationmax 0.1

#define Pbadtunn 0.3

#define OOIdetectionRatio 0.9

class Node;

class Exploration
{
private:

    Node explorationnodes[100];

public:
    Exploration();
    int explorationalgorithm(Node *nodos, vector<int> solutionpath, Tunnel *tuneles, int numtuneles,vector<Pair> OOIlist, int Numnodos,vector<Enlace> const& enlaces);
    int lost(Node *nodos, int Numnodos, int actualnode);
    void sensoreadings(int nodenumber, Node *nodos);
    float nodecomparison(int realnode, int mapnode, Node *nodos);
};

#endif // EXPLORATION_H
