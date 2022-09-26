#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include "Application.h"

/**
 * Class Application constructor.
 * Initializes a new instance of the Application class using the specified graph
 * @param graph Graph that will store all the information about the lines, stops and zones
 * @param graphLineChanges
 */
Application::Application(Graph graph, Graph graphLineChanges) : graph(graph), graphLineChanges(graphLineChanges) {
    graphLineChangesSize = 0;
    readStops();
    readLines();
    readLinesForLineChanges();
    setLinesChangesEdges();
}

/**
 * Sets edges between all the nodes that are a walking distance from each other
 * @param walkingDistance Walking distance to set the edges
 */
void Application::setWalkLines(double walkingDistance) {
    graph.setWalkingDistance(walkingDistance);
    graph.setWalkEdges();
}

/**
 * Checks if the stopNumbers map contains the given stop code
 * @param stop Name of the stop code
 * @return True if the the stop exists or false otherwise
 */
bool Application::stopExists(string &stop) {
    if (stopNumbers.find(stop) != stopNumbers.end()) {
        return true;
    }
    return false;
}

/**
 * Opens and read a file and returns it's content
 * Time complexity: O(N x D), N is the number of lines in the file and D is the number of words in each line
 * @param filename Name of the file
 * @return a vector containing all the words from each row
 */
vector<vector<string>> Application::read(string filename) {
    vector<vector<string>> content;
    vector<string> row;
    string line, word;
    fstream file;
    file.open(filename);
    if (file.is_open()) {
        getline(file, line); //info
        if (filename.substr(0, 5) == "line_") {
            graphLineChangesSize += stoi(line);
        }
        while (getline(file, line)) {
            row.clear();
            stringstream str(line);
            while (getline(str, word, ','))
                row.push_back(word);
            content.push_back(row);
        }
    }
    return content;
}

/**
 * Opens the "stops.csv" file and reads it.
 * Creates all the nodes of the graph and stores in the stopNumbers map a pair containing the stop's code and the node's number
 * Time complexity: O(N)
 */
void Application::readStops() {
    vector<vector<string>> fileContent = read("stops.csv");
    graph.setSize(fileContent.size());
    for (int i = 0; i < fileContent.size(); i++) {
        Coordinates c(stod(fileContent[i][3]), stod(fileContent[i][4]));
        graph.setNode(i, fileContent[i][0], fileContent[i][2], c);
        nodeInformation.insert(make_pair(fileContent[i][0], make_pair(c, fileContent[i][2])));
        stopNumbers.insert(make_pair(fileContent[i][0], i));
    }
}

/**
 * Opens each of the line files and reads them.
 * Creates all the edges between the lines' stops
 * Time complexity: O(N^2)
 */
void Application::readLines() {
    vector<vector<string>> fileContent = read("lines.csv");
    for (auto &i: fileContent) {
        vector<vector<string>> line0 = read("line_" + i[0] + "_0.csv");
        vector<vector<string>> line1 = read("line_" + i[0] + "_1.csv");
        for (int j = 0; j < line0.size() - 1; j++) {
            graph.setEdge(stopNumbers[line0[j][0]], stopNumbers[line0[j + 1][0]], "line_" + i[0] + "_0");
        }
        if (!line1.empty()) {
            for (int j = 0; j < line1.size() - 1; j++) {
                graph.setEdge(stopNumbers[line1[j][0]], stopNumbers[line1[j + 1][0]], "line_" + i[0] + "_1");
            }
        }
    }
    graphLineChanges.setSize(graphLineChangesSize);
}

/**
 * Opens each of the line files and reads them, adding them to the graphLineChanges
 * Creates all the edges between the stops with the same line
 * Time complexity: O(N^2)
 */
void Application::readLinesForLineChanges() {
    vector<vector<string>> fileContent = read("lines.csv");
    int nodeIndex = 0;
    for (auto &i: fileContent) {
        vector<vector<string>> line0 = read("line_" + i[0] + "_0.csv");
        vector<vector<string>> line1 = read("line_" + i[0] + "_1.csv");
        for (int j = 0; j < line0.size() - 1; j++) {
            graphLineChanges.setNode(nodeIndex, line0[j][0], nodeInformation[line0[j][0]].second,
                                     nodeInformation[line0[j][0]].first);
            lineChangesStopNumbers.insert(make_pair(line0[j][0], nodeIndex));
            graphLineChanges.setEdgeW(nodeIndex, nodeIndex + 1, "line_" + i[0] + "_0", 0);
            nodeIndex++;
        }
        graphLineChanges.setNode(nodeIndex, line0[line0.size() - 1][0],
                                 nodeInformation[line0[line0.size() - 1][0]].second,
                                 nodeInformation[line0[line0.size() - 1][0]].first);
        lineChangesStopNumbers.insert(make_pair(line0[line0.size() - 1][0], nodeIndex));
        nodeIndex++;
        if (!line1.empty()) {
            for (int j = 0; j < line1.size() - 1; j++) {
                graphLineChanges.setNode(nodeIndex, line1[j][0], nodeInformation[line1[j][0]].second,
                                         nodeInformation[line1[j][0]].first);
                lineChangesStopNumbers.insert(make_pair(line1[j][0], nodeIndex));
                graphLineChanges.setEdgeW(nodeIndex, nodeIndex + 1, "line_" + i[0] + "_1", 0);
                nodeIndex++;
            }
            graphLineChanges.setNode(nodeIndex, line1[line1.size() - 1][0],
                                     nodeInformation[line1[line1.size() - 1][0]].second,
                                     nodeInformation[line1[line1.size() - 1][0]].first);
            lineChangesStopNumbers.insert(make_pair(line1[line1.size() - 1][0], nodeIndex));
        }
    }
}

