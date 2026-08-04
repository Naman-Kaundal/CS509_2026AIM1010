#!/usr/bin/env python3
"""Generate a random GEMM test file: M K N followed by A rows then B rows."""
import random
import sys

def generate(M, K, N, path, low=-10, high=10, seed=None):
    if seed is not None:
        random.seed(seed)
    with open(path, "w") as f:
        f.write(f"{M} {K} {N}\n")
        for _ in range(M):
            f.write(" ".join(str(random.randint(low, high)) for _ in range(K)) + "\n")
        for _ in range(K):
            f.write(" ".join(str(random.randint(low, high)) for _ in range(N)) + "\n")

if __name__ == "__main__":
    if len(sys.argv) < 5:
        print("Usage: generate_gemm.py <M> <K> <N> <output_path> [seed]")
        sys.exit(1)
    M, K, N, out = int(sys.argv[1]), int(sys.argv[2]), int(sys.argv[3]), sys.argv[4]
    seed = int(sys.argv[5]) if len(sys.argv) > 5 else 42
    generate(M, K, N, out, seed=seed)
    print(f"Wrote {out} ({M}x{K} * {K}x{N})")
