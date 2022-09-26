#ifndef UNTITLED2_PASSENGER_H
#define UNTITLED2_PASSENGER_H

#include <iostream>
#include<list>
#include"Flight.h"

using namespace std;

class Passenger {
    string name;
    const int cardId;
    list<Flight> flights;
public:
    Passenger(string name, int cardId);
    Passenger(string name, int cardId, list<Flight> previousFlights);
    string getName() const;
    void setName(const string name);
    int getCardId() const;
    list<Flight> getFlights();
    void setFlights(list<Flight> flights);
    void addFlight(Flight &flight);
};


#endif //UNTITLED2_PASSENGER_H
