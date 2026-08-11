#include "csr_graph.h"

#include <fstream>
#include <iostream>

bool loadAdjacencyList(
    const std::string& path,
    AdjacencyListGraph& graph
)
{
    std::ifstream in(path);

    if (!in.is_open())
    {
        std::cerr << "Could not open file: "
                  << path << '\n';

        return false;
    }

    int V;
    int E;

    if (!(in >> V >> E))
    {
        std::cerr << "Invalid graph header.\n";
        return false;
    }

    if (V < 0 || E < 0)
    {
        std::cerr << "Invalid number of vertices or edges.\n";
        return false;
    }

    graph.numVertices = V;
    graph.numEdges = E;

    graph.adjacency.assign(
        V,
        {}
    );

    long long actualEdges = 0;

    for (int u = 0; u < V; ++u)
    {
        int vertex;
        int degree;

        if (!(in >> vertex >> degree))
        {
            std::cerr
                << "Invalid adjacency-list row for vertex "
                << u << ".\n";

            return false;
        }

        if (vertex != u)
        {
            std::cerr
                << "Expected vertex "
                << u
                << " but found "
                << vertex
                << ".\n";

            return false;
        }

        if (degree < 0)
        {
            std::cerr
                << "Invalid degree for vertex "
                << u << ".\n";

            return false;
        }

        for (int j = 0; j < degree; ++j)
        {
            int v;
            double weight;

            if (!(in >> v >> weight))
            {
                std::cerr
                    << "Invalid edge information for vertex "
                    << u << ".\n";

                return false;
            }

            if (v < 0 || v >= V)
            {
                std::cerr
                    << "Invalid destination vertex "
                    << v << ".\n";

                return false;
            }

            graph.adjacency[u].push_back(
                {v, weight}
            );

            ++actualEdges;
        }
    }

    if (actualEdges != E)
    {
        std::cerr
            << "Header says "
            << E
            << " edges, but adjacency list contains "
            << actualEdges
            << ".\n";

        return false;
    }

    return true;
}


CSRGraph convertToCSR(
    const AdjacencyListGraph& graph
)
{
    CSRGraph csr;

    csr.numVertices = graph.numVertices;
    csr.numEdges = graph.numEdges;

    csr.rowPtr.resize(
        graph.numVertices + 1,
        0
    );

    csr.colIdx.resize(
        graph.numEdges
    );

    csr.weights.resize(
        graph.numEdges
    );

    // Determine where each row begins.
    for (int u = 0; u < graph.numVertices; ++u)
    {
        csr.rowPtr[u + 1] =
            csr.rowPtr[u]
            + static_cast<int>(
                graph.adjacency[u].size()
            );
    }

    // Fill CSR arrays.
    int position = 0;

    for (int u = 0; u < graph.numVertices; ++u)
    {
        for (const auto& edge : graph.adjacency[u])
        {
            csr.colIdx[position] = edge.first;
            csr.weights[position] = edge.second;

            ++position;
        }
    }

    return csr;
}