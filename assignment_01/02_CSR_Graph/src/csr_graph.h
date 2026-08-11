#ifndef CSR_GRAPH_H
#define CSR_GRAPH_H

#include <string>
#include <utility>
#include <vector>

struct AdjacencyListGraph {
    int numVertices = 0;
    int numEdges = 0;

    // For each vertex:
    // adjacency[u] contains {destination, weight}.
    std::vector<std::vector<std::pair<int, double>>> adjacency;
};

struct CSRGraph {
    int numVertices = 0;
    int numEdges = 0;

    std::vector<int> rowPtr;
    std::vector<int> colIdx;
    std::vector<double> weights;
};

// Reads the adjacency-list representation.
bool loadAdjacencyList(
    const std::string& path,
    AdjacencyListGraph& graph
);

// Converts adjacency list to CSR.
// This is preprocessing and is not part of algorithm timing.
CSRGraph convertToCSR(
    const AdjacencyListGraph& graph
);

#endif