#include "Database.h"

#include <fstream>
#include <sstream>
#include <iostream>

void Database::loadGraphFromCSV(
    Graph& graph,
    const std::string& filename)
{
    std::ifstream file(filename);

    if(!file.is_open())
    {
        std::cout << "Failed to open file: "
                  << filename
                  << std::endl;
        return;
    }

    std::string line;

    std::getline(file, line);

    int edgeCount = 0;

    while(std::getline(file, line))
    {
        std::stringstream ss(line);

        std::string edgeIdStr;
        std::string sourceStr;
        std::string destinationStr;
        std::string weightStr;

        std::getline(ss, edgeIdStr, ',');
        std::getline(ss, sourceStr, ',');
        std::getline(ss, destinationStr, ',');
        std::getline(ss, weightStr, ',');

        int source = std::stoi(sourceStr);
        int destination = std::stoi(destinationStr);
        int weight = std::stoi(weightStr);

        source--;
        destination--;

        // Forward road
        graph.addEdge(
            source,
            destination,
            weight
        );

        // Reverse road
        graph.addEdge(
            destination,
            source,
            weight
        );

        edgeCount++;
    }

    file.close();

    std::cout << "Loaded "
              << edgeCount
              << " roads from CSV."
              << std::endl;

    std::cout << "Graph stored as "
              << edgeCount * 2
              << " directed connections."
              << std::endl;
}