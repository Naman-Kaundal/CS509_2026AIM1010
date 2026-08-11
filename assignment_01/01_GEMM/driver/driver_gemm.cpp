#include "../src/gemm.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

static bool readMatrix(
    std::ifstream& input,
    Matrix& matrix,
    int rows,
    int cols
)
{
    matrix.assign(
        rows,
        std::vector<long long>(cols)
    );

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (!(input >> matrix[i][j]))
            {
                return false;
            }
        }
    }

    return true;
}


static void printMatrix(
    const Matrix& matrix
)
{
    for (const auto& row : matrix)
    {
        for (std::size_t j = 0; j < row.size(); ++j)
        {
            if (j > 0)
            {
                std::cout << ' ';
            }

            std::cout << row[j];
        }

        std::cout << '\n';
    }
}


int main(int argc, char* argv[])
{
    if (argc < 2 || argc > 3)
    {
        std::cerr
            << "Usage: "
            << argv[0]
            << " <input_file> [block_size]\n";

        return 1;
    }

    int blockSize = 32;

    if (argc == 3)
    {
        blockSize = std::stoi(argv[2]);
    }

    std::ifstream input(argv[1]);

    if (!input)
    {
        std::cerr
            << "Error: cannot open input file: "
            << argv[1]
            << '\n';

        return 1;
    }

    int M, K, N;

    if (!(input >> M >> K >> N))
    {
        std::cerr
            << "Error: invalid matrix header.\n";

        return 1;
    }

    if (M <= 0 || K <= 0 || N <= 0)
    {
        std::cerr
            << "Error: matrix dimensions must be positive.\n";

        return 1;
    }

    Matrix A;
    Matrix B;

    if (!readMatrix(input, A, M, K))
    {
        std::cerr
            << "Error: invalid matrix A.\n";

        return 1;
    }

    if (!readMatrix(input, B, K, N))
    {
        std::cerr
            << "Error: invalid matrix B.\n";

        return 1;
    }

    // -------------------------------------------------
    // Simple GEMM
    // -------------------------------------------------

    auto simpleStart =
        std::chrono::high_resolution_clock::now();

    Matrix simpleResult =
        gemmSimple(A, B);

    auto simpleEnd =
        std::chrono::high_resolution_clock::now();

    double simpleTime =
        std::chrono::duration<double, std::milli>(
            simpleEnd - simpleStart
        ).count();

    // -------------------------------------------------
    // Blocking GEMM
    // -------------------------------------------------

    auto blockedStart =
        std::chrono::high_resolution_clock::now();

    Matrix blockedResult =
        gemmBlocked(A, B, blockSize);

    auto blockedEnd =
        std::chrono::high_resolution_clock::now();

    double blockedTime =
        std::chrono::duration<double, std::milli>(
            blockedEnd - blockedStart
        ).count();

    // -------------------------------------------------
    // Compare results
    // -------------------------------------------------

    bool correct =
        matricesEqual(
            simpleResult,
            blockedResult
        );

    std::cout << "GEMM\n";
    std::cout << "M = " << M
              << ", K = " << K
              << ", N = " << N << '\n';

    std::cout
        << "Block size: "
        << blockSize
        << '\n';

    std::cout
        << "Simple GEMM time: "
        << simpleTime
        << " ms\n";

    std::cout
        << "Blocking GEMM time: "
        << blockedTime
        << " ms\n";

    std::cout
        << "Simple vs Blocking: "
        << (correct ? "PASS" : "FAIL")
        << '\n';

    std::cout << "\nResult matrix:\n";

    printMatrix(simpleResult);

    return correct ? 0 : 1;
}