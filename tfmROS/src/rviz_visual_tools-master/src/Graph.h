#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include "rviz_visual_tools/headers/Node.h"

using namespace std;
class Node;
struct Enlace {
    int nodofuente, nododestino;
    float length;
};
typedef pair<int, int> Pair;

class Grafo
{
private:

    vector<vector<Pair>> ListaAdyacencia;
public:

    Grafo(vector<Enlace> const& enlaces, int N,Node *nodos);
    void printGraph(Grafo const& grafo, int N);
    vector<vector<Pair>> getlista();
};

#endif // GRAPH_H
