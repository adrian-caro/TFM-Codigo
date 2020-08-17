#ifndef EXPLORATION_H
#define EXPLORATION_H
#include "Node.h"
#include "Tunnel.h"

#define Pheightvariationmax 0.15
#define Pwidthvariationmax 0.15
#define PHorivariationmax 0.15
#define PVorivariationmax 0.15

#define Pbadtunn 0.2

class Node;

class Exploration
{
private:

    Node explorationnodes[100];

public:
    Exploration();
    void explorationalgorithm(Node *nodos, vector<int> solutionpath, Tunnel *tuneles, int numtuneles);
    int lost(Node *nodos, int Numnodos, int actualnode);
    void sensoreadings(int nodenumber, Node *nodos);
    float nodecomparison(int realnode, int mapnode, Node *nodos);
};

#endif // EXPLORATION_H
