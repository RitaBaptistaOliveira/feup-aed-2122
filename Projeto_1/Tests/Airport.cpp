#include "Airport.h"

/**
 * Class Airport constructor.
 * Initializes a new instance of the Airport class using default values
 */
Airport::Airport() = default;

/**
 * Class Airport constructor.
 * Initializes a new instance of the Airport class using the specified name, stations, maxPiles and maxLuggage
 * @param name Name of the airport
 * @param stations Set with the airport's closest transport stations
 * @param maxPiles Standard size of luggage piles by carriage cart of the airport
 * @param maxLuggage Standard size of the number of luggage per pile of the airport
 */
Airport::Airport(string name, set<TransportStation> stations, int maxPiles, int maxLuggage) {
    this->name = name;
    this->stations = stations;
    cartDimensions.first = maxPiles;
    cartDimensions.second = maxLuggage;
}

/**
 * @return The name of the airport
 */
string Airport::getName() const {
    return name;
}

/**
 * Sets the name of the airport to the given name
 * @param name New name for the airport
 */
void Airport::setName(const string &name) {
    this->name = name;
}

/**
 * @return The set with the airport's transport stations
 */
set<TransportStation> Airport::getStations() const{
    return stations;
}

/**
 * @return A pair with the standard dimensions of the luggage cart
 */
pair<int, int> Airport::getCartDimensions() const {
    return cartDimensions;
}

/**
 * Sets the luggage cart dimensions to the given maxPiles and maxLuggage
 * @param maxPiles New standard size for the luggage piles by carriage cart of the airport
 * @param maxLuggage New standard size for the number of luggage per pile of the airport
 */
void Airport::setCartDimensions(int maxPiles, int maxLuggage) {
    cartDimensions.first = maxPiles;
    cartDimensions.second = maxLuggage;
}

/**
 * @return The closest transport station to the airport
 */
TransportStation Airport::getClosestTransport() {
    return *stations.begin();
}

/**
 * Given a time, searches the transport stations with the closest departure
 * @param time Time given
 * @return The transport station with the next departure after the given time or, in case of equality of departure times, the closest one to the airport
 */
TransportStation Airport::getNextTransport(Time &time) {
    Time minimum(23, 59);
    TransportStation final("Bus", 0);
    set<TransportStation>::iterator it;
    for (it = stations.begin(); it != stations.end(); it++) {
        TransportStation t = (*it);
        Time temp = t.getNextDeparture(time);
        if (temp < minimum) {
            minimum = temp;
            final = t;
        } else if (temp == minimum) {
            if (t.getAirportDistance() < final.getAirportDistance())
                final = t;
        }
    }
    return final;
}

/**
 * Overloaded == operator
 * @param a Airport to compare to
 * @return true if the name and the cart dimensions of the airport are equal to the given airport's
 */
bool Airport::operator==(Airport &a) {
    return this->name == a.getName() && this->cartDimensions == a.getCartDimensions();
}