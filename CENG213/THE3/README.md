# CENG 213: Data Structures - Flight Finder Application

## Overview
This programming assignment involves the implementation of a flight finder application using C++ and various data structures such as MultiGraph and Hash Table. The main objectives include:

- Implementing MultiGraph for managing flights and their details.
- Implementing a Hash Table for efficient storage and retrieval of flight paths.
- Combining both data structures in the `CENGFlight` class for flight management.

## Implementation Details

### 1. MultiGraph Implementation
- **MultiGraph** data structure represents a directional, weighted multigraph.
- **GraphVertex** and **GraphEdge** structures define vertices and edges respectively.
- **MultiGraph** class includes methods for vertex and edge management, shortest path calculations, and more.

### 2. Hash Table
- A compile-time sized **HashTable** class is implemented.
- Hashing is done using a specific hash function and quadratic probing is used for resolving collisions.
- Entries in the hash table have an LRU counter to manage eviction.

### 3. CENG Flight Finder
- **CENGFlight** class combines the functionalities of MultiGraph and HashTable.
- It provides methods to find flights, halt and resume flights, manage cache, and more.

## Compilation and Execution
To compile and run the program, follow these steps:

1. Navigate to the directory containing the source files.
2. Compile the source files using the C++ compiler:
   ```
   g++ -o main MultiGraph.cpp HashTable.cpp CENGFlight.cpp main.cpp
   ```
3. Execute the compiled program:
   ```
   ./main
   ```

## Directory Structure
- **MultiGraph.h & MultiGraph.cpp**: Implement MultiGraph data structure.
- **HashTable.h & HashTable.hpp**: Implement Hash Table data structure.
- **CENGFlight.h & CENGFlight.cpp**: Implement the CENGFlight class combining MultiGraph and HashTable.
- **Exceptions.h**: Define custom exceptions.
- **IntPair.h**: Provide a template instantiation example for `std::priority_queue`.
- **README.md**: This documentation file.

## Important Notes
- Use of STL is restricted, with a few exceptions like `std::priority_queue`.
- Ensure to follow the given specifications and guidelines for each method and functionality.
- Handle exceptions appropriately and ensure proper error messages are displayed.

## Conclusion
This flight finder application provides a comprehensive solution for managing flight details, finding optimal flight paths, and caching frequently requested paths for efficiency. Ensure to test the application thoroughly and adhere to the given guidelines for best results.