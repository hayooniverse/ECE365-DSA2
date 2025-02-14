# Data Structures and Algorithms 2 - Project Repository

## Overview
This repository contains four projects developed for the **Fall 2023** Data Structures and Algorithms 2 course taught by **Professor Carl Sable** at **The Cooper Union**. Each project is implemented in C++ and demonstrates fundamental algorithmic concepts and data structures.

## Projects

### 1. Dijkstra's Algorithm
- **Description:** Implements Dijkstra's shortest path algorithm to solve the single-source shortest-path problem. The program reads a graph from a file and computes the shortest path from a user-specified starting vertex using a binary heap.
- **Implementation Details:**
  - Reads graph edges from a file with vertex identifiers and weights.
  - Uses a binary heap to efficiently determine shortest paths.
  - Outputs shortest paths along with total execution time.
  - Stores results in an output file listing each vertex and its shortest path from the source.
- **Key Concepts:** Graphs, Priority Queue, Greedy Algorithm, Binary Heap
- **Files:** `dijkstra.cpp`, `graph.h`, `graph.cpp`

### 2. Heap Implementation
- **Description:** Implements a binary heap priority queue with support for insertion, deletion, and key modification. The heap is designed to interact with a hash table for efficient lookups.
- **Implementation Details:**
  - Implements a max-capacity constrained binary heap.
  - Supports insertion, deletion, and key adjustments.
  - Integrates with a hash table for constant-time lookups.
  - Efficiently manages priority queue operations in logarithmic time.
- **Key Concepts:** Priority Queue, Binary Heap, Hash Table, Heapify Operations
- **Files:** `heap.cpp`, `heap.h`

### 3. Merge Algorithm
- **Description:** Solves the "merge of two strings" problem from the **1998 ACM Programming Contest**. It checks whether a third string is a valid interleaving (merge) of two given strings using dynamic programming.
- **Implementation Details:**
  - Utilizes a 2D dynamic programming table.
  - Ensures order is preserved for both strings.
  - Outputs the merged string with one string’s characters capitalized.
  - Handles large input sizes efficiently with optimal DP solutions.
- **Key Concepts:** Dynamic Programming, String Manipulation
- **Files:** `merge.cpp`

### 4. Spell Checker
- **Description:** Implements a spell-checking system using a custom hash table. It reads a dictionary file, loads words into a hash table, and then checks an input document for unrecognized words, reporting misspellings along with line numbers.
- **Implementation Details:**
  - Constructs a hash table using linear probing or double hashing.
  - Processes dictionary words and stores them efficiently.
  - Identifies misspelled words in a document while ignoring numbers.
  - Outputs a report detailing unknown words and long words.
- **Key Concepts:** Hashing, String Manipulation, Linear Probing or Double Hashing
- **Files:** `spellcheck.cpp`, `dictionary.h`, `dictionary.cpp`
