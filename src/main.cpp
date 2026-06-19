#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <omp.h>
#include <limits>

#include "Graph.h"
#include "Database.h"

void printPath(
    const std::vector<int>& parent,
    int destination)
{
    std::vector<int> path;

    int current = destination;

    while(current != -1)
    {
        path.push_back(current);
        current = parent[current];
    }

    std::reverse(path.begin(), path.end());

    for(size_t i = 0; i < path.size(); i++)
    {
        std::cout << path[i];

        if(i < path.size() - 1)
        {
            std::cout << " -> ";
        }
    }

    std::cout << std::endl;
}

int main()
{
    Graph graph(2000);

    Database::loadGraphFromCSV(
        graph,
        "data/edges.csv"
    );

    std::cout << "\n====================\n";
    std::cout << "Graph Statistics\n";
    std::cout << "====================\n";
    std::cout << "Nodes: 2000\n";
    std::cout << "Roads: 8000\n";
    std::cout << "Directed Connections: 16000\n";
    std::cout << "Average Degree: "
              << (16000.0 / 2000.0)
              << std::endl;

    std::vector<std::pair<int,int>> tests =
    {
        {0,100},
        {50,1500},
        {200,1900},
        {700,1800},
        {1000,1999}
    };

    std::ofstream resultsFile(
        "data/benchmark_results.csv"
    );

    resultsFile
        << "source,destination,distance,time\n";

    double totalTime = 0;
    double minTime = 999999;
    double maxTime = 0;

    for(size_t test = 0;
        test < tests.size();
        test++)
    {
        int source = tests[test].first;
        int destination = tests[test].second;

        double startTime = omp_get_wtime();

        auto result =
            graph.dijkstra(source);

        double endTime = omp_get_wtime();

        double executionTime =
            endTime - startTime;

        totalTime += executionTime;

        if(executionTime < minTime)
            minTime = executionTime;

        if(executionTime > maxTime)
            maxTime = executionTime;

        std::vector<int> distances =
            result.first;

        std::vector<int> parents =
            result.second;

        std::cout << "\n========== TEST "
                  << test + 1
                  << " ==========\n";

        std::cout << "Source: "
                  << source
                  << std::endl;

        std::cout << "Destination: "
                  << destination
                  << std::endl;

        if(distances[destination] ==
           std::numeric_limits<int>::max())
        {
            std::cout << "No path found.\n";

            resultsFile
                << source << ","
                << destination << ","
                << -1 << ","
                << executionTime
                << "\n";
        }
        else
        {
            std::cout << "Distance: "
                      << distances[destination]
                      << std::endl;

            std::cout << "Path: ";
            printPath(
                parents,
                destination
            );

            std::cout << "Time: "
                      << executionTime
                      << " seconds\n";

            resultsFile
                << source << ","
                << destination << ","
                << distances[destination]
                << ","
                << executionTime
                << "\n";
        }
    }

    resultsFile.close();

    std::cout
        << "\n====================\n";

    std::cout
        << "Benchmark Summary\n";

    std::cout
        << "====================\n";

    std::cout
        << "Average Time: "
        << totalTime / tests.size()
        << " seconds\n";

    std::cout
        << "Minimum Time: "
        << minTime
        << " seconds\n";

    std::cout
        << "Maximum Time: "
        << maxTime
        << " seconds\n";

    return 0;
}