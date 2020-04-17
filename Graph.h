#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
using namespace std;

struct Enlace {
    int nodofuente, nododestino;
};

class Grafo
{
private:

    vector<vector<int>> ListaAdyacencia;
public:

    Grafo(vector<Enlace> const& enlaces, int N);
    void printGraph(Grafo const& grafo, int N);
};

#endif // GRAPH_H
