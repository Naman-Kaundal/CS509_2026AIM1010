#include "gemm_blocking.h"
#include <algorithm>

// ---------------------------------------------------------------------
// Blocking (tiled) GEMM: the same computation as gemm_simple, but the
// i/j/k loops are split into blocks of size `block_size` so that data
// already loaded into cache is reused more before it is evicted.
// The mathematical result must be identical to gemm_simple.
// ---------------------------------------------------------------------
Matrix gemm_blocking(const Matrix &A, const Matrix &B, int M, int K, int N, int block_size) {
    Matrix C(M, std::vector<long long>(N, 0));

    if (block_size <= 0) {
        block_size = 32; // sane default
    }

    for (int ii = 0; ii < M; ii += block_size) {
        int i_max = std::min(ii + block_size, M);
        for (int jj = 0; jj < N; jj += block_size) {
            int j_max = std::min(jj + block_size, N);
            for (int kk = 0; kk < K; kk += block_size) {
                int k_max = std::min(kk + block_size, K);

                for (int i = ii; i < i_max; ++i) {
                    for (int j = jj; j < j_max; ++j) {
                        long long sum = C[i][j];
                        for (int k = kk; k < k_max; ++k) {
                            sum += A[i][k] * B[k][j];
                        }
                        C[i][j] = sum;
                    }
                }
            }
        }
    }
    return C;
}