/**
 * Finds the closest stop to the given coordinates and returns it's code
 * Time complexity: O(N)
 * @param coordinates The given coordinates
 * @return The code of the closest stop
 */
string Application::findClosestStop(Coordinates coordinates) {
    int node = graph.closestStop(coordinates);
    if (node == -1) return "There aren't any close stops. ";
    for (pair<string, int> stop: stopNumbers) {
        if (stop.second == node) {
            cout << "\n";
            return stop.first;
        }
    }
    return "";
}

/**
 * Find the path between two stops with the least amount of stops and shows it to the user
 * @param stop1 Origin stop
 * @param stop2 Destination stop
 */
void Application::findPathLeastStops(string &stop1, string &stop2) {
    int a = stopNumbers[stop1], b = stopNumbers[stop2];
    cout << "Distance: " << graph.bfsD_distance(a, b) << endl;
    list<int> path = graph.bfsD_path(a, b);
    outputPath(graph.simplifiedPath(path));
}

/**
 * Find the path between two stops with the least amount of zone changes and shows it to the user along with the cost
 * @param stop1 Origin stop
 * @param stop2 Destination stop
 */
void Application::findPathLeastZones(string &stop1, string &stop2) {
    int cost = 2;
    int a = stopNumbers[stop1], b = stopNumbers[stop2], numZones = graph.dijkstra_Zone(a, b);
    cout << "Number of zones: " << numZones + 1 << endl;
    cout << "Cost: " << cost + numZones << " euros" << endl; //The base cost is 2 euros and increases 1 euro per zone
    list<int> path = graph.dijkstra_pathZone(a, b);
    outputPath(graph.simplifiedPath(path));
}

/**
 * Find the path between two stops with the least overall distance and shows it to the user
 * @param stop1 Origin stop
 * @param stop2 Destination stop
 */
void Application::findPathShortestDistance(string &stop1, string &stop2) {
    int a = stopNumbers[stop1], b = stopNumbers[stop2];
    cout << "Distance in meters: " << graph.dijkstra_distance(a, b) << endl;
    list<int> path = graph.dijkstra_path(a, b);
    outputPath(graph.simplifiedPath(path));
}

/**
 * Find the path between two stops with the least amount of line changes and shows it to the user
 * Time complexity: O(S1 x S2), where S1 is the number of lines that go through stop1 and S2 is the number of lines that go through stop2
 * @param stop1 Origin stop
 * @param stop2 Destination stop
 */
void Application::findPathLeastLines(string stop1, string stop2) {
    double min = DBL_MAX, lineChanges;
    list<int> path;
    auto searchA = lineChangesStopNumbers.find(stop1);
    auto searchB = lineChangesStopNumbers.find(stop2);
    while (searchA != lineChangesStopNumbers.end() && searchA->first == stop1) {
        while (searchB != lineChangesStopNumbers.end() && searchB->first == stop2) {
            lineChanges = graphLineChanges.dijkstra_distance(searchA->second, searchB->second);
            cout << "1. " << searchA->first << ": " << searchA->second << "\n";
            cout << "2. " << searchB->first << ": " << searchB->second << "\n";
            if (lineChanges < min && lineChanges >= 0) {
                min = lineChanges;
                path = graphLineChanges.dijkstra_path(searchA->second, searchB->second);
                cout << "did path\n";
            }
            searchB++;
        }
        searchB = lineChangesStopNumbers.find(stop2);
        searchA++;
    }
    cout << "Minimum number of line changes: " << min << endl;
    list<string> output = graphLineChanges.simplifiedPath(path);
    outputPathLineChanges(output);
}

/**
 * Shows the user the path previously calculated.
 * @param output List with the strings to be outputted
 */
void Application::outputPath(list<string> output) {
    list<string>::iterator it = output.begin();
    while (it != output.end()) {
        if (isdigit((*it)[0])) {
            int num = stoi(*it);
            for (pair<string, int> stopCode: stopNumbers) {
                if (stopCode.second == num) {
                    cout << stopCode.first;
                    break;
                }
            }
        } else cout << *it;
        it++;
    }
}

/**
 * Shows the user the path previously calculated.
 * This one is specific for the "path with least line changes" option
 * @param output List with the strings to be outputted
 */
void Application::outputPathLineChanges(list<string> output) {
    list<string>::iterator it = output.begin();
    while (it != output.end()) {
        if (isdigit((*it)[0])) {
            int num = stoi(*it);
            for (pair<string, int> stopCode: lineChangesStopNumbers) {
                if (stopCode.second == num) {
                    cout << stopCode.first;
                    break;
                }
            }
        } else cout << *it;
        it++;
    }
}

/**
 * Calls the methods that create all the edges between the stops where the user can change line, and creates the edges according to the distance chosen by the user
 */
void Application::setLinesChangesEdges() {
    graphLineChanges.setLineChangeEdges(lineChangesStopNumbers, stopNumbers);
    graphLineChanges.setWalkEdges();
}