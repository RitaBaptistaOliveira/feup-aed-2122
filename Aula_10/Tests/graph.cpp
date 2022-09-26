// AED 2021/2022 - Aula Pratica 10
// Pedro Ribeiro (DCC/FCUP) [09/01/2022]

#include "graph.h"

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, int weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight});
    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}


// ----------------------------------------------------------
// Exercicio 3: Algoritmo de Prim
// ----------------------------------------------------------
// TODO
int Graph::prim(int r) {
    MinHeap<int, int> s(n, -1);
    int cost = 0;
    for (int v = 1; v <= n; v++){
        nodes[v].distance = INT_MAX;
        nodes[v].parent = 0;
    }
    nodes[r].distance = 0;
    while (s.getSize() != 0){
        int u = s.removeMin();
        cost += nodes[u].distance;
        for(auto &e : nodes[u].adj){
            int v = e.dest;
            int w = e.weight;
            if(s.hasKey(v) && nodes[v].distance > w){
                nodes[v].distance = w;
                nodes[v].parent = u;
                s.decreaseKey(v, w);
            }
        }
    }
    return cost;
}

// ----------------------------------------------------------
// Exercicio 5: Algoritmo de Kruskal
// ----------------------------------------------------------
// TODO
int Graph::kruskal() {
    return 0;
}
