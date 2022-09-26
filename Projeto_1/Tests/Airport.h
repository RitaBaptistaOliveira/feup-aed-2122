#ifndef UNTITLED2_AIRPORT_H
#define UNTITLED2_AIRPORT_H

#include <iostream>
#include <set>
#include <list>
#include "TransportStation.h"

using namespace std;

class Airport {
    string name;
    set<TransportStation> stations;
    pair<int, int> cartDimensions;
public:
    Airport();
    Airport(string name, set<TransportStation> stations, int maxPiles, int maxLuggage);
    string getName() const;
    void setName(const string &name);
    set<TransportStation> getStations() const;
    pair<int,int> getCartDimensions() const;
    void setCartDimensions(int maxPiles, int maxLuggage);
    TransportStation getClosestTransport();
    TransportStation getNextTransport(Time &time);
    bool operator==(Airport &a);
};

class InvalidAirport: public exception{
public:
    InvalidAirport(){
        cout << "Invalid Airport!" << "\n" << "\n";
    }
};

#endif //UNTITLED2_AIRPORT_H
