# Sem05-AnalysisAndDesignOfAlgorithms

### Course Overview
This repository contains assignments for the **Analysis and Design of Algorithms** course taken in my fifth semester. This course focused on analyzing algorithms for efficiency, categorizing them based on time complexity (e.g., O(n), Θ(n), Ω(n)), and learning techniques to optimize their performance. Topics included algorithmic complexity, dynamic programming, and efficient sorting and searching methods.

### Learning Outcomes
Through this course, I developed skills in:
- Evaluating and categorizing algorithms based on time and space complexity.
- Optimizing algorithms for performance, including reducing time and space costs.
- Implementing dynamic programming techniques for complex problem-solving.
- Applying sorting and graph traversal algorithms to enhance efficiency.

### Project and Assignments

#### 1. **Horse_testing3.cpp**
   - **Description**: Implements an algorithm that simulates a **knight’s tour** on a chessboard using recursive backtracking.
   - **Key Features**:
     - Uses heuristics to reduce the number of moves and checks for possible moves.
     - Evaluates algorithm complexity by calculating potential paths and pruning unnecessary moves.

#### 2. **Practica2.cpp**
   - **Description**: A multi-functional file containing several algorithmic implementations, including:
     - **Standard and Strassen’s Matrix Multiplication**: Implements both standard and optimized matrix multiplication (Strassen’s algorithm), suitable for large matrix computations.
     - **Matrix Operations**: Provides functions for matrix addition, zero padding, and partitioning matrices, essential for Strassen’s divide-and-conquer approach.
   - **Purpose**: Demonstrates the efficiency of matrix multiplication algorithms and introduces divide-and-conquer techniques.

#### 3. **SAT.cpp**
   - **Description**: Contains code for solving the **Boolean satisfiability problem (SAT)**, which finds variable assignments that satisfy a given Boolean formula.
   - **Key Features**:
     - Uses backtracking and heuristic methods for SAT resolution.
   - **Purpose**: Applies logic-based problem-solving and highlights algorithmic complexity in Boolean evaluations.

#### 4. **Sorts.cpp**
   - **Description**: Implements and analyzes various sorting algorithms:
     - **Bubble Sort, Insertion Sort, Selection Sort**: Demonstrates elementary sorting techniques.
     - **Merge Sort, Quick Sort, Heap Sort**: Implements advanced sorting algorithms with improved efficiency.
   - **Purpose**: Explores time complexities, demonstrating O(n²) for basic sorts and O(n log n) for optimized sorts like Merge, Quick, and Heap.

#### 5. **tarea.cpp**
   - **Description**: Uses **dynamic programming** and backtracking to solve a partition problem, outputting combinations that sum to a target value.
   - **Key Features**:
     - Allows users to input a target sum and displays possible partitions using a predefined set of numbers.
   - **Purpose**: Demonstrates recursion and dynamic programming for combinatorial problems.

### Usage Instructions
To run each assignment:
1. **Compile** the `.cpp` file with a C++ compiler, such as `g++`.
   ```bash
   g++ -o output_file_name assignment_name.cpp
   ```
2. **Execute** the compiled program:
   ```bash
   ./output_file_name
   ```
