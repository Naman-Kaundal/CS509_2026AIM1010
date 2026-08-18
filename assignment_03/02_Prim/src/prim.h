#ifndef PRIM_H
#define PRIM_H

#include "../../../assignment_01/02_CSR_Graph/src/csr_graph.h"
#include <vector>

struct Edge {
    int u, v;
    double weight;
};

double primMST(const CSRGraph& graph, std::vector<Edge>& mst);

#endif