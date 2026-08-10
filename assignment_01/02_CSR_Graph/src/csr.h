// #ifndef CSR_H
// #define CSR_H

// #include <vector>

// // One entry in an adjacency list: neighbour vertex + edge weight
// // (weight is ignored / set to 1 for unweighted graphs).
// struct AdjEdge {
//     int to;
//     int weight;
// };

// using AdjacencyList = std::vector<std::vector<AdjEdge>>;

// // Compressed Sparse Row representation of a graph.
// struct CSRGraph {
//     int V = 0;
//     int E = 0;
//     std::vector<int> row_ptr; // size V+1
//     std::vector<int> col_idx; // size E (or 2E for undirected, matches adjacency list entries)
//     std::vector<int> values;  // size == col_idx.size(); edge weights (1 if unweighted)
// };

// // Converts an adjacency list into CSR format.
// // This is a preprocessing step: its execution time must NEVER be counted
// // as part of any graph algorithm's reported execution time.
// CSRGraph convertAdjListToCSR(const AdjacencyList &adj, int V);

// #endif // CSR_H



#ifndef CSR_H
#define CSR_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

struct Edge {
    int to;
    double weight;
};

using AdjacencyList = std::vector<std::vector<Edge>>;

struct CSRGraph {
    int V = 0;
    int E = 0;
    int source = 0;
    std::vector<int> row_ptr;
    std::vector<int> col_idx;
    std::vector<double> values;
};

// Converts an in-memory AdjacencyList to CSRGraph (used for timing conversion only)
inline CSRGraph convertAdjListToCSR(const AdjacencyList& adj, int V, bool is_weighted = true) {
    CSRGraph graph;
    graph.V = V;
    graph.row_ptr.resize(V + 1, 0);

    int cumulative_edges = 0;
    for (int u = 0; u < V; ++u) {
        for (const auto& edge : adj[u]) {
            graph.col_idx.push_back(edge.to);
            if (is_weighted) {
                graph.values.push_back(edge.weight);
            }
            cumulative_edges++;
        }
        graph.row_ptr[u + 1] = cumulative_edges;
    }

    graph.E = cumulative_edges;
    return graph;
}

// Stream-based conversion (for parsing file directly into CSR format)
inline CSRGraph convertToCSR(std::istream& in, bool is_weighted = true) {
    CSRGraph graph;
    
    if (!(in >> graph.V >> graph.E)) {
        return graph;
    }

    graph.row_ptr.resize(graph.V + 1, 0);
    int cumulative_edges = 0;

    std::string line;
    int processed_vertices = 0;

    while (processed_vertices < graph.V && std::getline(in, line)) {
        if (line.empty() || line[0] == '#' || line[0] == '%') {
            continue;
        }

        std::stringstream ss(line);
        int u, degree;
        if (!(ss >> u >> degree)) {
            continue;
        }

        if (u < 0 || u >= graph.V) {
            std::cerr << "Warning: Vertex index " << u << " out of range [0, " << graph.V - 1 << "]\n";
            continue;
        }

        for (int d = 0; d < degree; ++d) {
            int v;
            if (ss >> v) {
                graph.col_idx.push_back(v);

                if (is_weighted) {
                    double w = 1.0;
                    if (ss >> w) {
                        graph.values.push_back(w);
                    } else {
                        graph.values.push_back(1.0);
                    }
                }
                cumulative_edges++;
            }
        }

        graph.row_ptr[u + 1] = cumulative_edges;
        processed_vertices++;
    }

    for (int i = 1; i <= graph.V; ++i) {
        if (graph.row_ptr[i] < graph.row_ptr[i - 1]) {
            graph.row_ptr[i] = graph.row_ptr[i - 1];
        }
    }

    std::string source_tag;
    while (in >> source_tag) {
        if (source_tag == "SOURCE" || source_tag == "source") {
            in >> graph.source;
            break;
        }
    }

    graph.E = cumulative_edges;
    return graph;
}

#endif // CSR_H