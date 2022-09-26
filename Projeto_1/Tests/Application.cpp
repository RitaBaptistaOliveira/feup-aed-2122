#include <algorithm>
#include "Application.h"

/**
 * Class Application constructor.
 * Initializes a new instance of the Application class with default values
 */
Application::Application() = default;


/**
 * Opens all the text files, shows the menu and checks the inputs
 */
void Application::run() {
    getSystemTime();
    readAirport();
    readAirplanes();
    readPassenger();
    readFlights();
    readEmployee();
    readServices();
    readTickets();
    string option;
    do {
        draw_menu();
        getline(cin, option);

        try {
            switch (stoi(option)) {
                case 1:
                    airportMenu();
                    break;
                case 2:
                    airplaneMenu();
                    break;
                case 3:
                    flightMenu();
                    break;
                case 4:
                    buyTicketMenu();
                    break;
                case 5:
                    checkIn();
                    break;
                case 6:
                    cancelTicket();
                    break;
                default:
                    cout << "Please insert a valid option!" << "\n";
                    break;
            }
        }
        catch (invalid_argument) {
            if (stoi(option) != 0) {
                cout << "Please insert a valid option!" << "\n";
                continue;
            }
        }
    } while (stoi(option) != 0);
    storePassengers();
    storeServices();
    storeFlightsAndTickets();
    return;
}

/**
 * Shows the menu to the user
 */
void Application::draw_menu() const {
    cout << "----------MENU----------" << endl << endl;
    cout << "1. Show transport stations" << endl;
    cout << "2. Check airplanes information" << endl;
    cout << "3. Show flights" << endl;
    cout << "4. Buy tickets" << endl;
    cout << "5. Check-in next flight" << endl;
    cout << "6. Cancel a ticket" << endl;
    cout << "0. Exit" << endl;
    cout << "Choose your option: ";
}

/**
 * Shows the Airplane menu options
 */
void Application::showAirplaneOptions() const {
    cout << "----------Options----------" << endl;
    cout << "1. Show Previous Flights" << endl;
    cout << "2. Show Future Flights" << endl;
    cout << "3. Show Previous Services" << endl;
    cout << "4. Show Future Services" << endl;
    cout << "5. Add Flight" << endl;
    cout << "6. Add Service" << endl;
    cout << "0. Exit" << endl;
    cout << "Chose your option: ";
}

/**
 * Option 1 of the main menu: shows the airports.
 * Gives the user the option to see the transport stations near the airport, allows them to check the schedules and checks their inputs
*/
void Application::airportMenu() const {
    string option;
    bool validOption;
    Airport chosenAirport;
    cout << "----------AIRPORTS----------" << endl;
    for (auto airport: airports) {
        cout << "- " << airport.getName() << endl;
    }
    while (!validOption) {
        validOption = false;
        if (!chooseAirport("From which airport?(Insert airport's name):", chosenAirport)) {
            return;
        }
        cout << "1. Find transports stations near the airport" << endl;
        cout << "2. Find the closest departure" << endl;
        cout << "3. Show all transport stations" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose your option: ";
        getline(cin, option);
        try {
            switch (stoi(option)) {
                case 1:
                    validOption = true;
                    cout << "There's a " << chosenAirport.getClosestTransport().getTransportType() << " station "
                         << chosenAirport.getClosestTransport().getAirportDistance();
                    cout << " meters from the airport." << endl << "Here's the schedule: " << endl;
                    showStationSchedule(chosenAirport.getClosestTransport());
                    break;
                case 2: {
                    validOption = true;
                    string op;
                    cout << "At what time would you like to leave?" << endl;
                    getline(cin, op);
                    Time t(op);
                    cout << "The closest departure is at the " << chosenAirport.getNextTransport(t).getTransportType()
                         << " station " << chosenAirport.getNextTransport(t).getAirportDistance();
                    cout << " meters from the airport, at "
                         << chosenAirport.getNextTransport(t).getNextDeparture(t).getTime() << "\n";
                    break;
                }
                case 3: {
                    set<TransportStation> stations = chosenAirport.getStations();
                    set<TransportStation>::iterator it;
                    for (it = stations.begin(); it != stations.end(); it++) {
                        cout << "There's a " << it->getTransportType() << " station " << it->getAirportDistance()
                             << " meters from the airport." << endl << "Here's the schedule: " << endl;
                        showStationSchedule(*it);
                    }
                    break;
                }
                case 0:
                    return;
                default:
                    cout << "Invalid option!" << endl;
                    break;
            }
        }
        catch (invalid_argument) {
            cout << "Insert a valid option!" << "\n";
            continue;
        }
    }
}

