# CS509 Laboratory Repository

## Repository Overview

This repository contains the implementations for the CS509 laboratory assignments.

The repository covers matrix multiplication, graph representation using Compressed Sparse Row (CSR), and shortest-path algorithms including Bellman-Ford and Floyd-Warshall.

The implementations are written in C++ and include separate source files, drivers, test cases, and a common wrapper for compilation and execution.

---

## Student

**Student Name:** Naman Kaundal
**Entry Number:** 2026AIM1010
**Programme:** M.Tech Artificial Intelligence
**Course:** CS509

---

## Language and Environment

* **Programming Language:** C++
* **Standard:** C++17
* **Compiler:** GNU G++
* **Optimization:** `-O2`
* **Warnings:** `-Wall`
* **Operating System:** Windows
* **Shell used for execution:** PowerShell
* **Editor:** Visual Studio Code

Compilation example:

```powershell
g++ -std=c++17 -O2 -Wall source_file.cpp driver_file.cpp -o program.exe
```

---

## Directory Structure

```text
CS509_2026AIM1010/
│
├── assignment_01/
│   ├── 01_GEMM/
│   │   ├── src/
│   │   ├── driver/
│   │   └── tests/
│   │
│   └── 02_CSR_Graph/
│       ├── src/
│       ├── driver/
│       └── tests/
│
├── assignment_02/
│   ├── 01_Bellman_Ford/
│   │   ├── src/
│   │   ├── driver/
│   │   └── tests/
│   │
│   └── 02_Floyd_Warshall/
│       ├── src/
│       ├── driver/
│       └── tests/
│
├── common_wrapper/
│   └── wrapper.cpp
│
└── README.md
```

---

# Common Wrapper: Build and Usage

The common wrapper provides a single interface for compiling and running the assignments.

It provides the following options:

```text
1. Compile all assignments
2. Run GEMM
3. Run CSR Graph
4. Run Bellman-Ford
5. Run Floyd-Warshall
0. Exit
```

### Compilation

From the repository root:

```powershell
g++ -std=c++17 -O2 -Wall .\common_wrapper\wrapper.cpp -o .\wrapper.exe
```

### Execution

```powershell
.\wrapper.exe
```

Select option `1` to compile all assignment executables.

The wrapper generates:

```text
gemm.exe
csr.exe
bellman_ford.exe
floyd_warshall.exe
```

---

# Assignment 01 - GEMM and CSR Graph

## Assignment Mode

Individual implementation.

## Objective

The assignment implements:

1. General Matrix-Matrix Multiplication (GEMM)
2. A blocked version of GEMM
3. Conversion of an adjacency-list graph representation into CSR format

---

# Assignment 01 - GEMM

## Objective

The GEMM implementation performs matrix multiplication and compares a straightforward implementation with a blocked implementation.

Both implementations compute:

```text
C = A × B
```

for compatible matrices.

## Algorithm / Approach

### Simple GEMM

The conventional triple-loop matrix multiplication approach is used.

For every output element `C[i][j]`, the implementation accumulates:

```text
A[i][k] × B[k][j]
```

over all valid `k`.

### Blocking GEMM

The matrix multiplication is divided into smaller blocks.

Blocking improves cache locality by operating on portions of the matrices that can remain in the processor cache for longer.

---

## Input Format

The GEMM test files contain the matrix dimensions followed by matrix elements according to the assignment specification.

Test files:

```text
gemm_test_01.txt
gemm_test_02.txt
gemm_test_03.txt
gemm_test_04.txt
gemm_test_05.txt
gemm_test_06.txt
```

---

## File Structure

```text
assignment_01/01_GEMM/
├── src/
│   └── gemm.cpp
├── driver/
│   └── driver_gemm.cpp
└── tests/
    ├── gemm_test_01.txt
    ├── gemm_test_02.txt
    ├── gemm_test_03.txt
    ├── gemm_test_04.txt
    ├── gemm_test_05.txt
    └── gemm_test_06.txt
```

---

## Compilation

