#include "csr.h"

CSRGraph convertAdjListToCSR(const AdjacencyList &adj, int V) {
    CSRGraph csr;
    csr.V = V;
    csr.row_ptr.assign(V + 1, 0);

    // Step 1: count degree of every vertex.
    for (int u = 0; u < V; ++u) {
        csr.row_ptr[u + 1] = csr.row_ptr[u] + static_cast<int>(adj[u].size());
    }

    int totalEdges = csr.row_ptr[V];
    csr.col_idx.assign(totalEdges, -1);
    csr.values.assign(totalEdges, 0);

    // Step 2: fill col_idx / values using a running write cursor per row.
    std::vector<int> cursor(csr.row_ptr.begin(), csr.row_ptr.begin() + V);
    for (int u = 0; u < V; ++u) {
        for (const AdjEdge &e : adj[u]) {
            int pos = cursor[u]++;
            csr.col_idx[pos] = e.to;
            csr.values[pos] = e.weight;
        }
    }

    csr.E = totalEdges;
    return csr;
}
