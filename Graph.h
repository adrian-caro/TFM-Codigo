#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
using namespace std;

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

    Grafo(vector<Enlace> const& enlaces, int N);
    void printGraph(Grafo const& grafo, int N);
};

#endif // GRAPH_H
