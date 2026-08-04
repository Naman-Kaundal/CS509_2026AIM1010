#ifndef GEMM_IO_H
#define GEMM_IO_H

// Shared, header-only I/O helpers used by both the Simple and Blocking
// GEMM drivers, so that both read/print in an identical (and therefore
// fairly comparable) way. Reading/printing here is always OUTSIDE the
// timed region in both drivers.

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using Matrix = std::vector<std::vector<long long>>;

// Reads the CS509 GEMM text-file format:
//   M K N
//   A row 0 .. A row M-1
//   B row 0 .. B row K-1
inline bool readGemmInput(const std::string &path, int &M, int &K, int &N,
                           Matrix &A, Matrix &B) {
    std::ifstream in(path);
    if (!in.is_open()) {
        return false;
    }
    in >> M >> K >> N;
    if (!in) return false;

    A.assign(M, std::vector<long long>(K));
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < K; ++j)
            if (!(in >> A[i][j])) return false;

    B.assign(K, std::vector<long long>(N));
    for (int i = 0; i < K; ++i)
        for (int j = 0; j < N; ++j)
            if (!(in >> B[i][j])) return false;

    return true;
}

inline void printMatrix(const Matrix &C) {
    for (const auto &row : C) {
        for (size_t j = 0; j < row.size(); ++j) {
            std::cout << row[j] << (j + 1 < row.size() ? ' ' : '\n');
        }
    }
}

#endif // GEMM_IO_H