/**
 * Option 2 of the main menu: check airplanes information.
 * Gives the user the option to see the previous and future services and flights and to create new services and new flights
*/
void Application::airplaneMenu() {
    cout << "----------Airplanes----------" << endl;
    showAirplanes();
    Airplane chosenAirplane;
    bool validOption = true;
    string option;
    while (validOption) {
        validOption = false;
        if (!chooseAirplane(chosenAirplane))
            return;
        showAirplaneOptions();
        getline(cin, option);
        try {
            switch (stoi(option)) {
                case 1: {
                    validOption = false;
                    chosenAirplane.showPreviousFlights();
                    break;
                }
                case 2: {
                    validOption = false;
                    chosenAirplane.showFutureFlights();
                    break;
                }
                case 3: {
                    validOption = false;
                    chosenAirplane.showPreviousServices();
                    break;
                }
                case 4: {
                    validOption = false;
                    chosenAirplane.showFutureServices();
                    break;
                }
                case 5: {
                    validOption = false;
                    addFlightToAirplane(chosenAirplane);
                    break;
                }
                case 6: {
                    validOption = false;
                    addServiceToAirplane(chosenAirplane);
                    break;
                }
                case 0:
                    validOption = true;
                    break;
                default:
                    validOption = false;
                    cout << "Choose a valid option!" << "\n";
            }
        }
        catch (invalid_argument) {
            cout << "Insert a valid option!" << "\n";
            continue;
        }
    }
    return;
}

/**
 * Option 3 of the main menu: shows the flights.
 * Gives the user the option to see the flights between two airports or between two dates and checks their inputs
*/
void Application::flightMenu() const {
    string option;
    bool validOption = false;
    Airport origin, destination;
    string date1, date2;
    while (!validOption) {
        validOption = false;
        cout << "1. Find all flights between two airports" << endl;
        cout << "2. Find all flights between two dates" << endl;
        cout << "3. Show all flights" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose your option: ";
        getline(cin, option);
        try {
            switch (stoi(option)) {
                case 1: {
                    validOption = true;
                    cout << "----------AIRPORTS----------" << endl;
                    for (auto airport: airports) {
                        cout << "- " << airport.getName() << endl;
                    }
                    chooseAirport("Airport of origin (Insert airport's name): ", origin);
                    chooseAirport("Airport of destination (Insert airport's name): ", destination);
                    showFlightsBetweenTwoAirports(origin, destination);
                    break;
                }
                case 2 : {
                    cout << "Between which dates would you like to see? " << endl;
                    cout << "Date 1: ";
                    getline(cin, date1);
                    Date first(date1);
                    cout << "Date 2: ";
                    getline(cin, date2);
                    Date second(date2);
                    showFlightsBetweenTwoDates(first, second);
                    break;
                }
                case 3:
                    for (auto flight: flights) {
                        cout << "Flight number " << flight.getFlightNumber() << " leaves day " << flight.getDate()
                             << " at " << flight.getDepartureTime() << " and has " << flight.getSeatsLeft()
                             << " seats left." << endl;
                    }
                case 0:
                    return;
                default:
                    cout << "Invalid option!" << endl;
                    break;
            }
        }
        catch (invalid_argument) {
            cout << "Insert a valid option!" << "\n";
            continue;
        }
    }
}

