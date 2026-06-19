#include "Graph.h"
#include <iostream>
#include <limits>
#include <omp.h>

Graph::Graph(int vertices)
{
    V = vertices;
    adj.resize(vertices);
}

void Graph::addEdge(
    int source,
    int destination,
    int weight)
{
    adj[source].push_back(
        {destination, weight}
    );
}
int Graph::getVertices()
{
    return V;
}

std::pair<std::vector<int>, std::vector<int>>
Graph::dijkstra(int source)
{
    std::vector<int> dist(V, std::numeric_limits<int>::max());
    std::vector<bool> visited(V, false);
    std::vector<int> parent(V, -1);

    dist[source] = 0;

    for(int count = 0; count < V - 1; count++)
    {
        int minDistance = std::numeric_limits<int>::max();
        int u = -1;

        for(int i = 0; i < V; i++)
        {
            if(!visited[i] && dist[i] < minDistance)
            {
                minDistance = dist[i];
                u = i;
            }
        }

        if(u == -1)
            break;

        visited[u] = true;

        #pragma omp parallel for
        for(int i = 0; i < (int)adj[u].size(); i++)
        {
            int v = adj[u][i].first;
            int weight = adj[u][i].second;

            if(!visited[v] &&
               dist[u] != std::numeric_limits<int>::max())
            {
                int newDistance = dist[u] + weight;

                #pragma omp critical
                {
                    if(newDistance < dist[v])
                    {
                        dist[v] = newDistance;
                        parent[v] = u;
                    }
                }
            }
        }
    }

    return {dist, parent};
}