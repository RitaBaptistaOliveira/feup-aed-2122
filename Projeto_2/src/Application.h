#ifndef FEUP_AED_PROJ2_APPLICATION_H
#define FEUP_AED_PROJ2_APPLICATION_H

#include <string>
#include <vector>
#include <map>
#include "Graph.h"

using namespace std;

class Application {
    Graph graph; /**< Main Graph */
    Graph graphLineChanges; /**< Graph used for the "path with the least line changes" */
    int graphLineChangesSize; /**< Size of the graph graphLineChanges*/
    map<string, int> stopNumbers; /**< Maps each bus stop code with the node index */
    multimap<string, int> lineChangesStopNumbers; /**< Maps each bus stop code with the node index given in the graphLineChanges*/
    map<string, pair<Coordinates, string>> nodeInformation; /**< Maps the code with a pair that contains the coordinates and the zone of the stop */
public:
    Application(Graph graph, Graph graphLineChanges);
    void setWalkLines(double walkingDistance);
    bool stopExists(string &stop);
    vector<vector<string>> read(string filename);
    void readStops();
    void readLines();
    void readLinesForLineChanges();
    string findClosestStop(Coordinates coordinates);
    void findPathLeastStops(string &stop1, string &stop2);
    void findPathLeastZones(string &stop1, string &stop2);
    void findPathShortestDistance(string &stop1, string &stop2);
    void findPathLeastLines(string stop1, string stop2);
    void setLinesChangesEdges();
    void outputPath(list<string> output);
    void outputPathLineChanges(list<string> output);
};

#endif