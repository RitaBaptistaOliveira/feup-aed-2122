#ifndef UNTITLED2_AIRPLANE_H
#define UNTITLED2_AIRPLANE_H

#include <iostream>
#include <string>
#include <list>
#include "Flight.h"
#include "Service.h"

using namespace std;

class Airplane {
    static int airplaneId;
    int id;
    int capacity;
    string type;
    string licencePlate;
    queue<Flight> futureFlights;
    list<Flight> previousFlights;
    queue<Service> futureServices;
    list<Service> previousServices;
public:
    Airplane();
    Airplane(string licencePlate, string type, int capacity);
    int getId() const;
    int getCapacity() const;
    string getType() const;
    void setType(const string &type);
    string getLicencePlate() const;
    void setLicencePlate(const string &licencePlate);
    queue<Flight> getFutureFlights() const;
    void addFutureFlight(Flight &flight);
    list<Flight> getPreviousFlights() const;
    void addPreviousFlight(Flight &flight);
    queue<Service> getFutureServices();
    void addFutureService(const Service &service);
    void removeFutureService();
    list<Service> getPreviousServices();
    void addPreviousService(Service &service);
    void flightDeparture();
    void showPreviousFlights() const;
    void showFutureFlights() const;
    void showPreviousServices() const;
    void showFutureServices() const;
};


#endif //UNTITLED2_AIRPLANE_H