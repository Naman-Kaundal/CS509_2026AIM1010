#ifndef CSR_H
#define CSR_H

#include <vector>

// One entry in an adjacency list: neighbour vertex + edge weight
// (weight is ignored / set to 1 for unweighted graphs).
struct AdjEdge {
    int to;
    int weight;
};

using AdjacencyList = std::vector<std::vector<AdjEdge>>;

// Compressed Sparse Row representation of a graph.
struct CSRGraph {
    int V = 0;
    int E = 0;
    std::vector<int> row_ptr; // size V+1
    std::vector<int> col_idx; // size E (or 2E for undirected, matches adjacency list entries)
    std::vector<int> values;  // size == col_idx.size(); edge weights (1 if unweighted)
};

// Converts an adjacency list into CSR format.
// This is a preprocessing step: its execution time must NEVER be counted
// as part of any graph algorithm's reported execution time.
CSRGraph convertAdjListToCSR(const AdjacencyList &adj, int V);

#endif // CSR_H