```powershell
g++ -std=c++17 -O2 -Wall `
.\assignment_01\01_GEMM\src\gemm.cpp `
.\assignment_01\01_GEMM\driver\driver_gemm.cpp `
-o .\gemm.exe
```

## Execution

```powershell
.\gemm.exe "assignment_01/01_GEMM/tests/gemm_test_01.txt"
```

The same command can be used with the other test files.

---

## Test Cases and Result Table

| Test Case          | Simple GEMM | Blocking GEMM |
| ------------------ | ----------: | ------------: |
| `gemm_test_01.txt` |        0 ms |          0 ms |
| `gemm_test_02.txt` |        0 ms |          0 ms |
| `gemm_test_03.txt` |        0 ms |          0 ms |
| `gemm_test_04.txt` |        0 ms |          0 ms |
| `gemm_test_05.txt` |        0 ms |          0 ms |
| `gemm_test_06.txt` |        1 ms |      1.999 ms |

The runtimes are machine-dependent and may vary between executions.

---

## Complexity

For matrices of compatible dimensions, conventional GEMM has:

```text
Time Complexity: O(N³)
```

for square `N × N` matrices.

The blocked implementation has the same asymptotic complexity but can provide improved cache utilization.

---

## References

* Course assignment specification
* Standard matrix multiplication algorithm
* Standard cache-blocking technique

---

# Assignment 01 - CSR Graph

## Objective

The objective is to convert an adjacency-list graph representation into Compressed Sparse Row (CSR) format.

CSR stores graph information using:

* `rowPtr`
* `colIdx`
* `weights`

This representation provides compact storage and efficient sequential traversal of outgoing edges.

---

## Algorithm / Approach

The adjacency-list representation is first loaded.

The CSR conversion then constructs:

```text
rowPtr
colIdx
weights
```

`rowPtr[u]` and `rowPtr[u+1]` identify the range of edges belonging to vertex `u`.

The conversion is treated as preprocessing.

---

## Input Format

The graph input contains the number of vertices and edges followed by adjacency-list information for every vertex.

---

## File Structure

```text
assignment_01/02_CSR_Graph/
├── src/
│   ├── csr_graph.cpp
│   └── csr_graph.h
├── driver/
│   └── driver_csr.cpp
└── tests/
    ├── csr_10.txt
    ├── csr_100.txt
    ├── csr_10000.txt
    ├── csr_50000.txt
    └── csr_100000.txt
```

---

## Compilation

```powershell
g++ -std=c++17 -O2 -Wall `
.\assignment_01\02_CSR_Graph\src\csr_graph.cpp `
.\assignment_01\02_CSR_Graph\driver\driver_csr.cpp `
-o .\csr.exe
```

## Execution

```powershell
.\csr.exe "assignment_01/02_CSR_Graph/tests/csr_10.txt"
```

---

## Test Cases and Result Table

| Test Case        | Vertices | Runtime |
| ---------------- | -------: | ------: |
| `csr_10.txt`     |       10 |     N/A |
| `csr_100.txt`    |      100 |     N/A |
| `csr_10000.txt`  |   10,000 |     N/A |
| `csr_50000.txt`  |   50,000 |     N/A |
| `csr_100000.txt` |  100,000 |     N/A |

`N/A` is used because the current CSR driver does not report a timing value.

---

## Complexity

CSR conversion requires processing every vertex and every edge.

```text
Time Complexity: O(V + E)
Space Complexity: O(V + E)
```

---

# Assignment 02 - Bellman-Ford and Floyd-Warshall

## Assignment Mode

Individual implementation.

---

# Assignment 02 - Bellman-Ford

## Objective

The Bellman-Ford algorithm computes shortest-path distances from a specified source vertex and detects reachable negative-weight cycles.

The implementation operates on the CSR representation produced by Assignment 01.

---

## Algorithm / Approach

The algorithm repeatedly relaxes all graph edges.

For a graph with `V` vertices, edges are relaxed up to:

```text
V - 1
```

times.

An additional pass checks whether a further relaxation is possible. If so, a reachable negative-weight cycle exists.

An early-termination optimization is used when no distance changes during an iteration.

---

## Input Format

The input uses the adjacency-list graph representation used by the CSR component.

The driver additionally accepts the source vertex.

---

## File Structure

```text
assignment_02/01_Bellman_Ford/
├── src/
│   ├── bellman_ford.cpp
│   └── bellman_ford.h
├── driver/
│   └── driver_bellman_ford.cpp
└── tests/
    ├── bf_10.txt
    ├── bf_100.txt
    ├── bf_10000.txt
    ├── bf_50000.txt
    ├── bf_100000.txt
    ├── bf_negative_edge.txt
    └── bf_negative_cycle.txt
```

---

## Compilation

```powershell
g++ -std=c++17 -O2 -Wall `
.\assignment_01\02_CSR_Graph\src\csr_graph.cpp `
.\assignment_02\01_Bellman_Ford\src\bellman_ford.cpp `
.\assignment_02\01_Bellman_Ford\driver\driver_bellman_ford.cpp `
-o .\bellman_ford.exe
```

