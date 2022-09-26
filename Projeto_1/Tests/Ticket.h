#ifndef UNTITLED2_TICKET_H
#define UNTITLED2_TICKET_H

#include <iostream>

using namespace std;

class Ticket {
    static int ID;
    int ticketId;
    int flightNumber;
    bool luggage;
    int passengerId;
public:
    Ticket(int flightNumber, bool luggage, int passengerId);
    int getTicketId() const;
    int getFlightNumber() const;
    void setFlightNumber(int flightNumber);
    bool getLuggage();
    void setLuggage(bool luggage);
    int getPassengerId() const;
    void setPassengerId(int passengerId);
    bool operator==(const Ticket &ticket) const;
};


#endif //UNTITLED2_TICKET_H
