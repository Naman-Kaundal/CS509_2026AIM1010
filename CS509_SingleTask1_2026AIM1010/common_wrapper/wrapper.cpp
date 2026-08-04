// wrapper.cpp
// CS509 Common Wrapper
//
// Repository-level menu that lets the user:
//   1. List available algorithms/assignments.
//   2. Select and compile one assignment's driver.
//   3. Run one selected test file for that assignment.
//   4. Run all test files for that assignment.
//   5. Compile and/or run all submitted algorithms.
//
// The wrapper only invokes each assignment's dedicated driver; it does
// not reimplement the algorithms itself. Update `assignments[]` below
// as new assignments (assignment_02, assignment_03, ...) are added.
//
// Build:
//   g++ -O2 -std=c++17 -Wall wrapper.cpp -o wrapper
// Run:
//   ./wrapper

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <cstdlib>
#include <algorithm>

namespace fs = std::filesystem;

struct AssignmentEntry {
    std::string name;        // display name
    std::string dir;         // path relative to repo root, e.g. "assignment_01/01_Matrix_Multiplication"
    std::string driverName;  // e.g. "driver_gemm_simple"
    std::string sourceFiles; // extra .cpp files (relative to dir) needed to link the driver
    std::string testsPrefix; // filename prefix used to find its test files (e.g. "gemm_")
    std::string extraArgs;   // extra CLI args appended after the test-file path
};

// ---- Registry of available assignment drivers -----------------------
// Single Task (Assignment 1): GEMM Simple, GEMM Blocking, CSR Graph Conversion.
static std::vector<AssignmentEntry> assignments = {
    {"GEMM - Simple", "assignment_01/01_Matrix_Multiplication", "driver_gemm_simple",
     "src/gemm_simple.cpp driver/driver_gemm_simple.cpp", "gemm_", ""},
    {"GEMM - Blocking", "assignment_01/01_Matrix_Multiplication", "driver_gemm_blocking",
     "src/gemm_blocking.cpp driver/driver_gemm_blocking.cpp", "gemm_", "32"},
    {"CSR Graph Conversion", "assignment_01/02_CSR_Graph", "driver_csr",
     "src/csr.cpp driver/driver_csr.cpp", "csr_", ""},
};

static std::string repoRoot() {
    // Assumes the wrapper binary is run from common_wrapper/ or the repo root.
    if (fs::exists("assignment_01")) return ".";
    if (fs::exists("../assignment_01")) return "..";
    return ".";
}

static std::string buildDir(const AssignmentEntry &a) {
    return repoRoot() + "/" + a.dir;
}

static std::string binaryPath(const AssignmentEntry &a) {
    return "/tmp/cs509_" + a.driverName;
}

static bool compileAssignment(const AssignmentEntry &a) {
    std::string dir = buildDir(a);
    std::string cmd = "g++ -O2 -std=c++17 -Wall " + a.sourceFiles +
                       " -o " + binaryPath(a);
    std::cout << "[compile] (cd " << dir << " && " << cmd << ")\n";
    std::string fullCmd = "cd " + dir + " && " + cmd;
    int rc = std::system(fullCmd.c_str());
    if (rc != 0) {
        std::cerr << "Error: compilation failed for '" << a.name << "'.\n";
        return false;
    }
    std::cout << "Compilation succeeded: " << binaryPath(a) << "\n";
    return true;
}

static std::vector<std::string> listTestFiles(const AssignmentEntry &a) {
    std::vector<std::string> files;
    std::string testsDir = buildDir(a) + "/tests";
    if (!fs::exists(testsDir)) return files;
    for (const auto &entry : fs::directory_iterator(testsDir)) {
        if (!entry.is_regular_file()) continue;
        std::string fname = entry.path().filename().string();
        if (fname.rfind(a.testsPrefix, 0) == 0) {
            files.push_back(entry.path().string());
        }
    }
    std::sort(files.begin(), files.end());
    return files;
}

