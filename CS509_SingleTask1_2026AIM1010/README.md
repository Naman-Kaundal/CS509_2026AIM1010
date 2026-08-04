# CS509 Laboratory Repository

## Repository Overview
This repository contains the **Individual (Single Task)** assignment work for CS509
(First-Year M.Tech CSE, 2026). It covers **Assignment 1 - Single Task**, split into two
parts as required by the assignment specification:

1. **Matrix Multiplication (GEMM)** - Simple implementation and Blocking implementation,
   kept in **separate source/driver files** so each can be built, run, and timed
   independently while still reading the exact same input file for a fair comparison.
2. **CSR (Compressed Sparse Row) Graph** - adjacency-list-to-CSR conversion helper, with
   test cases for **all five required graph sizes** (10, 100, 10,000, 50,000, 100,000
   vertices).

The Buddy tasks (BFS, DFS, SSSP) are out of scope for this repository - they belong to the
paired repository (`CS509_<2026CSM1022>_<2026AIM1010>`) per the lab guidelines.

## Student Details
- **Name:** Naman Kaundal
- **Entry Number:** `ENTRYNUMBER` (placeholder - replace with actual entry number)
- **Mode:** Individual (Single Task)

## Language and Environment
- **Language:** C++ (C++17)
- **Compiler:** g++ (GCC) 13.3.0, tested with `-std=c++17 -O2 -Wall`
- **OS used for measurements:** Linux x86_64 (container environment); replace with your
  own machine's OS/CPU details before submission.
- **Build tool:** plain `g++` invocations (see Compilation sections below); no external
  build system is required.

## Directory Structure
```
CS509_ENTRYNUMBER/
|-- README.md                              <- this file
|-- common_wrapper/
|   `-- wrapper.cpp                        <- repository-level menu (build/run any assignment)
|-- assignment_01/
|   |-- 01_Matrix_Multiplication/          <- GEMM (Single Task, part 1)
|   |   |-- src/
|   |   |   |-- gemm_simple.h/.cpp         <- GEMM Simple  (separate file, as required)
|   |   |   |-- gemm_blocking.h/.cpp       <- GEMM Blocking (separate file, as required)
|   |   |   `-- gemm_io.h                  <- shared read/print helpers (untimed I/O only)
|   |   |-- driver/
|   |   |   |-- driver_gemm_simple.cpp     <- runs + times GEMM Simple only
|   |   |   `-- driver_gemm_blocking.cpp   <- runs + times GEMM Blocking only
|   |   |-- tests/
|   |   |   `-- gemm_test_01.txt ... gemm_test_06.txt
|   |   `-- outputs/                       <- optional saved run outputs
|   `-- 02_CSR_Graph/                      <- CSR (Single Task, part 2)
|       |-- src/
|       |   `-- csr.h / csr.cpp            <- adjacency-list -> CSR conversion helper
|       |-- driver/
|       |   `-- driver_csr.cpp             <- reads graph, converts to CSR, times, prints
|       |-- tests/
|       |   `-- csr_10.txt, csr_100.txt, csr_10000.txt, csr_50000.txt, csr_100000.txt
|       `-- outputs/                       <- optional saved run outputs
`-- tools/
    |-- generate_gemm.py                   <- generates random GEMM test files of any size
    `-- generate_graph.py                  <- generates random graph test files of any size
```

## Common Wrapper: Build and Usage
The common wrapper is the single repository-level entry point. It does **not** replace the
per-assignment drivers - it compiles and invokes them.

**Build:**
```bash
cd common_wrapper
g++ -O2 -std=c++17 -Wall wrapper.cpp -o wrapper
```

**Run:**
```bash
./wrapper
```

