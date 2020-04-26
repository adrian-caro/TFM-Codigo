#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <vector>
#include "Graph.h"
#include <algorithm>
//typedef pair<int, int> Pair;
class Dijkstra
{
private:
    int nodestart;
    int nodegoal;
   // Grafo *grafo;
    vector<vector<Pair>> nodelist;
    std::vector<vector<int>> open;
    std::vector<vector<int>> closed;
public:
    Dijkstra(int sta, int goa,vector<vector<Pair>> n);
    void algorithm();
};

#endif // DIJKSTRA_H
