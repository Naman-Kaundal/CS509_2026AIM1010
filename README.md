# CS509 Laboratory Repository

## Repository Overview

This repository contains the implementations for the CS509 laboratory assignments.

The repository covers matrix multiplication, graph representation using Compressed Sparse Row (CSR), shortest-path algorithms including Bellman-Ford and Floyd-Warshall, and minimum spanning tree algorithms including Kruskal and Prim.

The implementations are written in C++ and include separate source files, drivers, test cases, and a common wrapper for compilation and execution.

---

## Student

| Field | Value |
|---|---|
| **Student Name** | Naman Kaundal |
| **Entry Number** | 2026AIM1010 |
| **Programme** | M.Tech Artificial Intelligence |
| **Course** | CS509 |

---

## Language and Environment

* **Programming Language:** C++
* **Standard:** C++17
* **Compiler:** GNU G++
* **Optimization:** `-O2`
* **Warnings:** `-Wall`
* **Operating System:** Ubuntu / WSL
* **Shell used for execution:** Bash
* **Editor:** Visual Studio Code

Compilation example:

```bash
g++ -std=c++17 -O2 -Wall source_file.cpp driver_file.cpp -o program
```

---

## Directory Structure

```
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
├── assignment_03/
│   ├── 01_Kruskal/
│   │   ├── src/
│   │   └── driver/
│   │
│   ├── 02_Prim/
│   │   ├── src/
│   │   └── driver/
│   │
│   └── tests/
│       ├── mst_10.txt
│       ├── mst_100.txt
│       ├── mst_10000.txt
│       ├── mst_50000.txt
│       └── mst_100000.txt
│
├── common_wrapper/
│   └── wrapper.cpp
│
└── README.md
```

---

# Common Wrapper: Build and Usage

The common wrapper provides a single interface for compiling and running all assignments.

The wrapper first asks the user to select the assignment, then the algorithm, and finally the required test case.

The main menu is:

```
========================================
          CS509 COMMON WRAPPER
========================================

Select Assignment:
1. Assignment 1
2. Assignment 2
3. Assignment 3
0. Exit
```

For Assignment 3, the algorithm menu is:

```
Select Algorithm:
1. Kruskal
2. Prim
0. Back
```

The available test cases are then displayed for the selected algorithm.

### Compilation

From the repository root:

```bash
g++ -std=c++17 -O2 -Wall common_wrapper/wrapper.cpp -o wrapper
```

### Execution

```bash
./wrapper
```

The wrapper can be used to compile and run the required assignment and test case.

---

# Assignment 01 – GEMM and CSR Graph

## Assignment Mode

Individual implementation.

## Objective

The assignment implements:

* General Matrix-Matrix Multiplication (GEMM)
* A blocked version of GEMM
* Conversion of an adjacency-list graph representation into CSR format

---

## Assignment 01 – GEMM

### Objective

The GEMM implementation performs matrix multiplication and compares a straightforward implementation with a blocked implementation.

Both implementations compute:

```
C = A × B
```

for compatible matrices.

### Algorithm / Approach

**Simple GEMM**

The conventional triple-loop matrix multiplication approach is used.

For every output element `C[i][j]`, the implementation accumulates `A[i][k] × B[k][j]` over all valid `k`.

**Blocking GEMM**

The matrix multiplication is divided into smaller blocks.

Blocking improves cache locality by operating on portions of the matrices that can remain in the processor cache for longer.

### Input Format

The GEMM test files contain the matrix dimensions followed by matrix elements according to the assignment specification.

Test files:

* `gemm_test_01.txt`
* `gemm_test_02.txt`
* `gemm_test_03.txt`
* `gemm_test_04.txt`
* `gemm_test_05.txt`
* `gemm_test_06.txt`

### File Structure

```
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

### Compilation

```bash
g++ -std=c++17 -O2 -Wall \
  assignment_01/01_GEMM/src/gemm.cpp \
  assignment_01/01_GEMM/driver/driver_gemm.cpp \
  -o gemm
