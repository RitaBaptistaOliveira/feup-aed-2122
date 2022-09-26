// AED 2021/2022 - Aula Pratica 11
// Pedro Ribeiro (DCC/FCUP) [17/01/2022]

#include "graph.h"
#include <climits>

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
// 1) Algoritmo de Dijkstra e caminhos mais curtos
// ----------------------------------------------------------

// ..............................
// a) Distância entre dois nós
// TODO
int Graph::dijkstra_distance(int a, int b) {
    MinHeap <int,int> h = MinHeap<int, int>(n, -1);
    for(Node & node : nodes){
        node.visited = false;
        node.pred = -1;
        node.dist = INT_MAX;
    }
    nodes[a].dist = 0;
    h.insert(a,0);
    while(h.getSize() != 0) {
        int u = h.removeMin();
        nodes[u].visited = true;
        for (Edge & edge: nodes[u].adj) {
            if (!nodes[edge.dest].visited && edge.weight + nodes[u].dist < nodes[edge.dest].dist) {
                nodes[edge.dest].dist = edge.weight + nodes[u].dist;
                nodes[edge.dest].pred = u;
                if (h.hasKey(edge.dest)) {
                    h.decreaseKey(edge.dest, nodes[edge.dest].dist);
                }
                else h.insert(edge.dest, nodes[edge.dest].dist);
            }
        }
    }
    if(nodes[b].dist == INT_MAX) return -1;
    return nodes[b].dist;
}

// ..............................
// b) Caminho mais curto entre dois nós
// TODO
list<int> Graph::dijkstra_path(int a, int b) {
    list<int> path;
    MinHeap <int,int> h = MinHeap<int, int>(n, -1);
    for(Node & node : nodes){
        node.visited = false;
        node.pred = -1;
        node.dist = INT_MAX;
    }
    nodes[a].dist = 0;
    h.insert(a,0);
    while(h.getSize() != 0) {
        int u = h.removeMin();
        nodes[u].visited = true;
        for (Edge & edge: nodes[u].adj) {
            if (!nodes[edge.dest].visited && edge.weight + nodes[u].dist < nodes[edge.dest].dist) {
                nodes[edge.dest].dist = edge.weight + nodes[u].dist;
                nodes[edge.dest].pred = u;
                if (h.hasKey(edge.dest)) {
                    h.decreaseKey(edge.dest, nodes[edge.dest].dist);
                }
                else h.insert(edge.dest, nodes[edge.dest].dist);
            }
        }
    }
    int last = b;
    if(nodes[last].pred == -1) return path;

    while(last != -1){
        path.push_front(last);
        last = nodes[last].pred;
    }

    return path;
}