#include "prim.h"
#include <queue>

using namespace std;

struct Item {
    double weight;
    int u, v;

    bool operator>(const Item& other) const {
        return weight > other.weight;
    }
};

double primMST(const CSRGraph& graph, vector<Edge>& mst) {
    int n = graph.numVertices;

    vector<bool> used(n, false);

    priority_queue<
        Item,
        vector<Item>,
        greater<Item>
    > pq;

    double total = 0;

    used[0] = true;

    for (int i = graph.rowPtr[0];
         i < graph.rowPtr[1]; i++) {

        pq.push({
            graph.weights[i],
            0,
            graph.colIdx[i]
        });
    }

    while (!pq.empty() && mst.size() < n - 1) {
        Item cur = pq.top();
        pq.pop();

        if (used[cur.v])
            continue;

        used[cur.v] = true;

        mst.push_back({
            cur.u,
            cur.v,
            cur.weight
        });

        total += cur.weight;

        for (int i = graph.rowPtr[cur.v];
             i < graph.rowPtr[cur.v + 1]; i++) {

            int v = graph.colIdx[i];

            if (!used[v]) {
                pq.push({
                    graph.weights[i],
                    cur.v,
                    v
                });
            }
        }
    }

    return total;
}