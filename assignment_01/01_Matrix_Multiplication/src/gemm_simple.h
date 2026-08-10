#ifndef GEMM_SIMPLE_H
#define GEMM_SIMPLE_H

#include <vector>

using Matrix = std::vector<std::vector<long long>>;

// Simple / direct nested-loop GEMM: C (MxN) = A (MxK) * B (KxN)
// C[i][j] = sum_k A[i][k] * B[k][j]
Matrix gemm_simple(const Matrix &A, const Matrix &B, int M, int K, int N);

#endif // GEMM_SIMPLE_H
