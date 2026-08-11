#include "../src/floyd_warshall.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr
            << "Usage: "
            << argv[0]
            << " <input_file>\n";

        return 1;
    }

    FloydWarshallGraph graph;

    /*
        Input loading is preprocessing.
        It is NOT included in algorithm timing.
    */

    if (!graph.loadFromFile(argv[1]))
    {
        return 1;
    }

    std::cout << "Floyd-Warshall\n";
    std::cout
        << "Vertices: "
        << graph.numVertices
        << '\n';

    /*
        Start timing ONLY for Floyd-Warshall.
    */

    auto start =
        std::chrono::high_resolution_clock::now();

    auto dist =
        floydWarshall(graph);

    auto end =
        std::chrono::high_resolution_clock::now();

    auto elapsed =
        std::chrono::duration_cast<
            std::chrono::milliseconds
        >(end - start);

    bool negativeCycle =
        hasNegativeCycle(dist);

    std::cout
        << "Negative-weight cycle: "
        << (negativeCycle ? "YES" : "NO")
        << '\n';

    std::cout
        << "Floyd-Warshall time: "
        << elapsed.count()
        << " ms\n";

    /*
        Print the resulting shortest-path matrix.
    */

    std::cout << "\nDistance matrix:\n";

    const double INF =
        std::numeric_limits<double>::infinity();

    for (int i = 0; i < graph.numVertices; ++i)
    {
        for (int j = 0; j < graph.numVertices; ++j)
        {
            if (dist[i][j] == INF)
            {
                std::cout << "INF";
            }
            else
            {
                std::cout
                    << std::setprecision(10)
                    << dist[i][j];
            }

            if (j + 1 < graph.numVertices)
            {
                std::cout << ' ';
            }
        }

        std::cout << '\n';
    }

    return 0;
}