You will see a menu:
```
[1] GEMM - Simple              (assignment_01/01_Matrix_Multiplication)
[2] GEMM - Blocking            (assignment_01/01_Matrix_Multiplication)
[3] CSR Graph Conversion       (assignment_01/02_CSR_Graph)
------------------------------------------------
[L] List available algorithms
[C] Compile a selected assignment
[R] Run one test file for a selected assignment
[A] Run ALL test files for a selected assignment
[B] Compile and run ALL submitted algorithms
[Q] Quit
```
- `C` then a number compiles that driver.
- `R` lets you pick one test file from that algorithm's `tests/` folder to run.
- `A` runs every test file belonging to the selected algorithm.
- `B` compiles and runs every registered algorithm against all of its test files in one go.
- Clear error messages are printed for missing executables, missing test files, or invalid
  menu selections.

## General Conventions
- **Test files:** one test case per file, named with a clear prefix
  (`gemm_test_NN.txt`, `csr_<V>.txt`).
- **Timing:** every driver starts a `std::chrono::high_resolution_clock` timer immediately
  before calling the algorithm and stops it immediately after. File I/O, parsing, and
  result printing are always outside the timed region. Reported unit is **milliseconds
  (ms)**.
- **CSR conversion:** treated strictly as preprocessing. Its own execution time is reported
  by `driver_csr` for reference/demonstration of the helper function; per the assignment
  spec this conversion time must never be counted as part of a graph algorithm's runtime
  (relevant once BFS/DFS/SSSP are implemented in the Buddy assignment).
- **Outputs:** each driver prints the result (matrix or CSR arrays) followed by
  `Execution time: <value> ms`.

---

## Assignment 01 - Single Task (Individual)

### Assignment Mode
Individual (Single task, per CS509 Assignment 1 instructions).

### Objective
1. Implement General Matrix Multiplication (GEMM) two ways - a direct/simple triple
   nested-loop version and a blocking (tiled) version, **kept in separate files** - and
   confirm both produce identical results while comparing their execution times.
2. Implement a reusable helper function that converts a graph's adjacency-list
   representation into Compressed Sparse Row (CSR) format, tested on all five required
   graph sizes (10, 100, 10,000, 50,000, 100,000 vertices).

---

### Part 1: Matrix Multiplication (`01_Matrix_Multiplication/`)

#### Algorithm / Approach
**GEMM Simple** (`gemm_simple.cpp` -> `gemm_simple()`): standard triple-nested loop -
`C[i][j] = sum_k A[i][k] * B[k][j]`, iterating `i`, then `j`, then `k`.

**GEMM Blocking** (`gemm_blocking.cpp` -> `gemm_blocking()`): the `M`, `N`, `K` loops are
each split into blocks of size `block_size` (default 32, configurable via CLI argument).
Each block of `C` is accumulated using the corresponding blocks of `A` and `B`, so a block
stays resident in cache while it is reused across the inner block computation.
Mathematically it computes exactly the same sum as the simple version, just in a different
iteration order.

