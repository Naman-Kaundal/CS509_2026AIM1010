#include "../src/kruskal.h"

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

bool loadMSTGraph(const string& path, AdjacencyListGraph& graph) {
    ifstream in(path);

    if (!in) {
        cout << "Could not open file: " << path << "\n";
        return false;
    }

    int V, E;

    if (!(in >> V >> E) || V <= 0 || E < 0) {
        cout << "Invalid graph header.\n";
        return false;
    }

    graph.numVertices = V;
    graph.numEdges = 2 * E;
    graph.adjacency.assign(V, {});

    for (int u = 0; u < V; u++) {
        int vertex, degree;

        if (!(in >> vertex >> degree) || vertex != u) {
            cout << "Invalid row for vertex " << u << ".\n";
            return false;
        }

        for (int j = 0; j < degree; j++) {
            int v;
            double w;

            if (!(in >> v >> w) || v < 0 || v >= V) {
                cout << "Invalid edge at vertex " << u << ".\n";
                return false;
            }

            graph.adjacency[u].push_back({v, w});
        }
    }

    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    AdjacencyListGraph graph;

    if (!loadMSTGraph(argv[1], graph))
        return 1;

    // Assignment 1 CSR conversion
    CSRGraph csr = convertToCSR(graph);

    vector<Edge> mst;

    auto start = chrono::high_resolution_clock::now();

    double total = kruskalMST(csr, mst);

    auto end = chrono::high_resolution_clock::now();

    double time =
        chrono::duration<double, milli>(end - start).count();

    cout << fixed << setprecision(2);

    cout << "Kruskal MST\n";
    cout << "Edges: " << mst.size() << "\n";
    cout << "Total weight: " << total << "\n";
    cout << "Time: " << time << " ms\n";

    return 0;
}