```

### Execution

```bash
./gemm "assignment_01/01_GEMM/tests/gemm_test_01.txt"
```

The same command can be used with the other test files.

### Test Cases and Result Table

| Test Case | Dimensions (M×K×N) | Simple GEMM | Blocking GEMM |
|---|---|---|---|
| gemm_test_01.txt | 2×3×2 | 0.001 ms | 0.001 ms |
| gemm_test_02.txt | 3×3×3 | 0.001 ms | 0.001 ms |
| gemm_test_03.txt | 100×150×80 | 0.86 ms | 0.88 ms |
| gemm_test_04.txt | 200×200×200 | 6.53 ms | 5.80 ms |
| gemm_test_05.txt | 500×500×500 | 196.35 ms | 110.74 ms |
| gemm_test_06.txt | 600×300×400 | 91.37 ms | 61.16 ms |

The runtimes are machine-dependent and may vary between executions.

### Complexity

For matrices of compatible dimensions, conventional GEMM has:

**Time Complexity:** O(N³) for square N × N matrices.

The blocked implementation has the same asymptotic complexity but can provide improved cache utilization.

### References

* Course assignment specification
* Standard matrix multiplication algorithm
* Standard cache-blocking technique

---

## Assignment 01 – CSR Graph

### Objective

The objective is to convert an adjacency-list graph representation into Compressed Sparse Row (CSR) format.

CSR stores graph information using:

* `rowPtr`
* `colIdx`
* `weights`

This representation provides compact storage and efficient sequential traversal of outgoing edges.

### Algorithm / Approach

The adjacency-list representation is first loaded.

The CSR conversion then constructs `rowPtr`, `colIdx`, and `weights`.

`rowPtr[u]` and `rowPtr[u+1]` identify the range of edges belonging to vertex `u`.

The conversion is treated as preprocessing.

The CSR implementation from Assignment 01 is reused by the graph algorithms in later assignments.

### Input Format

The graph input contains the number of vertices and edges followed by adjacency-list information for every vertex.

### File Structure

```
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

### Compilation

```bash
g++ -std=c++17 -O2 -Wall \
  assignment_01/02_CSR_Graph/src/csr_graph.cpp \
  assignment_01/02_CSR_Graph/driver/driver_csr.cpp \
  -o csr
```

### Execution

```bash
./csr "assignment_01/02_CSR_Graph/tests/csr_10.txt"
```

### Test Cases and Result Table

| Test Case | Vertices | Edges (input) | CSR entries | Conversion time |
|---|---|---|---|---|
| csr_10.txt | 10 | 20 | 40 | 0.0036 ms |
| csr_100.txt | 100 | 200 | 400 | 0.0067 ms |
| csr_10000.txt | 10,000 | 20,000 | 40,000 | 0.544 ms |
| csr_50000.txt | 50,000 | 100,000 | 200,000 | 2.338 ms |
| csr_100000.txt | 100,000 | 200,000 | 400,000 | 4.734 ms |

N/A is used where a reliable runtime was not obtained from the current driver.

### Complexity

**Time Complexity:** O(V + E)
**Space Complexity:** O(V + E)

---

# Assignment 02 – Bellman-Ford and Floyd-Warshall

## Assignment Mode

Individual implementation.

---

## Assignment 02 – Bellman-Ford

### Objective

The Bellman-Ford algorithm computes shortest-path distances from a specified source vertex and detects reachable negative-weight cycles.

The implementation operates on the CSR representation produced by Assignment 01.

### Algorithm / Approach

The algorithm repeatedly relaxes all graph edges.

For a graph with V vertices, edges are relaxed up to `V - 1` times.

An additional pass checks whether a further relaxation is possible. If so, a reachable negative-weight cycle exists.

An early-termination optimization is used when no distance changes during an iteration.

### Input Format

The input uses the adjacency-list graph representation used by the CSR component.

The driver additionally accepts the source vertex.

### File Structure

```
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
    ├── bf_neg_edge.txt
    └── bf_negative_cycle.txt
```

### Compilation

```bash
g++ -std=c++17 -O2 -Wall \
  assignment_01/02_CSR_Graph/src/csr_graph.cpp \
  assignment_02/01_Bellman_Ford/src/bellman_ford.cpp \
  assignment_02/01_Bellman_Ford/driver/driver_bellman_ford.cpp \
  -o bellman_ford
```

### Execution

```bash
./bellman_ford "assignment_02/01_Bellman_Ford/tests/bf_10.txt" 0
```

The final argument specifies the source vertex.

### Test Cases and Result Table

