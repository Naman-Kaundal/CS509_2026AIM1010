#include "kruskal.h"
#include <algorithm>

using namespace std;

int findParent(vector<int>& parent, int x) {
    if (parent[x] != x)
        parent[x] = findParent(parent, parent[x]);

    return parent[x];
}

bool unite(vector<int>& parent, vector<int>& rank, int a, int b) {
    a = findParent(parent, a);
    b = findParent(parent, b);

    if (a == b)
        return false;

    if (rank[a] < rank[b])
        swap(a, b);

    parent[b] = a;

    if (rank[a] == rank[b])
        rank[a]++;

    return true;
}

double kruskalMST(const CSRGraph& graph, vector<Edge>& mst) {
    vector<Edge> edges;

    for (int u = 0; u < graph.numVertices; u++) {
        for (int i = graph.rowPtr[u];
             i < graph.rowPtr[u + 1]; i++) {

            int v = graph.colIdx[i];

            if (u < v)
                edges.push_back({u, v, graph.weights[i]});
        }
    }

    sort(edges.begin(), edges.end(),
         [](const Edge& a, const Edge& b) {
             return a.weight < b.weight;
         });

    vector<int> parent(graph.numVertices);
    vector<int> rank(graph.numVertices, 0);

    for (int i = 0; i < graph.numVertices; i++)
        parent[i] = i;

    double total = 0;

    for (const Edge& edge : edges) {
        if (unite(parent, rank, edge.u, edge.v)) {
            mst.push_back(edge);
            total += edge.weight;

            if (mst.size() == graph.numVertices - 1)
                break;
        }
    }

    return total;
}