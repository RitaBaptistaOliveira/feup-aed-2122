#ifndef UNTITLED2_TRANSPORTSTATION_H
#define UNTITLED2_TRANSPORTSTATION_H

#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include "Time.h"

using namespace std;

class TransportStation {
    string transportType;
    int airportDistance;
    set<Time> schedule;
public:
    TransportStation(string transportType, int airportDistance);
    TransportStation(string transportType, int airportDistance, vector<string> schedule);
    string getTransportType() const;
    void setTransportType(string transportType);
    int getAirportDistance() const;
    void setAirportDistance(int airportDistance);
    set<Time> getSchedule() const;
    void setSchedule(set<Time> &schedule);
    void updateSchedule(Time &time);
    bool removeFromSchedule(Time &time);
    Time getNextDeparture(Time &time);
    bool validTransport(string basicString);
    bool operator<(const TransportStation &transportStation) const;
};

/**
 * Exception for an invalid transportType
 */
class InvalidTransport : public exception{
public:
    InvalidTransport() {
        cout << "Invalid transport!" << endl;
    }
};
#endif //UNTITLED2_TRANSPORTSTATION_H