| Test Case | Vertices | Source | Runtime |
|---|---|---|---|
| bf_10.txt | 10 | 0 | 0.00 ms |
| bf_100.txt | 100 | 0 | 0.00 ms |
| bf_10000.txt | 10,000 | 0 | 1.21 ms |
| bf_50000.txt | 50,000 | 0 | 2.34 ms |
| bf_100000.txt | 100,000 | 0 | 4.21 ms |
| bf_neg_edge.txt | — | 0 | 0.06 ms |
| bf_negative_cycle.txt | — | 0 | 1.22 ms |

The runtimes are machine-dependent and may vary between executions.

### Negative-Weight Cycle Test

The negative-cycle test is used to verify that Bellman-Ford identifies a reachable negative-weight cycle.

Expected behavior:

```
Negative-weight cycle detected.
```

### Complexity

**Time Complexity:** O(VE)
**Space Complexity:** O(V)

### References

* Course assignment specification
* Bellman-Ford shortest-path algorithm

---

## Assignment 02 – Floyd-Warshall

### Objective

The Floyd-Warshall algorithm computes shortest paths between all pairs of vertices.

The implementation uses the input graph to construct an all-pairs distance matrix.

### Algorithm / Approach

Initially:

* `dist[i][i] = 0`
* Direct edges are initialized using their weights.
* Unreachable pairs are represented using infinity.

For every intermediate vertex `k`, the algorithm checks whether the path `i → k → j` is shorter than the currently known path `i → j`.

### Input Format

The Floyd-Warshall test files contain a graph represented in the format expected by the Floyd-Warshall loader.

### File Structure

```
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

### Compilation

```bash
g++ -std=c++17 -O2 -Wall \
  assignment_02/02_Floyd_Warshall/src/floyd_warshall.cpp \
  assignment_02/02_Floyd_Warshall/driver/driver_floyd_warshall.cpp \
  -o floyd_warshall
```

### Execution

```bash
./floyd_warshall "assignment_02/02_Floyd_Warshall/tests/fw_10.txt"
```

### Test Cases and Result Table

| Test Case | Vertices | Runtime |
|---|---|---|
| fw_10.txt | 10 | 0.00 ms |
| fw_100.txt | 100 | 0.00 ms |
| fw_500.txt | 500 | 1.00 ms |
| fw_1000.txt | 1,000 | 2.44 ms |
| fw_2000.txt | 2,000 | 5.12 ms |

The runtimes are machine-dependent and may vary between executions.

### Complexity

**Time Complexity:** O(V³)
**Space Complexity:** O(V²)

### References

* Course assignment specification
* Floyd-Warshall all-pairs shortest-path algorithm

---

# Assignment 03 – Kruskal and Prim

## Assignment Mode

Individual implementation.

## Objective

The assignment implements two algorithms for finding a Minimum Spanning Tree (MST) of a weighted undirected graph:

* Kruskal's algorithm
* Prim's algorithm

Both algorithms use the CSR graph representation from Assignment 01.

The CSR implementation from Assignment 01 is reused rather than copied into Assignment 03.

---

## Assignment 03 – Kruskal

### Objective

Kruskal's algorithm constructs a Minimum Spanning Tree by considering graph edges in increasing order of weight.

An edge is added to the MST if it does not create a cycle.

A disjoint-set / union-find structure is used to detect whether adding an edge would form a cycle.

### Algorithm / Approach

The edges are sorted according to their weights.

Starting with an empty MST:

1. Select the smallest remaining edge.
2. Check whether its endpoints belong to different components.
3. If they are different, add the edge to the MST.
4. Merge the two components.
5. Continue until `V - 1` edges are selected.

For a connected graph with V vertices, the MST contains `V - 1` edges.

### Input Format

The test files contain weighted undirected graphs in adjacency-list form.

The first line contains:

```
V E
```

where `V` = number of vertices and `E` = number of undirected edges.

Each following line contains the vertex number, its degree, and the neighboring vertices with their edge weights.

The Assignment 03 test cases use integer edge weights.

Since the graph is undirected, each edge occurs in the adjacency lists of both endpoints.

### File Structure

```
assignment_03/01_Kruskal/
├── src/
│   ├── kruskal.cpp
│   └── kruskal.h
└── driver/
    └── driver_kruskal.cpp
