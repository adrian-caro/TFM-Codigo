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
    Dijkstra();
    vector<int> algorithm(int sta, int goa,vector<vector<Pair>> n);
};

#endif // DIJKSTRA_H
