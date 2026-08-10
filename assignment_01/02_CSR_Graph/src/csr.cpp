#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

struct CSRGraph {
    int V = 0;
    int E = 0;
    int source = 0;
    std::vector<int> row_ptr;
    std::vector<int> col_idx;
    std::vector<double> values;
};

// Converts the custom adjacency list input stream to CSR format
CSRGraph convertToCSR(std::istream& in, bool is_weighted = true) {
    CSRGraph graph;
    
    // 1. Read V and E
    if (!(in >> graph.V >> graph.E)) {
        return graph;
    }

    graph.row_ptr.resize(graph.V + 1, 0);

    // 2. Process each vertex's adjacency list sequentially (u0 through uV-1)
    for (int i = 0; i < graph.V; ++i) {
        int u, degree;
        in >> u >> degree;

        // Cumulative sum for row_ptr
        graph.row_ptr[u + 1] = graph.row_ptr[u] + degree;

        for (int d = 0; d < degree; ++d) {
            int v;
            in >> v;
            graph.col_idx.push_back(v);

            if (is_weighted) {
                double w;
                in >> w;
                graph.values.push_back(w);
            }
        }
    }

    // 3. Read SOURCE
    std::string source_tag;
    if (in >> source_tag >> graph.source) {
        // Source successfully parsed
    }

    return graph;
}

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // Parse graph from std::cin
    // Change to 'false' if running on an unweighted graph format
    CSRGraph csr = convertToCSR(std::cin, /*is_weighted=*/true);

    // --- Output CSR Arrays ---
    std::cout << "=== CSR Representation ===\n";
    std::cout << "V: " << csr.V << " | E: " << csr.E << " | SOURCE: " << csr.source << "\n\n";

    std::cout << "row_ptr: [ ";
    for (int val : csr.row_ptr) std::cout << val << " ";
    std::cout << "]\n";

    std::cout << "col_idx: [ ";
    for (int val : csr.col_idx) std::cout << val << " ";
    std::cout << "]\n";

    if (!csr.values.empty()) {
        std::cout << "values:  [ ";
        for (double val : csr.values) std::cout << val << " ";
        std::cout << "]\n";
    }

    // --- Graph Traversal Demonstration using CSR ---
    std::cout << "\n=== Adjacency Lookup Test ===\n";
    for (int u = 0; u < csr.V; ++u) {
        std::cout << "Vertex " << u << " -> ";
        int start = csr.row_ptr[u];
        int end   = csr.row_ptr[u + 1];

        if (start == end) {
            std::cout << "(No outgoing edges)";
        } else {
            for (int idx = start; idx < end; ++idx) {
                std::cout << "[" << csr.col_idx[idx];
                if (!csr.values.empty()) {
                    std::cout << ", w: " << csr.values[idx];
                }
                std::cout << "] ";
            }
        }
        std::cout << "\n";
    }

    return 0;
}