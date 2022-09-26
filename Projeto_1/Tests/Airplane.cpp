#include "Airplane.h"

/**
 * Initializes the number used to identify the airplane's id
 */
int Airplane::airplaneId = 1;

/**
 * Class Airplane constructor.
 * Initializes a new instance of the Airplane class using default values
 */
Airplane::Airplane() {};

/**
 * Class Airplane constructor.
 * Initializes a new instance of the Airplane class using the specified licencePlate, type and capacity
 * @param licencePlate Licence plate of the airplane
 * @param type Type of the airplane
 * @param capacity Maximum capacity of the airplane
 */
Airplane::Airplane(string licencePlate, string type, int capacity) {
    this->capacity = capacity;
    this->licencePlate = licencePlate;
    this->type = type;
    this->id = airplaneId;
    airplaneId++;
}

/**
 * @return The id of the airplane
 */
int Airplane::getId() const {
    return id;
}

/**
 * @return The capacity of the airplane
 */
int Airplane::getCapacity() const {
    return capacity;
}

/**
 * @return The type of the airplane
 */
string Airplane::getType() const {
    return type;
}

/**
 * Sets the type of the airplane to the given type
 * @param type New airplane type
 */
void Airplane::setType(const string &type) {
    this->type = type;
}

/**
 * @return The licence plate of the airplane
 */
string Airplane::getLicencePlate() const {
    return licencePlate;
}

/**
 * Sets the licence plate of the airplane to the given licence plate
 * @param licencePlate New licence plate
 */
void Airplane::setLicencePlate(const string &licencePlate) {
    this->licencePlate = licencePlate;
}

/**
 * @return The queue of the airplane's future flights
 */
queue<Flight> Airplane::getFutureFlights() const {
    return futureFlights;
}

/**
 * Adds a new flight to the airplane's queue of future flights
 * @param flight New flight
 */
void Airplane::addFutureFlight(Flight &flight) {
    futureFlights.push(flight);
}

/**
 * @return The list of the airplane's previous flights
 */
list<Flight> Airplane::getPreviousFlights() const {
    return previousFlights;
}

/**
 * Adds an old flight to the airplane's list of previous flights
 * @param flight Old flight
 */
void Airplane::addPreviousFlight(Flight &flight) {
    previousFlights.push_back(flight);
}

/**
 * @return The queue of the airplane's future services
 */
queue<Service> Airplane::getFutureServices(){
    return futureServices;
}

/**
 * Adds a service to the airplane's future services
 * @param service New service
 */
void Airplane::addFutureService(const Service &service) {
    futureServices.push(service);
}

/**
 * Once a service has been concluded, that service is removed from the futureServices queue and added to the previousServices list
 */
void Airplane::removeFutureService() {
    Service s = futureServices.front();
    futureServices.pop();
    previousServices.push_back(s);
}

/**
 * @return The list of the airplane's previous services
 */
list<Service> Airplane::getPreviousServices() {
    return previousServices;
}

/**
 * Adds the given service to the previous services list
 * @param service Service to add
 */
void Airplane::addPreviousService(Service &service) {
    previousServices.push_back(service);
}

/**
 * Once the airplane has landed in its current flight's destination, that flight is removed from the futureFlights queue and added to the previousFlights list
 */
void Airplane::flightDeparture() {
    Flight f = futureFlights.front();
    futureFlights.pop();
    previousFlights.push_back(f);
}

/**
 * Shows the user the airplane's previous flights list
 */
void Airplane::showPreviousFlights() const {
    if(previousFlights.size()==0) {
        cout << "This airplane has no previous flights!" << "\n" << "\n";
        return;
    }
    for (Flight flight: previousFlights) {
        cout << "Flight number " << flight.getFlightNumber() << " departed from " << flight.getOrigin().getName()
             << " on the day " << flight.getDate() << " at " <<
             flight.getDepartureTime() << " and arrived at " << flight.getDestination().getName()
             << " at " << flight.getArrivalTime() << endl;
    }
}

/**
 * Shows the user the airplane's future flights queue
 */
void Airplane::showFutureFlights() const{
    queue<Flight> f = futureFlights;
    int n = f.size();
    while (n != 0) {
        Flight flight = f.front();
        f.pop();
        cout << "Flight number " << flight.getFlightNumber() << " will depart from "
             << flight.getOrigin().getName() <<
             " on the day " << flight.getDate() << " at " << flight.getDepartureTime()
             << " and will arrived at " << flight.getDestination().getName() <<
             " at " << flight.getArrivalTime() << endl;
        n--;
    }
}

/**
 * Shows the user the airplane's previous services list
 */
void Airplane::showPreviousServices() const{
    for (auto service : previousServices) {
        cout << service.getType() << " service made by employee number " << service.getEmployeeId()
             << " on the day " << service.getDate().getDate() << endl;
    }
}

/**
 * Shows the user the airplane's future services queue
 */
void Airplane::showFutureServices() const{
    queue<Service> services = futureServices;
    int n = services.size();
    while (n != 0) {
        Service s = services.front();
        services.pop();
        cout << s.getType() << " service will be made by employee number " << s.getEmployeeId()
             << " on the day " << s.getDate().getDate() << endl;
        n--;
    }
}