```

The CSR implementation is reused from `assignment_01/02_CSR_Graph/`.

### Compilation

```bash
g++ -std=c++17 -O2 \
  assignment_01/02_CSR_Graph/src/csr_graph.cpp \
  assignment_03/01_Kruskal/src/kruskal.cpp \
  assignment_03/01_Kruskal/driver/driver_kruskal.cpp \
  -o kruskal
```

### Execution

```bash
./kruskal assignment_03/tests/mst_10.txt
```

### Test Cases and Result Table

| Test Case | Vertices | MST Edges | Total Weight | Runtime |
|---|---|---|---|---|
| mst_10.txt | 10 | 9 | 27.00 | 0.00 ms |
| mst_100.txt | 100 | 99 | 2160.00 | 0.02 ms |
| mst_10000.txt | 10,000 | 9,999 | 200115.00 | 1.88 ms |
| mst_50000.txt | 50,000 | 49,999 | 1013030.00 | 10.08 ms |
| mst_100000.txt | 100,000 | 99,999 | 2023168.00 | 20.09 ms |

The graphs are connected, so each MST contains `V - 1` edges.

### Complexity

**Time Complexity:** O(E log E)
**Space Complexity:** O(V + E)

The main cost is sorting the graph edges.

### References

* Course assignment specification
* Kruskal's minimum spanning tree algorithm
* Disjoint-set / Union-Find data structure

---

## Assignment 03 – Prim

### Objective

Prim's algorithm constructs a Minimum Spanning Tree by starting from a vertex and repeatedly adding the minimum-weight edge that connects the current MST to an unvisited vertex.

### Algorithm / Approach

Starting from a selected vertex:

1. Mark the starting vertex as part of the MST.
2. Find the minimum-weight edge connecting the MST to an unvisited vertex.
3. Add that vertex and edge to the MST.
4. Update the minimum connection cost of neighboring vertices.
5. Repeat until all vertices are included.

For a connected graph with V vertices, the MST contains `V - 1` edges.

The implementation uses the CSR representation from Assignment 01.

### Input Format

The same weighted undirected adjacency-list input is used by Kruskal and Prim.

The Assignment 03 test cases use integer edge weights.

### File Structure

```
assignment_03/02_Prim/
├── src/
│   ├── prim.cpp
│   └── prim.h
└── driver/
    └── driver_prim.cpp
```

The CSR implementation is reused from `assignment_01/02_CSR_Graph/`.

### Compilation

```bash
g++ -std=c++17 -O2 \
  assignment_01/02_CSR_Graph/src/csr_graph.cpp \
  assignment_03/02_Prim/src/prim.cpp \
  assignment_03/02_Prim/driver/driver_prim.cpp \
  -o prim
```

### Execution

```bash
./prim assignment_03/tests/mst_10.txt
```

### Test Cases and Result Table

| Test Case | Vertices | MST Edges | Total Weight | Runtime |
|---|---|---|---|---|
| mst_10.txt | 10 | 9 | 27.00 | 0.00 ms |
| mst_100.txt | 100 | 99 | 2160.00 | 0.03 ms |
| mst_10000.txt | 10,000 | 9,999 | 200115.00 | 2.77 ms |
| mst_50000.txt | 50,000 | 49,999 | 1013030.00 | 15.72 ms |
| mst_100000.txt | 100,000 | 99,999 | 2023168.00 | 43.51 ms |

The MST weights produced by Prim and Kruskal are identical for every test case.

### Complexity

For the priority-queue implementation:

**Time Complexity:** O(E log V)
**Space Complexity:** O(V + E)

### References

* Course assignment specification
* Prim's minimum spanning tree algorithm
* Priority queue based graph traversal

---

## Assignment 03 – Comparison of MST Algorithms

Both Kruskal's and Prim's algorithms produced the same MST for all test cases.

| Test Case | Vertices | Kruskal Time | Prim Time | MST Weight |
|---|---|---|---|---|
| mst_10.txt | 10 | 0.00 ms | 0.00 ms | 27.00 |
| mst_100.txt | 100 | 0.02 ms | 0.03 ms | 2160.00 |
| mst_10000.txt | 10,000 | 1.88 ms | 2.77 ms | 200115.00 |
| mst_50000.txt | 50,000 | 10.08 ms | 15.72 ms | 1013030.00 |
| mst_100000.txt | 100,000 | 20.09 ms | 43.51 ms | 2023168.00 |

For every test case, MST edges = `V - 1`.

The total MST weight obtained by both algorithms is the same for every test case.

The measured runtimes show that Kruskal was faster than Prim for the tested graph sizes in this implementation and environment.

Runtime measurements are machine-dependent and may vary between executions.

---

# Overall Compilation and Execution Summary

All commands below are executed from the repository root in Ubuntu / WSL.

## Common Wrapper

Compile:

```bash
g++ -std=c++17 -O2 common_wrapper/wrapper.cpp -o wrapper
```

Run:

```bash
./wrapper
```

The wrapper provides the following menu:

```
========================================
          CS509 COMMON WRAPPER