/**
 * Option 4 of the main menu: buy tickets.
 * Gives the user the option to buy one ticket or to by multiple tickets for a group
*/
void Application::buyTicketMenu() {
    Flight flight;
    string option;
    bool validOption = false;
    while (!validOption) {
        try {
            if (!chooseFlight(flight)) return;
        }
        catch (invalid_argument) {
            cout << "Invalid flight" << "\n" << "\n";
            continue;
        }
        cout << "----------Buy Ticket----------" << endl;
        cout << "   1. One ticket" << endl;
        cout << "   2. Group ticket" << endl;
        cout << "   0. Exit" << endl << endl;
        cout << "Choose your option:";
        getline(cin, option);
        try {
            switch (stoi(option)) {
                case 1: {
                    int m = flight.getFlightNumber();
                    if (buyTicket(m)) {
                        cout << "The ticket has been bought!" << endl;
                    } else
                        cout << "There's no room left on the flight!" << endl;
                    validOption = true;
                    break;
                }
                case 2: {
                    cout << "How many tickets? ";
                    getline(cin, option);
                    int n = stoi(option);
                    for (int i = 0; i < n; i++) {
                        if (buyTicket(flight.getFlightNumber())) {
                            cout << "The ticket has been bought!" << endl;
                        } else
                            cout << "There's no room left on the flight!" << endl;
                    }
                    validOption = true;
                    break;
                }
                case 0:
                    return;
            }
        }
        catch (invalid_argument) {
            cout << "Insert a valid option!" << "\n";
            continue;
        }
    }
}

/**
 * Option 5 of the main menu: check-in next flight.
 * Makes the flight with the closest date depart and set the current date to the date of that flight, concluding the services with dates previous to the new date
*/
void Application::checkIn() {
    flights.sort();
    Flight flight;
    list<Flight>::iterator it;
    for (it = flights.begin(); it != flights.end(); it++) {
        Date d(it->getDate());
        if (current < d) {
            if (*it == flights.back()) {
                cout << "There are no more available flights!" << "\n\n";
                return;
            }
            flight = *it;
            break;
        }
    }
    Date date(flight.getDate());
    current = date;
    ofstream current_date;
    current_date.open("Date.txt", ofstream::out | ofstream::trunc);
    if (current_date.is_open()) {
        current_date << current.getDate();
        current_date.close();
    }
    list<Airplane>::iterator itr;
    for (itr = airplanes.begin(); itr != airplanes.end(); itr++) {
        while (itr->getFutureServices().size() != 0 && itr->getFutureServices().front().getDate() <= current) {
            itr->removeFutureService();
        }
    }
    flight.addToConveyorBelt();
    queue<luggage> temp = flight.getConveyorBelt();
    cout << "Conveyor Belt:" << endl;
    for (int i = 0; i < flight.getConveyorBelt().size(); i++) {
        cout << temp.front() << " ";
        temp.pop();
    }
    cout << "\n";
    flight.conveyorBeltToCart();
    cout << "Luggage Cart: " << endl;
    for (auto x: flight.getLuggageCart()) {
        for (auto y: x.getCart()) {
            cout << "|";
            while (!y.empty()) {
                cout << y.top() << " ";
                y.pop();
            }
            cout << "\n";
        }
        cout << "   |\n";
    }
    cout << "  _|__________\n";
    cout << "  |          |\n";
    cout << "(@)          |\n";
    cout << "  |          |\n";
    cout << "  |       ___|\n";
    cout << "(@)      /\n";
    cout << "  |_____/\n";
    cout << endl;
}

/**
 * Opens the file "Date.txt" and reads the current date of the database system
 */
void Application::getSystemTime() {
    ifstream file;
    string date;
    file.open("Date.txt");
    getline(file, date);
    Date d(date);
    current = d;
    file.close();
}

/**
 * Opens the file "Airport.txt" and reads the information about the airports stored in it
 */
void Application::readAirport() {
    ifstream file;
    file.open("Airport.txt");
    string temp;
    while (getline(file, temp)) {
        string airport = getString(temp);
        int maxPiles = stoi(getString(temp));
        int maxLuggage = stoi(temp);
        set<TransportStation> transports = getTransports(airport);
        Airport airport1(airport, transports, maxPiles, maxLuggage);
        airports.push_back(airport1);
    }
    file.close();
}

/**
 * Opens the file "Airplane.txt" and reads the information about the airplanes stored in it;
 */
void Application::readAirplanes() {
    int capacity;
    ifstream file;
    string sAirplane, origin, licencePlate, type;
    file.open("Airplane.txt");
    while (getline(file, sAirplane)) {
        licencePlate = getString(sAirplane);
        type = getString(sAirplane);
        capacity = stoi(getString(sAirplane));
        Airplane airplane(licencePlate, type, capacity);
        airplanes.push_back(airplane);
    }
    file.close();
}

