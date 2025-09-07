# Graph Algorithms in C++

C++ implementations of classic graph algorithms:

- **Floyd–Warshall** – All-pairs shortest paths with intermediate phases.  
- **Dijkstra** – Single-source shortest paths using a priority queue.  
- **MST-based TSP Approximation** – Builds a Minimum Spanning Tree and performs a preorder traversal to approximate a TSP tour.  

### Features
- Uses adjacency matrices and adjacency lists where appropriate.  
- Handles unreachable nodes with a large `inf` constant.  
- Returns both path reconstructions and total distances.  

### Usage
Compile and run with:

```bash
g++ -std=c++17 main.cpp -o graph_algos
./graph_algos
