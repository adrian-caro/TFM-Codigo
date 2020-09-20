#ifndef EXPLORATION_H
#define EXPLORATION_H
#include "rviz_visual_tools/headers/Node.h"
#include "rviz_visual_tools/headers/Tunnel.h"
#include "rviz_visual_tools/headers/Graph.h"
//#include <rviz_visual_tools/rviz_visual_tools.h>
//#include "rviz_visual_tools_demo.cpp"

#define Pheightvariationmax 0.1
#define Pwidthvariationmax 0.1
#define PHorivariationmax 0.1
#define PVorivariationmax 0.1

#define Pbadtunn 0.2

#define OOIdetectionRatio 0.9

class Node;

class Exploration
{
private:

    Node explorationnodes[100];

public:
    Exploration();
    int explorationalgorithm(Node *nodos, vector<int> solutionpath, Tunnel *tuneles, int numtuneles, vector<Pair> OOIlist,int Numnodos,vector<Enlace> const& enlaces);

    int lost(Node *nodos, int Numnodos, int actualnode);
    void sensoreadings(int nodenumber, Node *nodos);
    float nodecomparison(int realnode, int mapnode, Node *nodos);
};

#endif // EXPLORATION_H