/**
 * Opens the "Passenger.txt" and reads the information about the passengers stored in it
 */
void Application::readPassenger() {
    fstream file;
    file.open("Passengers.txt");
    string person, name;
    int id;
    while (getline(file, person)) {
        id = stoi(getString(person));
        name = getString(person);
        Passenger e(name, id);
        passengers.push_back(e);
    }
    file.close();
}

/**
 * Opens the "Flight.txt" and reads information about the flights stored in it
 */
void Application::readFlights() {
    int duration, airplaneId;
    Airport o, d;
    string flight, date, origin, destination;
    fstream file;
    file.open("Flights.txt");
    while (getline(file, flight)) {
        airplaneId = stoi(getString(flight));
        date = getString(flight);
        duration = stoi(getString(flight));
        origin = getString(flight);
        destination = getString(flight);
        findAirport(origin, o);
        findAirport(destination, d);
        Time time(flight);
        Flight f(date, duration, o, d, time, airplaneId);
        flights.push_back(f);
        Date d1(date);
        list<Airplane>::iterator it = airplanes.begin();
        while (it != airplanes.end()) {
            if (it->getId() == airplaneId) {
                f.setSeatsLeft(it->getCapacity());
                if (d1 < current) {
                    it->addPreviousFlight(f);
                } else {
                    it->addFutureFlight(f);
                }
                break;
            }
            it++;
        }
    }
    file.close();
}

/**
 * Opens the file "Employee.txt" and reads the information about the employees stored in it
 */
void Application::readEmployee() {
    fstream file;
    file.open("Employee.txt");
    string person, name;
    int id;
    while (getline(file, person)) {
        name = getString(person);
        id = stoi(getString(person));
        Employee e(name, id);
        employees.push_back(e);
    }
    file.close();
}

/**
 * Opens the file "Services.txt" and reads the information about the services stored in it
 */
void Application::readServices() {
    fstream file;
    file.open("Services.txt");
    int id;
    string service, licencePlate, type, date;
    while (getline(file, service)) {
        licencePlate = getString(service);
        type = getString(service);
        id = stoi(getString(service));
        date = getString(service);
        Service serviceP(type, id, date);
        Date d(date);
        list<Employee>::iterator it = employees.begin();
        while (it != employees.end()) {
            if (it->getCardId() == id) {
                it->addService(serviceP);
                break;
            }
            it++;
        }
        list<Airplane>::iterator itr = airplanes.begin();
        while (itr != airplanes.end()) {
            if (itr->getLicencePlate() == licencePlate) {
                if (d < current) {
                    itr->addPreviousService(serviceP);
                } else {
                    itr->addFutureService(serviceP);
                }
                break;
            }
            itr++;
        }
    }
    file.close();
}

/**
 * Opens the file "Tickets.txt" and reads the information about the tickets stored in it
 */
void Application::readTickets() {
    fstream file;
    file.open("Tickets.txt");
    int fNumber, id;
    string ticket, l;
    bool luggage;
    while (getline(file, ticket)) {
        fNumber = stoi(getString(ticket));
        l = getString(ticket);
        if (l == "true")
            luggage = true;
        else luggage = false;
        id = stoi(getString(ticket));
        Ticket t(fNumber, luggage, id);
        list<Flight>::iterator it;
        for (it = flights.begin(); it != flights.end(); it++) {
            if (fNumber == it->getFlightNumber()) {
                it->addTicket(t);
                break;
            }
        }
    }
    file.close();
}

/**
 * Shows the information about all the flights between airports a1 and a2
 * @param a1 Origin airport
 * @param a2 Destination airport
 */
void Application::showFlightsBetweenTwoAirports(Airport &a1, Airport &a2) const {
    for (auto it = flights.begin(); it != flights.end(); it++) {
        if (it->getOrigin() == a1 && it->getDestination() == a2) {
            cout << "Flight number " << it->getFlightNumber() << " leaves day " << it->getDate() << " at "
                 << it->getDepartureTime() << " and has " << it->getSeatsLeft() << " seats left." << endl;
        }
    }
}

