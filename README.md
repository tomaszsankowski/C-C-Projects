# C/C++ Projects Collection

This repository serves as an archive for my C and C++ projects, ranging from low-level data structure implementations to complex simulations and distributed systems. The projects focus on performance, memory management, and algorithmic efficiency.

## Repository Structure

### 🧠 Algorithms & Data Structures

- **[CSS](./CSS/)**: A specialized CSS Parser featuring custom data structure implementations designed for efficient style rule management.
- **[ShortestPathFinder](./ShortestPathFinder/)**: Implementation of Dijkstra's algorithm for finding the shortest path, utilizing custom-built data structures instead of standard libraries.
- **[Probability-and-combinatorics](./Probability-and-combinatorics/)**: A collection of laboratory assignments focusing on mathematical computations, probability, and combinatorial algorithms.

### 🎮 Games & Simulations

- **[Virtual-World-Simulator](./Virtual-World-Simulator/)**: A comprehensive Virtual World simulator built using Object-Oriented Programming (OOP) principles, featuring complex interactions between entities.
- **[GIPF](./GIPF/)**: A digital implementation of logic and mechanics for the GIPF board game, focusing on game state management and move validation.

### ⚙️ Systems & Concurrent Programming

- **[distributed-processing](./distributed-processing/)**: Projects and laboratory assignments covering distributed processing, operating system concepts, and concurrent programming challenges.

## Setup and Requirements

- **Compiler**: A C++ compiler supporting at least **C++11** or **C++14** (e.g., GCC, Clang, or MSVC).
- **Build Tools**: Most projects use a standard **Makefile** or are designed to be compiled directly via `g++`.
- **Operating System**: While most projects are cross-platform, the `distributed-processing` tasks may require a Linux-based environment for POSIX features.

## How to Run

1. **Navigate** to the chosen project directory.
2. **Compile** using the provided Makefile or manually via terminal:
```bash
g++ -O3 main.cpp -o program_name
```
3. **Execute** the generated binary:
```bash
./program_name
```

---

_Note: Each directory contains its own dedicated README.md file with a more detailed description of the specific project, implemented algorithms, and mathematical background._
