#include "Ticket.h"

/**
 * Initializes the number used to identify the flights' numbers
 */
int Ticket::ID = 1;

/**
 * Class Ticket constructor.
 * Initializes a new instance of the Ticket class using the specified flightNumber, luggage and passengerId
 * @param flightNumber Flight number of the ticket's flight
 * @param luggage True if the passenger wants to take luggage with them or false otherwise
 * @param passengerId The ticket's passenger id
 */
Ticket::Ticket(int flightNumber, bool luggage, int passengerId) {
    this->luggage = luggage;
    this->ticketId = ID;
    ID++;
    this->flightNumber = flightNumber;
    this->passengerId = passengerId;
}

/**
 * @return The ticket id
 */
int Ticket::getTicketId() const {
    return ticketId;
}

/**
 * @return The flight number of the ticket's flight
 */
int Ticket::getFlightNumber() const{
    return flightNumber;
}

/**
 * Sets the flight number of the ticket's flight to the given number
 * @param flightNumber New flight number
 */
void Ticket::setFlightNumber(int flightNumber) {
    this->flightNumber = flightNumber;
}

/**
 * @return true if the passenger wants to take luggage with them or false otherwise
 */
bool Ticket::getLuggage() {
    return luggage;
}

/**
 * Sets the luggage value to the given boolean
 * @param luggage New luggage value
 */
void Ticket::setLuggage(bool luggage) {
    this->luggage = luggage;
}

/**
 * @return The ticket's passenger id
 */
int Ticket::getPassengerId() const {
    return passengerId;
}

/**
 * Sets the ticket's passenger id to the given number
 * @param passengerId New passenger id
 */
void Ticket::setPassengerId(int passengerId) {
    this->passengerId = passengerId;
}

/**
 * Overloaded == operator
 * @param ticket Ticket to compare to
 * @return true if the Ticket's id and the flight number are the same as the id and the flight number of the given ticket or false otherwise
 */
bool Ticket::operator==(const Ticket &ticket) const {
    return (ticketId == ticket.ticketId && flightNumber == ticket.flightNumber);
}