/**
 * Shows the user the information of all flights between two dates
 * @param date1 First date
 * @param date2 Second date
 */
void Application::showFlightsBetweenTwoDates(Date &date1, Date &date2) const {
    list<Flight>::const_iterator it;
    for (it = flights.begin(); it != flights.end(); it++) {
        Date date(it->getDate());
        if (date1 < date && date < date2) {
            cout << "Flight number " << it->getFlightNumber() << " leaves " << it->getOrigin().getName() << " day "
                 << it->getDate() << " at " << it->getDepartureTime() << " and arrives in "
                 << it->getDestination().getName()
                 << " at " << it->getArrivalTime() << ". It has " << it->getSeatsLeft() << " seats left." << endl;
        }
    }
}

/**
 * Shows the user schedule of the given transport station
 * @param station The given transport station
 */
void Application::showStationSchedule(TransportStation station) const {
    set<Time>::iterator it;
    set<Time> schedule = station.getSchedule();
    for (it = schedule.begin(); it != schedule.end(); it++) {
        cout << it->getTime() << endl;
    }
}

/**
 * Shows the user the information of all airplanes
 */
void Application::showAirplanes() const {
    for (auto airplane: airplanes) {
        cout << "Airplane with licence " << airplane.getLicencePlate()
             << ", type " << airplane.getType() << " and maximum capacity of " << airplane.getCapacity() << " people"
             << endl;
    }
}

/**
 * Shows a string to the user asking for a name of an airport, checks if their input is valid and returns the airport
 * @param str String to show
 * @param airport Airport to be updated
 * @return true if the choosen airport is valid or false if the option is 0
 */
bool Application::chooseAirport(const string &str, Airport &airport) const {
    bool validOption = false;
    string option;
    while (!validOption) {
        cout << str;
        getline(cin, option);
        try {
            int n = stoi(option);
            if (n == 0) break;
        }
        catch (invalid_argument) {
            for (auto a: airports) {
                if (a.getName() == option) {
                    validOption = true;
                    airport = a;
                    break;
                }
            }
            if (!validOption)
                cout << "Pick a valid airport name" << endl;
        }
    }
    return validOption;
}

/**
 * Asks the user for the licence plate of an airplane, checks if their input is valid and returns the airplane
 * @param airplane Airplane to be updated
 * @return true if the airplane is valid or false if the option is 0
 */
bool Application::chooseAirplane(Airplane &airplane) const {
    bool validOption = false;
    string option;
    while (!validOption) {
        cout << endl << "Choose an airplane: (Insert airplane's licence plate)";
        getline(cin, option);
        try {
            size_t size;
            int n;
            const auto num = stoi(option, &size);
            if (option.size() == size) {
                n = stoi(option);
                if (n == 0) break;
            } else throw invalid_argument("");
        }
        catch (invalid_argument) {
            for (auto a: airplanes) {
                if (a.getLicencePlate() == option) {
                    validOption = true;
                    airplane = a;
                }
            }
            if (!validOption)
                cout << "Pick a valid airplane license plate!" << "\n";
        }
    }
    return validOption;
}

/**
 * Asks the user for the flight number of the flight, checks if their input is valid and returns the flight
 * @param flight Flight to be updated
 * @return true if the flight is valid or false if the number 0 is inserted
 */
bool Application::chooseFlight(Flight &flight) const {
    bool validOption = false;
    string option;
    while (!validOption) {
        cout << "From which flight number would you like to buy a ticket? (Insert flight's number)";
        getline(cin, option);
        if (stoi(option) == 0) break;
        for (auto f: flights) {
            Date d(f.getDate());
            if (current < d) {
                if (f.getFlightNumber() == stoi(option)) {
                    validOption = true;
                    flight = f;
                    break;
                }
            }
        }
        if (!validOption)
            cout << "Pick a valid flight number!" << endl;
    }
    return validOption;
}

/**
 * Searches the existing employees list, checks if the id exists and updates the employee with the information of the result
 * @param id Id to search
 * @param employee Employee to update
 * @return true if the employee with the given id exists or false otherwise
 */
