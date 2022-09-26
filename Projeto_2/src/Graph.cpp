#include "Graph.h"
#include <climits>
#include <queue>

/**
 * Constructor of the Graph class.
 * Initializes a new instance of the Graph class using the specified bool and default values
 * @param dir bool that determines if the graph is directed or not
 */
Graph::Graph(bool dir) : n(0), hasDir(dir), nodes(1){
}

/**
 * Sets the size of the graph
 * @param num New size of the graph
 */
void Graph::setSize(int num) {
    n = num;
    nodes = vector<Node>(num+1);
}

/**
 * Sets the walking distance
 * @param walkingDistance the new walking distance
 */
void Graph::setWalkingDistance(double walkingDistance) {
    this->walkingDistance = walkingDistance;
}

/**
 * Sets the parameters of a certain node
 * @param node Number of the node
 * @param zone Name of the node's zone
 * @param coordinates Coordinates of the node
 */
void Graph::setNode(int node,string code,string zone, Coordinates coordinates) {
    nodes[node].code = code;
    nodes[node].coordinates = coordinates;
    nodes[node].zone = zone;
}

/**
 * Adds an edge to the list of edge of the src node
 * @param src The source node where the edge is going to be added
 * @param dest The destination of the edge
 * @param weight the weight of the edge
 * @param line The name of the edge's line
 */
void Graph::addEdge(int src, int dest, double weight, string line) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight, line, nodes[src].zone != nodes[dest].zone});
    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}

/**
 * Sets a new edge
 * @param a The edge's source
 * @param b The edge's destination
 * @param line The name of the edge's line
 */
void Graph::setEdge(int a, int b, string line){
    addEdge(a, b,nodes[a].coordinates.haversine(nodes[b].coordinates), line);
}

void Graph::setEdgeW(int a, int b, string line, double weight){
    addEdge(a, b,weight, line);
}


/**
 * Adds an edge to every two stops that have a distance between them inferior or equal to the walking distance
 * Time complexity: O(N^2)
 */
void Graph::setWalkEdges() {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            double distance = nodes[i].coordinates.haversine(nodes[j].coordinates);
            if (distance <= walkingDistance && nodes[i].code != nodes[j].code) {
                addEdge(i, j, distance, "Walk");
                addEdge(j, i, distance, "Walk");
            }
        }
    }
}

/**
 * Sets the edges between nodes that represent the same bus stop
 * @param lineChangesStopNumbers Multimap that maps the code of the stop to the multiple node indexes
 * @param stopNumbers Map that maps the code of the stop to the node index
 */
void Graph::setLineChangeEdges(multimap<string,int> lineChangesStopNumbers, map<string, int> stopNumbers){
    for (pair<string, int> p : stopNumbers){
        auto range = lineChangesStopNumbers.equal_range(p.first);
        auto range2 = lineChangesStopNumbers.equal_range(p.first);
        for(auto it1 = range.first; it1 != range.second; ++it1){
            for(auto it2 = range2.first; it2 != range2.second; ++it2){
                if(it1->second != it2->second){
                    addEdge(it1->second , it2->second, 1, "change line");
                }
            }
        }

    }
}

/**
 * Finds the closest stop to the given coordinates and returns the number of the stop's node
 * Time complexity: O(N)
 * @param coordinates The given coordinates
 * @return The number of the closest stop's node
 */
int Graph::closestStop(Coordinates coordinates) {
    double min = DBL_MAX, dist;
    int node = -1;
    for (int i = 0; i < n; i++){
        dist = coordinates.haversine(nodes[i].coordinates);
        if(dist <= walkingDistance && dist < min) {
            min = dist;
            node = i;
        }
    }
    return node;
}

/**
 * Dijkstra algorithm.
 * Computes the shortest path from the given node
 * Time complexity: O(E x log(V)), E is the number of edges and V is the number of nodes
 * @param s Number of the node
 */
void Graph::dijkstra(int s) {
    MinHeap <int,double> h = MinHeap<int,double>(n, -1);
    for(Node & node : nodes){
        node.visited = false;
        node.pred = -1;
        node.dist = INT_MAX;
    }
    nodes[s].dist = 0;
    h.insert(s,0);
    while(h.getSize() != 0) {
        int u = h.removeMin();
        nodes[u].visited = true;
        for (Edge & edge: nodes[u].adj) {
            if (!nodes[edge.dest].visited && edge.weight + nodes[u].dist < nodes[edge.dest].dist) {
                nodes[edge.dest].dist = edge.weight + nodes[u].dist;
                nodes[edge.dest].pred = u;
                nodes[edge.dest].line = edge.line;
                if (h.hasKey(edge.dest)) {
                    h.decreaseKey(edge.dest, nodes[edge.dest].dist);
                }
                else h.insert(edge.dest, nodes[edge.dest].dist);
            }
        }
    }
}

/**
 * Uses the dijkstra algorithm to return the minimum distance between two nodes
 * @param a Number of the node of origin
 * @param b Number of the node of destination
 * @return -1 if it's not possible to reach the second node from the first node or the distance otherwise
 */
double Graph::dijkstra_distance(int a, int b) {
    dijkstra(a);
    if(!nodes[b].visited) return -1;
    return nodes[b].dist;
}

/**
 * Uses the dijkstra algorithm to find the minimum distance between two nodes and creates a list with all of the path's nodes
 * Time complexity: O(N)
 * @param a Number of the node of origin
 * @param b Number of the node of destination
 * @return An empty list if it's not possible to reach the second node from the first node or a list with all of the path's nodes otherwise
 */
