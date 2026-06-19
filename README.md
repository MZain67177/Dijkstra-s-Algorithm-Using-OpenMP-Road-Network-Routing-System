# Road Network Routing System Using Dijkstra Algorithm and OpenMP

## Overview

This project implements a road network routing system using graph data structures, Dijkstra's shortest path algorithm, and OpenMP parallelization.

The road network consists of:

* 2000 Nodes
* 8000 Roads
* 16000 Directed Connections

The system loads graph data from a CSV dataset generated from a MySQL database and computes the shortest path between selected locations.

## Technologies Used

* C++
* OpenMP
* MySQL
* GCC
* Visual Studio Code

## Features

* Adjacency List Graph Representation
* Dijkstra Shortest Path Algorithm
* Path Reconstruction
* OpenMP Parallel Processing
* Performance Benchmarking
* Bidirectional Road Network

## Benchmark Results

| Source | Destination | Distance | Time (s) |
| ------ | ----------- | -------- | -------- |
| 0      | 100         | 70       | 0.288    |
| 50     | 1500        | 112      | 0.253    |
| 200    | 1900        | 116      | 0.254    |
| 700    | 1800        | 88       | 0.253    |
| 1000   | 1999        | 184      | 0.252    |

Average Execution Time: 0.26 seconds

## Build

```bash
g++ src/main.cpp src/Graph.cpp src/Database.cpp -fopenmp -o build/main.exe
```

## Run Executable

```bash
./build/main.exe
```

## Rebuild From Source

```bash
g++ src/main.cpp src/Graph.cpp src/Database.cpp -fopenmp -o build/main.exe
```
