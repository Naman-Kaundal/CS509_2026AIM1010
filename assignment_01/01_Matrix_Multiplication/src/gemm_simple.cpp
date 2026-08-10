#include "gemm_simple.h"

// ---------------------------------------------------------------------
// Simple GEMM: direct triple nested loop, C[i][j] = sum_k A[i][k]*B[k][j]
// This is the baseline / reference implementation used to validate the
// blocking implementation (both must produce identical results).
// ---------------------------------------------------------------------
Matrix gemm_simple(const Matrix &A, const Matrix &B, int M, int K, int N) {
    Matrix C(M, std::vector<long long>(N, 0));

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            long long sum = 0;
            for (int k = 0; k < K; ++k) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
    return C;
}
