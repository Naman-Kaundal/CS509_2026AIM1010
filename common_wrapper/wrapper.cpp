#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

bool fileExists(const std::string& path)
{
std::ifstream file(path);
return file.good();
}

int runCommand(const std::string& command)
{
std::cout << "\n> " << command << "\n\n";
return std::system(command.c_str());
}

bool compileGEMM()
{
return runCommand(
"g++ -std=c++17 -O2 -Wall "
"./assignment_01/01_GEMM/src/gemm.cpp "
"./assignment_01/01_GEMM/driver/driver_gemm.cpp "
"-o .\\gemm.exe"
) == 0;
}

bool compileCSR()
{
return runCommand(
"g++ -std=c++17 -O2 -Wall "
"./assignment_01/02_CSR_Graph/src/csr_graph.cpp "
"./assignment_01/02_CSR_Graph/driver/driver_csr.cpp "
"-o .\\csr.exe"
) == 0;
}

bool compileBellmanFord()
{
return runCommand(
"g++ -std=c++17 -O2 -Wall "
"./assignment_01/02_CSR_Graph/src/csr_graph.cpp "
"./assignment_02/01_Bellman_Ford/src/bellman_ford.cpp "
"./assignment_02/01_Bellman_Ford/driver/driver_bellman_ford.cpp "
"-o .\\bellman_ford.exe"
) == 0;
}

bool compileFloydWarshall()
{
return runCommand(
"g++ -std=c++17 -O2 -Wall "
"./assignment_02/02_Floyd_Warshall/src/floyd_warshall.cpp "
"./assignment_02/02_Floyd_Warshall/driver/driver_floyd_warshall.cpp "
"-o .\\floyd_warshall.exe"
) == 0;
}

bool compileAll()
{
bool ok = true;

std::cout << "\n========== COMPILING GEMM ==========\n";
if (!compileGEMM())
    ok = false;

std::cout << "\n========== COMPILING CSR ==========\n";
if (!compileCSR())
    ok = false;

std::cout << "\n========== COMPILING BELLMAN-FORD ==========\n";
if (!compileBellmanFord())
    ok = false;

std::cout << "\n========== COMPILING FLOYD-WARSHALL ==========\n";
if (!compileFloydWarshall())
    ok = false;

return ok;

}

void runGEMM()
{
std::string testFile;

std::cout << "Enter GEMM test-file path: ";
std::getline(std::cin, testFile);

if (!fileExists(testFile))
{
    std::cerr << "Error: test file not found.\n";
    return;
}

if (!fileExists(".\\gemm.exe"))
{
    std::cout << "GEMM executable not found. Compiling...\n";

    if (!compileGEMM())
    {
        std::cerr << "GEMM compilation failed.\n";
        return;
    }
}

runCommand(".\\gemm.exe \"" + testFile + "\"");

}

void runCSR()
{
std::string testFile;

std::cout << "Enter CSR test-file path: ";
std::getline(std::cin, testFile);

if (!fileExists(testFile))
{
    std::cerr << "Error: test file not found.\n";
    return;
}

if (!fileExists(".\\csr.exe"))
{
    std::cout << "CSR executable not found. Compiling...\n";

    if (!compileCSR())
    {
        std::cerr << "CSR compilation failed.\n";
        return;
    }
}

runCommand(".\\csr.exe \"" + testFile + "\"");

}

void runBellmanFord()
{
std::string testFile;
std::string source;

std::cout << "Enter Bellman-Ford test-file path: ";
std::getline(std::cin, testFile);

if (!fileExists(testFile))
{
    std::cerr << "Error: test file not found.\n";
    return;
}

std::cout << "Enter source vertex: ";
std::getline(std::cin, source);

if (!fileExists(".\\bellman_ford.exe"))
{
    std::cout << "Bellman-Ford executable not found. Compiling...\n";

    if (!compileBellmanFord())
    {
        std::cerr << "Bellman-Ford compilation failed.\n";
        return;
    }
}

runCommand(
    ".\\bellman_ford.exe \"" +
    testFile +
    "\" " +
    source
);

}

void runFloydWarshall()
{
std::string testFile;

std::cout << "Enter Floyd-Warshall test-file path: ";
std::getline(std::cin, testFile);

if (!fileExists(testFile))
{
    std::cerr << "Error: test file not found.\n";
    return;
}

if (!fileExists(".\\floyd_warshall.exe"))
{
    std::cout << "Floyd-Warshall executable not found. Compiling...\n";

    if (!compileFloydWarshall())
    {
        std::cerr << "Floyd-Warshall compilation failed.\n";
        return;
    }
}

runCommand(
    ".\\floyd_warshall.exe \"" +
    testFile +
    "\""
);

}

int main()
{
while (true)
{
std::cout
<< "\n========================================\n"
<< "        CS509 ASSIGNMENT WRAPPER\n"
<< "========================================\n"
<< "1. Compile all assignments\n"
<< "2. Run GEMM\n"
<< "3. Run CSR Graph\n"
<< "4. Run Bellman-Ford\n"
<< "5. Run Floyd-Warshall\n"
<< "0. Exit\n"
<< "========================================\n"
<< "Enter choice: ";

    std::string choice;
    std::getline(std::cin, choice);

    if (choice == "0")
    {
        std::cout << "Exiting wrapper.\n";
        break;
    }

    if (choice == "1")
    {
        if (compileAll())
        {
            std::cout
                << "\nAll assignments compiled successfully.\n";
        }
        else
        {
            std::cerr
                << "\nOne or more compilations failed.\n";
        }
    }
    else if (choice == "2")
    {
        runGEMM();
    }
    else if (choice == "3")
    {
        runCSR();
    }
    else if (choice == "4")
    {
        runBellmanFord();
    }
    else if (choice == "5")
    {
        runFloydWarshall();
    }
    else
    {
        std::cerr
            << "Invalid choice. Please select 0-5.\n";
    }
}

return 0;

}
