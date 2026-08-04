// driver_csr.cpp
// Reads a graph in adjacency-list text format (see CS509 Assignment 1,
// sections 6.1 / 7.1), builds the adjacency list, and converts it to
// Compressed Sparse Row (CSR) format using the shared helper function.
//
// NOTE: The adjacency-list-to-CSR conversion is a preprocessing step.
// Its timing is reported separately here purely for reference /
// demonstration of the helper function's performance; it must NEVER be
// folded into the reported execution time of a graph algorithm (BFS,
// DFS, SSSP) that consumes this CSR structure in the buddy assignments.
//
// Usage:
//   ./driver_csr <input_file> [--weighted]
//
// If --weighted is passed, each neighbour is expected to be followed by
// an edge weight (as in the SSSP input format). Otherwise every
// neighbour is read without a weight (as in the BFS/DFS input format)
// and stored with weight = 1.

#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <algorithm>
#include "../src/csr.h"

static bool readGraph(const std::string &path, bool weighted,
                       AdjacencyList &adj, int &V, int &E, int &source, bool &hasSource) {
    std::ifstream in(path);
    if (!in.is_open()) return false;

    in >> V >> E;
    if (!in) return false;

    adj.assign(V, {});
    for (int i = 0; i < V; ++i) {
        int u, degree;
        if (!(in >> u >> degree)) return false;
        if (u < 0 || u >= V) return false;
        adj[u].reserve(degree);
        for (int d = 0; d < degree; ++d) {
            int to, w = 1;
            if (!(in >> to)) return false;
            if (weighted) {
                if (!(in >> w)) return false;
            }
            adj[u].push_back({to, w});
        }
    }

    hasSource = false;
    std::string tag;
    if (in >> tag) {
        if (tag == "SOURCE") {
            if (in >> source) hasSource = true;
        }
    }

    return true;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Error: missing input file.\n"
                     "Usage: ./driver_csr <input_file> [--weighted]\n";
        return 1;
    }

    std::string inputPath = argv[1];
    bool weighted = false;
    for (int i = 2; i < argc; ++i) {
        if (std::string(argv[i]) == "--weighted") weighted = true;
    }

    // --- Setup (NOT timed): read + parse adjacency-list file ---
    AdjacencyList adj;
    int V = 0, E = 0, source = -1;
    bool hasSource = false;
    if (!readGraph(inputPath, weighted, adj, V, E, source, hasSource)) {
        std::cerr << "Error: could not read or parse input file '" << inputPath << "'.\n";
        return 1;
    }

    // --- Timed region: adjacency-list -> CSR conversion only ---
    auto start = std::chrono::high_resolution_clock::now();
    CSRGraph csr = convertAdjListToCSR(adj, V);
    auto end = std::chrono::high_resolution_clock::now();
    double conversionMs = std::chrono::duration<double, std::milli>(end - start).count();

    // --- Output (NOT timed) ---
    std::cout << "Input file: " << inputPath << "\n";
    std::cout << "Graph type: " << (weighted ? "Weighted" : "Unweighted") << " adjacency list\n";
    std::cout << "V = " << csr.V << ", E (input, undirected-count) = " << E
               << ", CSR entries = " << csr.E << "\n";
    if (hasSource) std::cout << "Source: " << source << "\n";

    std::cout << "\nAlgorithm: Adjacency-List to CSR Conversion\n";

    auto printVec = [](const std::string &label, const std::vector<int> &v) {
        std::cout << label << " (" << v.size() << "): ";
        size_t limit = std::min<size_t>(v.size(), 50); // avoid flooding console for huge graphs
        for (size_t i = 0; i < limit; ++i) std::cout << v[i] << (i + 1 < limit ? ' ' : '\n');
        if (v.size() > limit) std::cout << "... (" << v.size() - limit << " more)\n";
        if (v.empty()) std::cout << "\n";
    };

    printVec("row_ptr", csr.row_ptr);
    printVec("col_idx", csr.col_idx);
    if (weighted) printVec("values ", csr.values);

    std::cout << "Execution time (conversion only): " << conversionMs << " ms\n";

    return 0;
}