## Execution

```powershell
.\bellman_ford.exe "assignment_02/01_Bellman_Ford/tests/bf_10.txt" 0
```

The final argument specifies the source vertex.

---

## Test Cases and Result Table

| Test Case               | Source |  Runtime |
| ----------------------- | -----: | -------: |
| `bf_10.txt`             |      0 |     0 ms |
| `bf_100.txt`            |      0 |     0 ms |
| `bf_10000.txt`          |      0 |     0 ms |
| `bf_50000.txt`          |      0 | 2.001 ms |
| `bf_100000.txt`         |      0 |      N/A |
| `bf_negative_edge.txt`  |      0 |   Tested |
| `bf_negative_cycle.txt` |      0 |   Tested |

The `bf_100000.txt` test file produced an input-consistency error during the recorded run, so no runtime is reported for it.

---

## Negative-Weight Cycle Test

The negative-cycle test is used to verify that Bellman-Ford identifies a reachable negative-weight cycle.

Expected behavior:

```text
Negative-weight cycle detected.
```

---

## Complexity

```text
Time Complexity: O(VE)
Space Complexity: O(V)
```

---

## References

* Course assignment specification
* Bellman-Ford shortest-path algorithm

---

# Assignment 02 - Floyd-Warshall

## Objective

The Floyd-Warshall algorithm computes shortest paths between all pairs of vertices.

The implementation uses the CSR graph representation as input and constructs an all-pairs distance matrix.

---

## Algorithm / Approach

Initially:

* `dist[i][i] = 0`
* Direct edges are initialized using their weights.
* Unreachable pairs are represented using infinity.

For every intermediate vertex `k`, the algorithm checks whether the path:

```text
i → k → j
```

is shorter than the currently known path:

```text
i → j
```

---

## Input Format

The Floyd-Warshall test files contain a graph represented in the format expected by the Floyd-Warshall loader.

---

## File Structure

```text
assignment_02/02_Floyd_Warshall/
├── src/
│   ├── floyd_warshall.cpp
│   └── floyd_warshall.h
├── driver/
│   └── driver_floyd_warshall.cpp
└── tests/
    ├── fw_10.txt
    ├── fw_100.txt
    ├── fw_500.txt
    ├── fw_1000.txt
    └── fw_2000.txt
```

---

## Compilation

```powershell
g++ -std=c++17 -O2 -Wall `
.\assignment_02\02_Floyd_Warshall\src\floyd_warshall.cpp `
.\assignment_02\02_Floyd_Warshall\driver\driver_floyd_warshall.cpp `
-o .\floyd_warshall.exe
```

## Execution

```powershell
.\floyd_warshall.exe "assignment_02/02_Floyd_Warshall/tests/fw_10.txt"
```

---

## Test Cases and Result Table

| Test Case     | Vertices | Runtime |
| ------------- | -------: | ------: |
| `fw_10.txt`   |       10 |    0 ms |
| `fw_100.txt`  |      100 |    0 ms |
| `fw_500.txt`  |      500 |   91 ms |
| `fw_1000.txt` |    1,000 |     N/A |
| `fw_2000.txt` |    2,000 |     N/A |

The runtimes for `fw_1000.txt` and `fw_2000.txt` were not measured because execution was taking too long during the final testing session. No estimated values are reported.

---

## Complexity

```text
Time Complexity: O(V³)
Space Complexity: O(V²)
```

---

## References

* Course assignment specification
* Floyd-Warshall all-pairs shortest-path algorithm

---

# Overall Compilation and Execution Summary

From the repository root:

```powershell
g++ -std=c++17 -O2 -Wall .\common_wrapper\wrapper.cpp -o .\wrapper.exe
```

Run:

```powershell
.\wrapper.exe
```

### Menu

```text
1. Compile all assignments
2. Run GEMM
3. Run CSR Graph
4. Run Bellman-Ford
5. Run Floyd-Warshall
0. Exit
```

Option `1` compiles all assignments.

Options `2`–`5` run the corresponding assignment.

---

# Notes

* All algorithms were implemented in C++17.
* Compilation was performed using GNU G++.
* `-O2` optimization was used for benchmark compilation.
* Runtime measurements are machine-dependent.
* Input loading and CSR preprocessing are kept separate from algorithm execution where applicable.
* `N/A` indicates that a reliable runtime was not obtained during testing and is intentionally not replaced with an estimated value.
* The common wrapper provides a unified compilation and execution interface.
