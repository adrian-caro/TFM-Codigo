#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <vector>
#include "Graph.h"
#include "Tunnel.h"
#include <algorithm>

class Dijkstra
{
private:
    int nodestart;
    int nodegoal;
    vector<vector<Pair>> nodelist;
    std::vector<vector<int>> open;
    std::vector<vector<int>> closed;
public:
    Dijkstra(int sta, int goa,vector<vector<Pair>> n);
    vector<int> algorithm();
};

#endif // DIJKSTRA_H