list<int> Graph::dijkstra_path(int a, int b) {
    list<int> path;
    int last = b;
    dijkstra(a);
    if(nodes[last].pred == -1) return path;
    while(last != -1){
        path.push_front(last);
        last = nodes[last].pred;
    }
    return path;
}

/**
 * Adapted version of the dijkstra algorithm.
 * Computes the path from the given node with the least amount of zone changes
 * Time complexity: O(E x log(V)), E is the number of edges and V is the number of nodes
 * @param s Number of the node
 */
void Graph::dijkstraZones(int s) {
    MinHeap <int,int> h = MinHeap<int,int>(n, -1);
    for(Node & node : nodes){
        node.visited = false;
        node.pred = -1;
        node.dist = INT_MAX;
    }
    nodes[s].dist = 0;
    h.insert(s, 0);
    while(h.getSize() != 0) {
        int u = h.removeMin();
        nodes[u].visited = true;
        for (Edge & edge: nodes[u].adj) {
            if (!nodes[edge.dest].visited && int(edge.zoneChange) + nodes[u].dist < nodes[edge.dest].dist) {
                nodes[edge.dest].dist =  int(edge.zoneChange) + nodes[u].dist;
                nodes[edge.dest].pred = u;
                nodes[edge.dest].line = edge.line;
                if (h.hasKey(edge.dest)) {
                    h.decreaseKey(edge.dest, nodes[edge.dest].dist);
                }
                else h.insert(edge.dest, nodes[edge.dest].dist);
            }
        }
    }
}

/**
 * Uses the adaptations of the dijkstra algorithm to find the path between two nodes with the least amount of zone changes
 * @param a Number of the node of origin
 * @param b Number of the node of destination
 * @return -1 if it's not possible to reach the second node from the second node or the number of zone changes otherwise
 */
double Graph::dijkstra_Zone(int a, int b) {
    dijkstraZones(a);
    if(!nodes[b].visited) return -1;
    return nodes[b].dist;
}

/**
 * Uses the adaptations of the dijkstra algorithm to find the path between two nodes with the least amount of zone changes and creates a list with all of the path's nodes
 * Time complexity: O(N)
 * @param a Number of the node of origin
 * @param b Number of the node of destination
 * @return An empty list if it's not possible to reach the second node from the first node or a list with all of the path's nodes otherwise
 */
list<int> Graph::dijkstra_pathZone(int a, int b) {
    list<int> path;
    int last = b;
    dijkstraZones(a);
    if(nodes[last].pred == -1) return path;
    while(last != -1){
        path.push_front(last);
        last = nodes[last].pred;
    }
    return path;
}

/**
 * Breadth-first search.
 * Computes the path with the least amount of stops from the given node
 * Time complexity: O(V x E), E is the number of edges and V is the number of nodes
 * @param v Number of the node
 */
void Graph::bfsD(int v) {
    for (int v = 1; v <= n; v++){
        nodes[v].visited = false;
        nodes[v].pred = -1;
        nodes[v].dist = -1;
    }
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
    nodes[v].dist = 0;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        for (auto &e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].pred = u;
                nodes[w].visited = true;
                nodes[w].dist = nodes[u].dist + 1;
                nodes[w].line = e.line;
            }
        }
    }
}

/**
 * Uses the breadth-first search to find the path with the least amount of stops between two nodes
 * @param a Number of the node of origin
 * @param b Number of the node of destination
 * @return -1 if it's not possible to reach the second node from the second node or the number of stops otherwise
 */
int Graph::bfsD_distance(int a, int b) {
    bfsD(a);
    if(!nodes[b].visited) return -1;
    return nodes[b].dist;
}

/**
 * Uses the breadth-first search to find the path with the least amount of stops between two nodes and creates a list with all of the path's nodes
 * Time complexity: O(N)
 * @param a Number of the node of origin
 * @param b Number of the node of destination
 * @return An empty list if it's not possible to reach the second node from the first node or a list with all of the path's nodes otherwise
 */
list<int> Graph::bfsD_path(int a, int b) {
    list<int> path;
    bfsD(a);
    int last = b;

    if(nodes[last].pred == -1) return path;
    while(last != -1){
        path.push_front(last);
        last = nodes[last].pred;
    }
    return path;
}

/**
 * Uses the list of stops to generate a simplified and more understandable output for the user
 * @param stops List of stops with the path the bus will make
 * @return List of strings to be shown to the user
 */
list<string> Graph::simplifiedPath(list<int> stops){
    list<string> output;
    list<int> ::iterator it = stops.begin();
    it++;
    string line = nodes[*it].line;
    it = stops.begin();
    while(it != stops.end()){
        if(it != stops.begin()){
            line = nodes[*it].line;
        }
        if(line == "Walk"){
            output.push_back("Walk to the stop ");
        }
        else if(line == "change line"){
            output.push_back("Change to the line ");
        }
        else {
            output.push_back("You enter the " + line + " in the stop ");
            output.push_back(to_string(*it));
            output.push_back(" and exit the bus at the stop ");
        }
        it++;
        while(it != stops.end()){
            string line2 = nodes[*it].line;
            if(line != line2){
                output.push_back(to_string(*it));
                output.push_back(".\n");
                break;
            }
            else if(it == stops.end()){
                output.push_back(to_string(*it));
                output.push_back(".\n");
                break;
            }
            line = nodes[*it].line;
            it++;
        }
    }
    it--;
    output.push_back(to_string(*it));
    output.push_back(".\n");
    output.push_back("You reached you destination!\n\n");
    return output;
}
