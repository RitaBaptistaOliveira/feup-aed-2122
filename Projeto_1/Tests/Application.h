#ifndef UNTITLED2_APPLICATION_H
#define UNTITLED2_APPLICATION_H

#include <iostream>
#include <fstream>
#include "Airport.h"
#include "Flight.h"
#include "Airplane.h"
#include "Employee.h"
#include "Passenger.h"
#include <list>
#include <string>

using namespace std;

class Application {
public:
    Application();
    void run();
private:
    Date current;
    list<Airport> airports;
    list<Flight> flights;
    list<Airplane> airplanes;
    list<Employee> employees;
    list<Passenger> passengers;
    void draw_menu() const;
    void showAirplaneOptions() const;
    void airportMenu() const;
    void airplaneMenu();
    void flightMenu() const;
    void buyTicketMenu();
    void checkIn();
    void getSystemTime();
    void readAirport();
    void readAirplanes();
    void readPassenger();
    void readFlights();
    void readEmployee();
    void readServices();
    void readTickets();
    void showFlightsBetweenTwoAirports(Airport &a1, Airport &a2) const;
    void showFlightsBetweenTwoDates(Date &date1, Date &date2) const;
    void showStationSchedule(TransportStation station) const;
    void showAirplanes() const;
    bool chooseAirport(const string &str, Airport &airport) const;
    bool chooseAirplane(Airplane &airplane) const;
    bool chooseFlight(Flight &flight) const;
    bool findEmployee(int id, Employee &employee);
    bool findAirport(string &airportName, Airport &airport);
    string getString(string &original_s) const;
    set<TransportStation> getTransports(string airport);
    bool buyTicket(int fNumber);
    void addFlightToAirplane(Airplane &airplane);
    void addServiceToAirplane(Airplane &airplane);
    string askForFutureDate();
    void cancelTicket();
    void storeFlightsAndTickets();
    void storePassengers();
    void storeServices();
};

#endif //UNTITLED2_APPLICATION_H