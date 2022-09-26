#ifndef FEUP_AED_PROJ2_GRAPH_H
#define FEUP_AED_PROJ2_GRAPH_H

#include "Coordinates.h"
#include "minHeap.h"
#include <vector>
#include <list>
#include <iostream>
#include <float.h>
#include <set>
#include <map>

using namespace std;

class Graph {
    struct Edge {
        int dest;   /**< Destination node */
        double weight; /**< An integer weight */
        string line;  /**< Name of the bus line */
        bool zoneChange;  /**< True if the source node and the destination node have different zones or false otherwise */
    };

    struct Node {
        string code; /** Code of the stop*/
        list<Edge> adj; /**< The list of outgoing edges (to adjacent nodes) */
        double dist;
        int pred;
        bool visited;
        string zone; /**< Name of the zone of the bus stop */
        Coordinates coordinates; /**< Coordinates of the bus stop */
        string line;
    };

    int n;              /**< Graph size (number of stops) */
    bool hasDir;        /**< True if the graph is directed or false otherwise */
    vector<Node> nodes; /**< The list of nodes being represented */
    double walkingDistance; /**< Distance the user is willing to walk */

    void dijkstra(int s);
    void dijkstraZones(int s);
    void bfsD(int v);

public:
    Graph(bool dir = false);

    void setSize(int nodes);
    void setWalkingDistance(double walkingDistance);
    void setNode(int node,string code, string zone, Coordinates coordinates);
    void addEdge(int src, int dest, double weight = 1, string line = "line");
    void setEdge(int a, int b, string line);
    void setEdgeW(int a, int b, string line, double weight);
    void setLineChangeEdges(multimap<string,int> lineChangesStopNumbers, map<string, int> stopNumbers);
    void setWalkEdges();

    int closestStop(Coordinates coordinates);

    double dijkstra_distance(int a, int b);
    list<int> dijkstra_path(int a, int b);

    double dijkstra_Zone(int a, int b);
    list<int> dijkstra_pathZone(int a, int b);

    int bfsD_distance(int a, int b);
    list<int> bfsD_path(int a, int b);

    list<string> simplifiedPath(list<int> stops);
};

#endif