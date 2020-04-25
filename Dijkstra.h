#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <vector>
#include "Graph.h"

class Dijkstra
{
private:
    std::vector<int> visited;
    std::vector<int> queue;
public:
    Dijkstra();
    void algorithm(Grafo grafo,int source);
};

#endif // DIJKSTRA_H
