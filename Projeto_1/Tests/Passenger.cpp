#include "Passenger.h"

/**
 * Class Passenger constructor.
 * Initializes a new instance of the Passenger class using the specified name and cardId
 * @param name Name of the passenger
 * @param cardId Id of the passenger's card
 */
Passenger::Passenger(string name, int cardId) : cardId(cardId) {
    this->name = name;
}

/**
 * Class Passenger constructor.
 * Initializes a new instance of the Passenger class using the specified name, cardId and flights
 * @param name Name of the passenger
 * @param cardId Id of the passenger's card
 * @param flights List of flights that the passenger has been on
 */
Passenger::Passenger(string name, int cardId, list<Flight> flights) : cardId(cardId){
    this->name = name;
    for(auto flight: flights){
        this->flights.push_back(flight);
    }
}

/**
 * @return The name of the passenger
 */
string Passenger::getName() const {
    return name;
}

/**
 * Sets the name of the passenger to the given name
 * @param name New name of the passenger
 */
void Passenger::setName(const string name) {
    this->name = name;
}

/**
 * @return The id of the passenger's card
 */
int Passenger::getCardId() const {
    return cardId;
}

/**
 * @return The list of flights the passenger has been on
 */
list<Flight> Passenger::getFlights(){
    flights.sort();
    return flights;
}

/**
 * Sets the list of flights the passenger has been on to the given list
 * @param flights New flights list
 */
void Passenger::setFlights(list<Flight> flights) {
    for(auto flight: flights){
        this->flights.push_back(flight);
    }
}

/**
 * Adds a flight to the passenger's list of flights
 * @param flight Flight to add to the list
 */
void Passenger::addFlight(Flight &flight) {
    flights.push_back(flight);
}
