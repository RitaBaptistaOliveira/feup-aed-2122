#include "Menu.h"

/**
 * Class Menu constructor.
 * Initializes a new instance of the Menu class using default values
 */
Menu::Menu() : app(Graph(true), Graph(true)) {}

/**
 * Asks the user the distance they're willing to walk and sets all the walking distance edges. Calls the methods that allows the user to see all the menu's options
 */
void Menu::run() {
    pair<string, string> stops;
    double walkingDistance;
    cout << "How much are you willing to walk in meters? ";
    cin >> walkingDistance;
    app.setWalkLines(walkingDistance);
    int option;
    do {
        drawMenu();
        cin >> option;
        if (option == 1) {
            stops = stopType();
            stopsMenu(stops);
        }
    } while (option != 0);
}

/**
 * Shows the user the menu's options
 */
void Menu::drawMenu() {
    cout << "--------Graph Program--------" << endl << endl;
    cout << "1. Best path between two stops" << endl;
    cout << "0. Exit" << endl;
    cout << "Choose one:";
}

/**
 * Shows the user the options to find the path between two stops and, according to the user's choice, shows the best path
 * @param stops pair with the code of the stop of origin and destination
 */
void Menu::stopsMenu(pair<string, string> stops) {
    int option;
    do {
        cout << "1. Path with least stops" << endl;
        cout << "2. Cheapest path" << endl;
        cout << "3. Path with the shortest overall distance" << endl;
        cout << "4. Path with least bus changes" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose one: ";
        cin >> option;
        switch (option) {
            case 1:
                app.findPathLeastStops(stops.first, stops.second);
                break;
            case 2:
                app.findPathLeastZones(stops.first, stops.second);
                break;
            case 3:
                app.findPathShortestDistance(stops.first, stops.second);
                break;
            case 4:
                app.findPathLeastLines(stops.first, stops.second);
                break;
            default:
                break;
        }
    } while (option != 0);
}

/**
 * Shows the user the options of input, if they want to enter coordinates of the code od the stops
 * @return a pair with the closest stops if the user gave coordinates or the stops' codes given
 */
pair<string, string> Menu::stopType() {
    int option;
    char separator;
    double latitude1, latitude2;
    double longitude1, longitude2;
    string stop1, stop2;
    cout << "1. Coordinates" << endl;
    cout << "2. Stop code" << endl;
    cout << "0. Exit" << endl;
    cout << "Choose one: ";
    cin >> option;
    do {
        switch (option) {
            case 1: {
                cout << "Origin coordinates(latitude,longitude): ";
                cin >> latitude1 >> separator >> longitude1;
                Coordinates coordinates1(latitude1, longitude1);
                cout << "Destination coordinates(latitude,longitude): ";
                cin >> latitude2 >> separator >> longitude2;
                Coordinates coordinates2(latitude2, longitude2);
                stop1 = app.findClosestStop(coordinates1);
                stop2 = app.findClosestStop(coordinates2);
                return make_pair(stop1, stop2);
            }
            case 2:
                do{
                    cout << "Origin stop: ";
                    cin >> stop1;
                }while(!app.stopExists(stop1));
                do{
                    cout << "Destination stop: ";
                    cin >> stop2;
                }while(!app.stopExists(stop2));
                return make_pair(stop1, stop2);
            default:
                break;
        }
    } while (option != 0);
    return make_pair("","");
}