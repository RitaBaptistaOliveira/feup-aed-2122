#include "TransportStation.h"

/**
 * Class TransportStation constructor.
 * Initializes a new instance of the TransportStation class using the specified transportType and airportDistance.
 * @param transportType Type of the Transport (can be a Train, a Subway or a Bus)
 * @param airportDistance Distance from the airport to the station (in meters)
 */
TransportStation::TransportStation(string transportType, int airportDistance){
    setTransportType(transportType);
    this->airportDistance = airportDistance;
}

/**
 * Class TransportStation constructor.
 * Initializes a new instance of the TransportStation class using the specified transportType, airportDistance and schedule.
 * @param transportType Type of the transport (can be a Train, a Subway or a Bus)
 * @param airportDistance Distance from the airport to the station (in meters)
 * @param schedule Vector with the times (in string form) the transport departs
 */
TransportStation::TransportStation(string transportType, int airportDistance, vector<string> schedule){
    setTransportType(transportType);
    this->airportDistance = airportDistance;
    for (auto time :schedule){
        Time t = Time(time);
        this->schedule.insert(t);
    }
}

/**
 * @return The transportType (Bus, Subway or Train)
 */
string TransportStation::getTransportType() const {
    return transportType;
}

/**
 * Sets the transportType to the given string if it is a valid transportType.
 * @param transportType Type of the Transport (has to be a Train, a Subway or a Bus to be valid)
 */
void TransportStation::setTransportType(string transportType) {
    if(validTransport(transportType))
        this->transportType = transportType;
    else
        throw InvalidTransport();
}

/**
 * @return The distance in meters from the airport to the TransportStation
 */
int TransportStation::getAirportDistance() const {
    return airportDistance;
}

/**
 * Sets the airportDistance to the given distance.
 * @param airportDistance Distance in meters from the airport to the transport station
 */
void TransportStation::setAirportDistance(int airportDistance) {
    this->airportDistance = airportDistance;
}

/**
 * @return The entire schedule of the TransportStation
 */
set<Time> TransportStation::getSchedule() const {
    return schedule;
}

/**
 * Sets the TransportStation's schedule to the given schedule.
 * @param schedule New schedule of the TransportStation
 */
void TransportStation::setSchedule(set<Time> &schedule) {
    this->schedule = schedule;
}

/**
 * Adds a new time to the schedule of the TransportStation
 * @param time New time to be added to the schedule
 */
void TransportStation::updateSchedule(Time &time){
    schedule.insert(time);
}

/**
 * Removes a given time from the schedule.
 * @param time Time to be removed from the schedule
 * @return true if the time got removed or false if the time didn't exist in the schedule
 */
bool TransportStation::removeFromSchedule(Time &time) {
    set<Time>::iterator search = schedule.find(time);
    if(search != schedule.end()){
        schedule.erase(search);
        return true;
    }
    else{
        return false;
    }
}

/**
 * Given a time, searches the schedule for the closest departure
 * @param time Time given
 * @return The earliest departure after the given time
 */
Time TransportStation::getNextDeparture(Time &time){
    if( *schedule.rbegin() < time)
        return *schedule.begin();
    return *(schedule.upper_bound(time));
}

/**
 * Checks if the transportType given is valid.
 * @param transport Transport to be checked
 * @return true if the transport is valid or false otherwise
 */
bool TransportStation::validTransport(string transport) {
    return (transport == "Subway" || transport == "Bus" || transport == "Train");
}

/**
 * Overloaded < operator
 * @param transportStation Transport station to compare to
 * @return true if the Transport station is closer to the airport than the given transport station or false otherwise
 */
bool TransportStation::operator<(const TransportStation &transportStation) const {
    return airportDistance < transportStation.getAirportDistance();
}