========================================

Select Assignment:
1. Assignment 1
2. Assignment 2
3. Assignment 3
0. Exit
```

After selecting an assignment, the available algorithms are displayed.

For Assignment 3:

```
Select Algorithm:
1. Kruskal
2. Prim
0. Back
```

The available test cases are then displayed for selection.

## Direct Compilation and Execution - Individual
Run the commands from the repository root. In the execution command(2nd), replace the test-case filename with the desired test case file you want to run.

### GEMM

```bash
g++ -std=c++17 -O2 \
  assignment_01/01_GEMM/src/gemm.cpp \
  assignment_01/01_GEMM/driver/driver_gemm.cpp \
  -o gemm

./gemm assignment_01/01_GEMM/tests/gemm_test_01.txt
```

### CSR

```bash
g++ -std=c++17 -O2 \
  assignment_01/02_CSR_Graph/src/csr_graph.cpp \
  assignment_01/02_CSR_Graph/driver/driver_csr.cpp \
  -o csr

./csr assignment_01/02_CSR_Graph/tests/csr_10.txt
```

### Bellman-Ford

```bash
g++ -std=c++17 -O2 \
  assignment_01/02_CSR_Graph/src/csr_graph.cpp \
  assignment_02/01_Bellman_Ford/src/bellman_ford.cpp \
  assignment_02/01_Bellman_Ford/driver/driver_bellman_ford.cpp \
  -o bellman_ford

./bellman_ford assignment_02/01_Bellman_Ford/tests/bf_10.txt 0
```

### Floyd-Warshall

```bash
g++ -std=c++17 -O2 \
  assignment_02/02_Floyd_Warshall/src/floyd_warshall.cpp \
  assignment_02/02_Floyd_Warshall/driver/driver_floyd_warshall.cpp \
  -o floyd_warshall

./floyd_warshall assignment_02/02_Floyd_Warshall/tests/fw_10.txt
```

### Kruskal

```bash
g++ -std=c++17 -O2 \
  assignment_01/02_CSR_Graph/src/csr_graph.cpp \
  assignment_03/01_Kruskal/src/kruskal.cpp \
  assignment_03/01_Kruskal/driver/driver_kruskal.cpp \
  -o kruskal

./kruskal assignment_03/tests/mst_10.txt
```

### Prim

```bash
g++ -std=c++17 -O2 \
  assignment_01/02_CSR_Graph/src/csr_graph.cpp \
  assignment_03/02_Prim/src/prim.cpp \
  assignment_03/02_Prim/driver/driver_prim.cpp \
  -o prim

./prim assignment_03/tests/mst_10.txt
```

---

# Notes

* All algorithms were implemented in C++17.
* Compilation was performed using GNU G++ on Ubuntu / WSL.
* `-O2` optimization was used for benchmark compilation.
* Runtime measurements are machine-dependent.
* Input loading and CSR preprocessing are kept separate from algorithm execution where applicable.
* The CSR implementation from Assignment 01 is reused by the algorithms that require CSR.
* Assignment 03 uses weighted undirected graphs.
* Assignment 03 test cases use integer edge weights.
* Kruskal's and Prim's algorithms both produce a Minimum Spanning Tree for connected graphs.
* For all Assignment 03 test cases, both algorithms produced `V - 1` MST edges and identical total MST weights.
* The common wrapper provides a unified compilation and execution interface for all assignments.
* The common wrapper allows the user to select the assignment, algorithm, and test case before execution.