bool Application::findEmployee(int id, Employee &employee) {
    for (auto e: employees) {
        if (e.getCardId() == id) {
            employee = e;
            return true;
        }
    }
    return false;
}

/**
 * Searches the existing airports list, checks if the name exists and updates the airport with the information of the result
 * @param airportName Name to search
 * @param airport Airport to update
 * @return
 */
bool Application::findAirport(string &airportName, Airport &airport) {
    for (auto a: airports) {
        if (a.getName() == airportName) {
            airport = a;
            return true;
        }
    }
    return false;
}

/**
 * Find the first word of a string and shortens the original string
 * @param original_s Original string
 * @return The first word
 */
string Application::getString(string &original_s) const {
    unsigned ind = original_s.find(' ');
    string s = original_s.substr(0, ind);
    original_s = original_s.substr(ind + 1);
    return s;
}

/**
 * Opens the file "Stations.txt" of a certain airport and reads the information about the transport stations stored in it
 * @param airport Name of the airport
 * @return A set with the airport's transport stations sorted by distance to the airport
 */
set<TransportStation> Application::getTransports(string airport) {
    fstream stations_file;
    string stations, type;
    stations_file.open(airport + "Stations.txt");
    set<TransportStation> transports;
    while (getline(stations_file, stations)) {
        type = getString(stations);
        int distance = stoi(getString(stations));
        TransportStation transport(type, distance);
        set<Time> schedule;
        size_t ind = stations.find(' ');
        while (ind != string::npos) {
            string time = getString(stations);
            Time t(time);
            schedule.insert(t);
            ind = stations.find(' ');
        }
        Time t(stations);
        schedule.insert(t);
        transport.setSchedule(schedule);
        transports.insert(transport);
    }
    return transports;
}

/**
 * Asks the user for their id (creating a new passenger if they don't already exist), asks them for the ticket information and adds their ticket to the flight's bought tickets list
 * @param fNumber Number of the flight (given previously by the user
 * @return true if the flight has seats left for the passenger or false othewise
 */
bool Application::buyTicket(int fNumber) {
    int id;
    bool luggage, validOption = false, exists = false;
    string sId, sLuggage;
    cout << "Passenger ID:";
    getline(cin, sId);
    id = stoi(sId);
    list<Passenger>::iterator it = passengers.begin();
    while (it != passengers.end()) {
        if (it->getCardId() == id) {
            for (auto flight: flights) {
                if (flight.getFlightNumber() == fNumber) {
                    if (flight.getSeatsLeft() == 0) return false;
                    it->addFlight(flight);
                    break;
                }
            }
            exists = true;
            break;
        }
        it++;
    }
    if (!exists) {
        string name;
        cout << "Name:";
        getline(cin, name);
        Passenger p(name, id);
        for (auto flight: flights) {
            if (flight.getFlightNumber() == fNumber) {
                if (flight.getSeatsLeft() == 0) return false;
                p.addFlight(flight);
                break;
            }
        }
        passengers.push_back(p);
    }
    while (!validOption) {
        cout << "Will you take luggage? (Y/N)";
        getline(cin, sLuggage);
        if (sLuggage == "Y" || sLuggage == "y") {
            luggage = true;
            validOption = true;
        } else if (sLuggage == "N" || sLuggage == "n") {
            luggage = false;
            validOption = true;
        } else validOption = false;
    }
    Ticket t(fNumber, luggage, id);
    list<Flight>::iterator itr = flights.begin();
    while (itr != flights.end()) {
        if (itr->getFlightNumber() == fNumber) {
            itr->addTicket(t);
            break;
        }
        itr++;
    }
    return true;
}

/**
 * Creates a flight using the user's input, checks if they are valid and adds it to the future flights list of the airplane
 * @param airplane Airplane to add the flight to
 */
void Application::addFlightToAirplane(Airplane &airplane) {
    Airport origin, destination;
    string time, sorigin, sdestination, duration;
    string date = askForFutureDate();
    cout << "Departure time:";
    getline(cin, time);
    Time t(time);
    do {
        cout << "Name of the airport of origin:";
        getline(cin, sorigin);
    } while (!findAirport(sorigin, origin));
    do {
        cout << "Name of the airport of destination:";
        getline(cin, sdestination);
    } while (!findAirport(sdestination, destination));
    cout << "Duration:";
    getline(cin, duration);
    Flight f(date, stoi(duration), origin, destination, t, airplane.getId());
    flights.push_back(f);
}

