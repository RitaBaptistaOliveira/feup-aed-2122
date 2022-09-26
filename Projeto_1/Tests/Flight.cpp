#include "Flight.h"

/**
 * Initializes the number used to identify the flights' numbers
 */
int Flight::fNumber = 1;

/**
 * Class Flight constructor.
 * Initializes a new instance of the Flight class using default values
 */
Flight::Flight() = default;

/**
 * Class Flight constructor.
 * Initializes a new instance of the Flight class using the specified date, duration, origin and destination
 * @param date Date of the flight
 * @param duration Duration of the flight
 * @param origin Origin airport of the flight
 * @param destination Destination airport of the flight
 * @param departureTime Departure time of the flight
 */
Flight::Flight(string date, int duration, Airport &origin, Airport &destination, Time departureTime, int airplaneId) : destination(destination), origin(origin) {
    setDate(date);
    this->duration = duration;
    flightNumber = fNumber;
    fNumber++;
    this->departureTime = departureTime;
    this->airplaneId = airplaneId;
}

/**
 * @return The flight number
 */
int Flight::getFlightNumber() const {
    return flightNumber;
}

/**
 * @return The flight's airplane id
 */
int Flight::getAirplaneId() const{
    return airplaneId;
}

/**
 * @return The date of the flight in the format "dd/mm/yyyy"
 */
string Flight::getDate() const {
    return date.getDate();
}

/**
 * Sets the flight's date to the given date
 * @param date New date for the flight
 */
void Flight::setDate(string date) {
    this->date = Date(date);
}

/**
 * @return The time of departure of the flight in the format "hh:mm"
 */
string Flight::getDepartureTime() const {
    return departureTime.getTime();
}

/**
 * Sets the departure time of the flight to the given time
 * @param time New time of departure
 */
void Flight::setDepartureTime(Time &time) {
    this->departureTime = time;
}

/**
 * @return The duration of the flight
 */
int Flight::getDuration() const {
    return duration;
}

/**
 * Sets the duration of the flight to the given duration
 * @param duration New duration of the flight
 */
void Flight::setDuration(int duration) {
    this->duration = duration;
}

/**
 * @return The number of seats left on the flight
 */
int Flight::getSeatsLeft() const {
    return seatsLeft;
}

/**
 * Sets the flight's seats left to the given number
 * @param seats New number of seats left for the flight
 */
void Flight::setSeatsLeft(int seats) {
    this->seatsLeft = seats;
}

/**
 * @return The origin airport of the flight
 */
Airport Flight::getOrigin() const {
    return origin;
}

/**
 * @return The destination airport of the flight
 */
Airport Flight::getDestination() const {
    return destination;
}

/**
 * @return The list with the flight's luggage carts
 */
list<LuggageCart> Flight::getLuggageCart() const {
    return carts;
}

/**
 * @return The queue (conveyor belt) with the luggage
 */
queue<luggage> Flight::getConveyorBelt() const {
    return conveyorBelt;
}

/**
 * Adds the luggage (ticketId) to the conveyor belt if the ticket's passenger has luggage
 */
void Flight::addToConveyorBelt() {
    list<Ticket>::iterator it;
    for (it = boughtTickets.begin(); it != boughtTickets.end(); it++) {
        if (it->getLuggage())
            conveyorBelt.push(it->getTicketId());
    }
}

/**
 * Empties the conveyor belt and transfers the luggage to the luggage carts.
 */
void Flight::conveyorBeltToCart() {
    int maxPiles = origin.getCartDimensions().first;
    int maxLuggage = origin.getCartDimensions().second;
    float c = conveyorBelt.size();
    int numLuggageCarts = ceil(c / (maxPiles * maxLuggage));
    for (int i = 0; i < numLuggageCarts; i++) {
        LuggageCart l(maxPiles, maxLuggage);
        carts.push_back(l);
    }
    list<LuggageCart>::iterator it = carts.begin();
    while (!conveyorBelt.empty()) {
        if (!it->isFull()) {
            it->addLuggage(conveyorBelt.front());
            conveyorBelt.pop();
        } else {
            it++;
        }
    }
}

/**
 * @return The list with the bought tickets
 */
list<Ticket> Flight::getBoughtTickets() const {
    return boughtTickets;
}

/**
 * Adds a ticket to the bought tickets list and decreases the number of seats left
 * @param ticket New bought ticket
 */
void Flight::addTicket(Ticket &ticket) {
    boughtTickets.push_back(ticket);
    seatsLeft--;
}

/**
 * Removes a ticket with the given passenger's id from the flight's bought tickets list
 * @param id
 */
void Flight::removeTicket(int id) {
    list<Ticket>::iterator it;
    for (it = boughtTickets.begin(); it != boughtTickets.end(); it++) {
        if (it->getPassengerId() == id) {
            boughtTickets.erase(it);
            break;
        }
    }
}

/**
 * Calculates the time of arrival of a flight according to its departure time and duration
 * @return The arrival time in the format "hh:mm"
 */
string Flight::getArrivalTime() const {
    int m = departureTime.getHours() * 60 + departureTime.getMinutes() + duration;
    m = m % 1440;
    Time t;
    t.setHours(m / 60);
    t.setMinutes(m % 60);
    return t.getTime();
}

/**
 * Overloaded < operator
 * @param flight Flight to compare to
 * @return true if the Date is earlier than the given flight's date or false otherwise
 */
bool Flight::operator<(const Flight &flight) const {
    if(date == flight.getDate())
        return departureTime < flight.getDepartureTime();
    return date < flight.getDate();
}

bool Flight::operator==(const Flight &flight) const {
    return date == flight.getDate() && departureTime == flight.getDepartureTime();
}