The two implementations live in **separate `.h`/`.cpp` files and are run by separate
driver programs**, so each can be compiled, run, and timed on its own. Both drivers reuse
the same header-only `gemm_io.h` for reading the input file and printing the result matrix,
so both implementations are always evaluated on identical input handling - only the
algorithm itself differs (see section 5.1 of the assignment: "use the same input file for
both implementations").

#### Input Format
`gemm_test_NN.txt`:
```
M K N
<A row 0>
...
<A row M-1>
<B row 0>
...
<B row K-1>
```
`A` is `M x K`, `B` is `K x N`, result `C` is `M x N`.

**Assumptions/constraints:** all matrix values are integers (stored as `long long` to avoid
overflow on larger test cases); each row is on its own line.

#### File Structure
```
01_Matrix_Multiplication/
|-- src/
|   |-- gemm_simple.h,   gemm_simple.cpp      - GEMM Simple (separate file)
|   |-- gemm_blocking.h, gemm_blocking.cpp    - GEMM Blocking (separate file)
|   `-- gemm_io.h                             - shared file-reading / printing (untimed)
|-- driver/
|   |-- driver_gemm_simple.cpp                - runs + times GEMM Simple only
|   `-- driver_gemm_blocking.cpp              - runs + times GEMM Blocking only
`-- tests/                                    - gemm_test_01.txt ... gemm_test_06.txt
```

#### Compilation
```bash
# GEMM Simple
g++ -O2 -std=c++17 -Wall assignment_01/01_Matrix_Multiplication/src/gemm_simple.cpp assignment_01/01_Matrix_Multiplication/driver/driver_gemm_simple.cpp -o driver_gemm_simple.exe

.\driver_gemm_simple.exe assignment_01\01_Matrix_Multiplication\tests\gemm_test_01.txt


# GEMM Blocking


#### Execution
g++ -O2 -std=c++17 -Wall assignment_01/01_Matrix_Multiplication/src/gemm_blocking.cpp assignment_01/01_Matrix_Multiplication/driver/driver_gemm_blocking.cpp -o driver_gemm_blocking.exe

(Both are also compiled automatically by `common_wrapper/wrapper.cpp`.)

#### Execution
```bash
# GEMM Simple:   ./driver_gemm_simple <input_file>
.\driver_gemm_simple.exe assignment_01\01_Matrix_Multiplication\tests\gemm_test_01.txt

# GEMM Blocking: ./driver_gemm_blocking <input_file> [block_size]
.\driver_gemm_blocking.exe assignment_01\01_Matrix_Multiplication\tests\gemm_test_01.txt 32
```

#### Test Cases and Result Table
All six test files were generated (`gemm_test_03`-`06` via `tools/generate_gemm.py` with a
fixed seed, for reproducibility) and every case was run through both drivers; `Simple` and
`Blocking` outputs were diffed and matched exactly on every test.

| Test File | Input Type / Size | Expected Output | Actual Output | Simple Time | Blocking Time | Block Size | Status |
|---|---|---|---|---|---|---|---|
| gemm_test_01.txt | 2x3 and 3x2 (assignment PDF example) | C = [[58,64],[139,154]] | C = [[58,64],[139,154]] | 0.000889 ms | 0.001754 ms | 32 | Pass |
| gemm_test_02.txt | 3x3 and 3x3 (hand-crafted, with negatives) | C = [[3,-2,5],[6,2,1],[10,4,2]] | C = [[3,-2,5],[6,2,1],[10,4,2]] | 0.000725 ms | 0.000791 ms | 32 | Pass |
| gemm_test_03.txt | 100x150 and 150x80 (random, seed=7) | Result matrix (100x80) | Matches Simple output | 6.469 ms | 0.833 ms | 32 | Pass |
| gemm_test_04.txt | 200x200 and 200x200 (random, seed=42) | Result matrix (200x200) | Matches Simple output | 7.178 ms | 5.663 ms | 32 | Pass |
| gemm_test_05.txt | 500x500 and 500x500 (random, seed=123) | Result matrix (500x500) | Matches Simple output | 186.404 ms | 91.872 ms | 32 | Pass |
| gemm_test_06.txt | 600x300 and 300x400 (random, seed=99) | Result matrix (600x400) | Matches Simple output | 82.436 ms | 56.512 ms | 32 | Pass |

*Timings above were measured in the development container (1 vCPU); re-run on your own
machine and record fresh numbers with your machine's specs (see Language and Environment
section). Small (test_01/02) timings are noisy at sub-microsecond scale - run multiple
times and average if more precision is needed (assignment section 8).*

#### Complexity
- **GEMM Simple:** Time O(M·K·N), Space O(M·N) for the output (plus O(M·K + K·N) input).
- **GEMM Blocking:** Time O(M·K·N) (same asymptotic complexity; improves cache locality,
  not asymptotic complexity), Space O(M·N). Blocking's benefit grows with matrix size, as
  seen in the timing table above (test_03/05/06 show a larger speed-up than the small
  test_01/02 cases where overhead dominates).

---

### Part 2: CSR Graph (`02_CSR_Graph/`)