static bool runOnTestFile(const AssignmentEntry &a, const std::string &testFile) {
    std::string bin = binaryPath(a);
    if (!fs::exists(bin)) {
        std::cerr << "Error: executable for '" << a.name
                  << "' not found. Compile it first (option 2).\n";
        return false;
    }
    if (!fs::exists(testFile)) {
        std::cerr << "Error: test file '" << testFile << "' not found.\n";
        return false;
    }
    std::string cmd = bin + " " + testFile + " " + a.extraArgs;
    std::cout << "\n----- Running: " << cmd << " -----\n";
    int rc = std::system(cmd.c_str());
    if (rc != 0) {
        std::cerr << "Note: driver exited with non-zero status (" << rc << ").\n";
    }
    return true;
}

static void printMenu() {
    std::cout << "\n============ CS509 Common Wrapper ============\n";
    std::cout << "Available algorithms/assignments:\n";
    for (size_t i = 0; i < assignments.size(); ++i) {
        std::cout << "  [" << (i + 1) << "] " << assignments[i].name
                  << "  (" << assignments[i].dir << ")\n";
    }
    std::cout << "------------------------------------------------\n";
    std::cout << "  [L] List available algorithms\n";
    std::cout << "  [C] Compile a selected assignment\n";
    std::cout << "  [R] Run one test file for a selected assignment\n";
    std::cout << "  [A] Run ALL test files for a selected assignment\n";
    std::cout << "  [B] Compile and run ALL submitted algorithms\n";
    std::cout << "  [Q] Quit\n";
    std::cout << "================================================\n";
    std::cout << "Choice: ";
}

static int selectAssignment() {
    std::cout << "Select assignment number: ";
    int idx;
    if (!(std::cin >> idx) || idx < 1 || idx > static_cast<int>(assignments.size())) {
        std::cerr << "Error: invalid selection.\n";
        return -1;
    }
    return idx - 1;
}

int main() {
    std::cout << "CS509 Common Wrapper - repository-level menu\n";
    std::cout << "(Invokes each assignment's own dedicated driver; does not replace it.)\n";

    std::string choice;
    while (true) {
        printMenu();
        if (!(std::cin >> choice)) break;

        if (choice == "L" || choice == "l") {
            for (size_t i = 0; i < assignments.size(); ++i) {
                std::cout << "  [" << (i + 1) << "] " << assignments[i].name << "\n";
            }
        } else if (choice == "C" || choice == "c") {
            int idx = selectAssignment();
            if (idx >= 0) compileAssignment(assignments[idx]);
        } else if (choice == "R" || choice == "r") {
            int idx = selectAssignment();
            if (idx < 0) continue;
            auto files = listTestFiles(assignments[idx]);
            if (files.empty()) {
                std::cerr << "Error: no test files found for '" << assignments[idx].name << "'.\n";
                continue;
            }
            std::cout << "Available test files:\n";
            for (size_t i = 0; i < files.size(); ++i) {
                std::cout << "  [" << (i + 1) << "] " << files[i] << "\n";
            }
            std::cout << "Select test file number: ";
            int tIdx;
            if (!(std::cin >> tIdx) || tIdx < 1 || tIdx > static_cast<int>(files.size())) {
                std::cerr << "Error: invalid selection.\n";
                continue;
            }
            runOnTestFile(assignments[idx], files[tIdx - 1]);
        } else if (choice == "A" || choice == "a") {
            int idx = selectAssignment();
            if (idx < 0) continue;
            auto files = listTestFiles(assignments[idx]);
            if (files.empty()) {
                std::cerr << "Error: no test files found for '" << assignments[idx].name << "'.\n";
                continue;
            }
            for (const auto &f : files) runOnTestFile(assignments[idx], f);
        } else if (choice == "B" || choice == "b") {
            for (auto &a : assignments) {
                if (!compileAssignment(a)) continue;
                auto files = listTestFiles(a);
                if (files.empty()) {
                    std::cerr << "Warning: no test files found for '" << a.name << "'.\n";
                    continue;
                }
                for (const auto &f : files) runOnTestFile(a, f);
            }
        } else if (choice == "Q" || choice == "q") {
            std::cout << "Exiting.\n";
            break;
        } else {
            std::cerr << "Error: unrecognized option '" << choice << "'.\n";
        }
    }
    return 0;
}