/**
 * Creates a employee using the user's input, checks if they are valid and adds it to the future services list of the airplane
 * @param airplane Airplane to add the service to
 */
void Application::addServiceToAirplane(Airplane &airplane) {
    Employee employee;
    string date = askForFutureDate();
    string employeeId, type;
    do {
        cout << "Employee ID:";
        getline(cin, employeeId);
    } while (findEmployee(stoi(employeeId), employee));
    do {
        cout << "Type of service (Cleaning or Maintenance):";
        getline(cin, type);
    } while (type != "Cleaning" && type != "Maintenance");
    Service s(type, stoi(employeeId), date);
    airplane.addFutureService(s);
}

/**
 * Asks the user for a date and checks if the date is larger than the current date
 * @return The date in string format
 */
string Application::askForFutureDate() {
    string sdate;
    Date date;
    do {
        cout << "Date:";
        getline(cin, sdate);
        Date inputDate(sdate);
        date = inputDate;
    } while (date < current);
    return date.getDate();
}

/**
 * Asks the user for their id and flight number and removes their ticket from the bought tickets list of the flight
 */
void Application::cancelTicket() {
    string sPassengerId, sFNumber;
    int passengerId, fNumber;
    cout << "Passenger id:";
    getline(cin, sPassengerId);
    cout << "Flight number:";
    getline(cin, sFNumber);
    passengerId = stoi(sPassengerId);
    fNumber = stoi(sFNumber);
    for (auto &flight: flights) {
        if (flight.getFlightNumber() == fNumber) {
            flight.removeTicket(passengerId);
        }
    }
}

/**
 * Opens the "Flights.txt" and "Tickets.txt" files and stores the new information in them
 */
void Application::storeFlightsAndTickets() {
    ofstream file, fileTickets;
    file.open("Flights.txt", ofstream::out | ofstream::trunc);
    fileTickets.open("Tickets.txt", ofstream::out | ofstream::trunc);
    list<Flight>::iterator it;
    for (it = flights.begin(); it != flights.end(); it++) {
        file << it->getAirplaneId() << " " << it->getDate() << " " << it->getDuration() << " "
             << it->getOrigin().getName() << " " << it->getDestination().getName() << " " << it->getDepartureTime()
             << endl;
        Date d(it->getDate());
        if (current < d) {
            list<Ticket> t = it->getBoughtTickets();
            string luggage;
            for (auto &ticket: t) {
                if (ticket.getLuggage())
                    luggage = "true";
                else luggage = "false";
                fileTickets << it->getFlightNumber() << " " << luggage << " " << ticket.getPassengerId() << endl;
            }
        }
    }
    file.close();
    fileTickets.close();
}

/**
 * Opens the "Passengers.txt" file and stores the new information in it
 */
void Application::storePassengers() {
    ofstream file;
    file.open("Passengers.txt", ofstream::out | ofstream::trunc);
    list<Passenger>::iterator it;
    for (it = passengers.begin(); it != passengers.end(); it++) {
        file << it->getCardId() << " " << it->getName() << endl;
    }
    file.close();
}

/**
 * Opens the "Services.txt" file and stores the new information in it
 */
void Application::storeServices() {
    ofstream file;
    file.open("Services.txt", ofstream::out | ofstream::trunc);
    list<Service>::iterator it;
    list<Airplane>::iterator itr;
    for (itr = airplanes.begin(); itr != airplanes.end(); itr++) {
        list<Service> p = itr->getPreviousServices();
        for (it = p.begin(); it != p.end(); it++) {
            file << itr->getLicencePlate() << " " << it->getType() << " " << it->getEmployeeId() << " "
                 << it->getDate().getDate() << endl;
        }
        queue<Service> f = itr->getFutureServices();
        while (!f.empty()) {
            file << itr->getLicencePlate() << " " << f.front().getType() << " " << f.front().getEmployeeId() << " "
                 << f.front().getDate().getDate() << endl;
            f.pop();
        }
    }
    file.close();
}