#### Algorithm / Approach
**CSR Conversion** (`convertAdjListToCSR` in `csr.cpp`): given `V` and an adjacency list
(a `vector` of per-vertex neighbour lists), it:
1. Computes `row_ptr` via a prefix sum of vertex degrees (`row_ptr[u+1] = row_ptr[u] +
   degree(u)`).
2. Allocates `col_idx` and `values` of total size `row_ptr[V]`.
3. Uses a per-row write cursor (initialised from `row_ptr`) to place each neighbour /
   weight into its correct slot in a single linear pass.

This runs in O(V + E) time and is treated purely as a preprocessing helper - its own
timing is reported separately here for demonstration only, and must never be added to a
graph algorithm's reported runtime once BFS/DFS/SSSP are implemented (Buddy assignment).

#### Input Format
`csr_<V>.txt`, unweighted adjacency-list format (assignment section 6.1):
```
V E
u0 degree n1 n2 ...
...
u(V-1) degree n1 n2 ...
SOURCE s
```
The driver also supports the weighted variant, `u degree n1 w1 n2 w2 ...`, via the
`--weighted` flag, for reuse when SSSP is implemented in the Buddy assignment.

**Assumptions/constraints:** vertices are numbered `0` to `V-1`; graphs are undirected, so
each edge appears in both endpoints' adjacency lists (CSR entry count = 2E); all test
graphs are randomly generated but kept connected (`tools/generate_graph.py` builds a random
spanning structure first, then adds extra random edges up to the target average degree).

#### File Structure
```
02_CSR_Graph/
|-- src/csr.h,  csr.cpp      - Adjacency-list -> CSR helper
|-- driver/driver_csr.cpp    - CSR driver (reads, converts, times, prints)
`-- tests/                   - csr_10.txt, csr_100.txt, csr_10000.txt, csr_50000.txt, csr_100000.txt
```

#### Compilation
```bash
g++ -O2 -std=c++17 -Wall assignment_01/02_CSR_Graph/src/csr.cpp assignment_01/02_CSR_Graph/driver/driver_csr.cpp -o driver_csr.exe

```
(Also compiled automatically by `common_wrapper/wrapper.cpp`.)

#### Execution
```bash
.\driver_csr.exe assignment_01\02_CSR_Graph\tests\csr_10.txt
```

#### Test Cases and Result Table
All **five required graph sizes** from the assignment (section 4.2) are included as
committed test files (generated via `tools/generate_graph.py`, average degree 4,
seed=42, for reproducibility):

| Mode | Test File | Input Type | Input Size | Expected Output | Actual Output | Algorithm Time |
|---|---|---|---|---|---|---|
| Single | csr_10.txt | Unweighted adjacency list -> CSR | V = 10, E = 20 | Valid CSR arrays, `col_idx` size = 2E = 40 | row_ptr/col_idx generated, size 40 | 0.0012 ms |
| Single | csr_100.txt | Unweighted adjacency list -> CSR | V = 100, E = 200 | `col_idx` size = 2E = 400 | row_ptr/col_idx generated, size 400 | 0.0043 ms |
| Single | csr_10000.txt | Unweighted adjacency list -> CSR | V = 10000, E = 20000 | `col_idx` size = 2E = 40000 | row_ptr/col_idx generated, size 40000 | 0.397 ms |
| Single | csr_50000.txt | Unweighted adjacency list -> CSR | V = 50000, E = 100000 | `col_idx` size = 2E = 200000 | row_ptr/col_idx generated, size 200000 | 1.990 ms |
| Single | csr_100000.txt | Unweighted adjacency list -> CSR | V = 100000, E = 200000 | `col_idx` size = 2E = 400000 | row_ptr/col_idx generated, size 400000 | 4.188 ms |

*Timings above were measured in the development container (1 vCPU); re-run on your own
machine and record fresh numbers with your machine's specs. Conversion time scales
linearly with V + E, as expected for the O(V + E) algorithm.*

#### Complexity
- **CSR Conversion:** Time O(V + E), Space O(V + E) for `row_ptr`, `col_idx`, `values`.