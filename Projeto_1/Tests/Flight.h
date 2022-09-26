#ifndef UNTITLED2_FLIGHT_H
#define UNTITLED2_FLIGHT_H

#include <iostream>
#include <string>
#include <queue>
#include <list>
#include <cmath>
#include <iomanip>
#include "Date.h"
#include "LuggageCart.h"
#include "Ticket.h"
#include "Airport.h"
#include "Time.h"

using namespace std;

typedef int luggage;

class Flight {
    static int fNumber;
    int flightNumber;
    int airplaneId;
    Date date;
    Time departureTime;
    int duration;
    int seatsLeft;
    Airport origin;
    Airport destination;
    list<LuggageCart> carts;
    queue<luggage> conveyorBelt;
    list<Ticket> boughtTickets;
public:
    Flight();
    Flight(string date, int duration, Airport &origin, Airport &destination, Time departureTime, int airplaneId);
    int getFlightNumber() const;
    int getAirplaneId() const;
    string getDate() const;
    void setDate(string date);
    string getDepartureTime() const;
    void setDepartureTime(Time &time);
    int getDuration() const;
    void setDuration(int duration);
    int getSeatsLeft() const;
    void setSeatsLeft(int seats);
    Airport getOrigin() const;
    Airport getDestination() const;
    list<LuggageCart> getLuggageCart() const;
    queue<luggage> getConveyorBelt() const;
    void addToConveyorBelt();
    void conveyorBeltToCart();
    list<Ticket> getBoughtTickets() const;
    void addTicket(Ticket &ticket);
    void removeTicket(int id);
    string getArrivalTime() const;
    bool operator<(const Flight &flight) const;
    bool operator==(const Flight &flight) const;
};

class InvalidFlight : public exception{
public:
    InvalidFlight(){
        cout << "Invalid flight!" << "\n" << "\n";
    }
};

#endif //UNTITLED2_FLIGHT_H
