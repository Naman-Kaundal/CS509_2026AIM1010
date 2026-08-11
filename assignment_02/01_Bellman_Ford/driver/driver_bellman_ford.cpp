#include "../../../assignment_01/02_CSR_Graph/src/csr_graph.h"
#include "../src/bellman_ford.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cerr
            << "Usage: "
            << argv[0]
            << " <input_file> <source_vertex>\n";

        return 1;
    }

    const std::string inputFile = argv[1];

    int source;

    try
    {
        source = std::stoi(argv[2]);
    }
    catch (...)
    {
        std::cerr
            << "Invalid source vertex.\n";

        return 1;
    }

    /*
     * ----------------------------------------------------
     * PREPROCESSING
     * ----------------------------------------------------
     *
     * Adjacency-list loading and CSR conversion are
     * preprocessing and are NOT timed.
     */

    AdjacencyListGraph adjacencyGraph;

    if (!loadAdjacencyList(
            inputFile,
            adjacencyGraph))
    {
        return 1;
    }

    CSRGraph csrGraph =
        convertToCSR(adjacencyGraph);

    /*
     * ----------------------------------------------------
     * ALGORITHM TIMING STARTS HERE
     * ----------------------------------------------------
     */

    auto start =
        std::chrono::high_resolution_clock::now();

    BellmanFordResult result =
        bellmanFord(
            csrGraph,
            source
        );

    auto end =
        std::chrono::high_resolution_clock::now();

    double elapsedMs =
        std::chrono::duration<double, std::milli>(
            end - start
        ).count();

    /*
     * ----------------------------------------------------
     * OUTPUT
     * ----------------------------------------------------
     */

    std::cout
        << "Bellman-Ford\n";

    std::cout
        << "Vertices: "
        << csrGraph.numVertices
        << '\n';

    std::cout
        << "Edges: "
        << csrGraph.numEdges
        << '\n';

    std::cout
        << "Source: "
        << source
        << '\n';

    if (result.hasNegativeCycle)
    {
        std::cout
            << "Negative-weight cycle detected.\n";
    }
    else
    {
        std::cout
            << "Negative-weight cycle: NO\n";

        std::cout
            << std::setprecision(10);

        for (int v = 0;
             v < csrGraph.numVertices;
             ++v)
        {
            std::cout
                << "dist["
                << v
                << "] = ";

            if (result.distances[v] ==
                std::numeric_limits<double>::infinity())
            {
                std::cout << "INF";
            }
            else
            {
                std::cout
                    << result.distances[v];
            }

            std::cout << '\n';
        }
    }

    std::cout
        << "Bellman-Ford time: "
        << elapsedMs
        << " ms\n";

    return 0;
}