#ifndef GEMM_BLOCKING_H
#define GEMM_BLOCKING_H

#include <vector>

using Matrix = std::vector<std::vector<long long>>;

// Blocking / tiled GEMM: mathematically identical to gemm_simple, but the
// i/j/k loops are split into tiles of size `block_size` so that data
// already loaded into cache is reused more before it is evicted.
Matrix gemm_blocking(const Matrix &A, const Matrix &B, int M, int K, int N, int block_size);

#endif // GEMM_BLOCKING_H
