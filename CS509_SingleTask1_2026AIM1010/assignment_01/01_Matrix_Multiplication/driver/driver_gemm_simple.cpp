// driver_gemm_simple.cpp
// Reads a GEMM test file (M K N followed by A's rows then B's rows) and
// runs GEMM Simple, as required by CS509 Assignment 1 (section 5).
//
// Usage:
//   ./driver_gemm_simple <input_file>
//
// Only the algorithm call itself is timed. File reading/parsing and
// result printing are outside the timed region (Assignment 1, section 8).

#include <iostream>
#include <chrono>
#include <string>
#include "../src/gemm_simple.h"
#include "../src/gemm_io.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Error: missing input file.\n"
                     "Usage: ./driver_gemm_simple <input_file>\n";
        return 1;
    }

    std::string inputPath = argv[1];
    int M, K, N;
    Matrix A, B;

    // --- Setup (NOT timed): read + parse input file ---
    if (!readGemmInput(inputPath, M, K, N, A, B)) {
        std::cerr << "Error: could not read or parse input file '" << inputPath << "'.\n";
        return 1;
    }

    // --- Timed region: GEMM Simple only ---
    auto start = std::chrono::high_resolution_clock::now();
    Matrix C = gemm_simple(A, B, M, K, N);
    auto end = std::chrono::high_resolution_clock::now();
    double ms = std::chrono::duration<double, std::milli>(end - start).count();

    // --- Output (NOT timed) ---
    std::cout << "Input file: " << inputPath << "\n";
    std::cout << "Dimensions: A(" << M << "x" << K << ") * B(" << K << "x" << N
               << ") -> C(" << M << "x" << N << ")\n\n";

    std::cout << "Algorithm: GEMM Simple\n";
    std::cout << "Result matrix:\n";
    printMatrix(C);
    std::cout << "Execution time: " << ms << " ms\n";

    return 0;
}
