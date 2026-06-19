#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>

class Graph
{
private:
    int V;
    std::vector<std::vector<std::pair<int,int>>> adj;

public:
    Graph(int vertices);
    int getVertices();

    void addEdge(
        int source,
        int destination,
        int weight
    );

    std::pair<
    std::vector<int>,
    std::vector<int>
> dijkstra(int source);
};

#endif