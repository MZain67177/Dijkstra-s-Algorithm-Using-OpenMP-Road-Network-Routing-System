#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include "Graph.h"

class Database
{
public:
    static void loadGraphFromCSV(
        Graph& graph,
        const std::string& filename
    );
};

#endif