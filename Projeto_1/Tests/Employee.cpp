#include "Employee.h"

/**
 * Class Employee constructor.
 * Initializes a new instance of the Employee class using default values
 */
Employee::Employee() = default;

/**
 * Class Employee constructor.
 * Initializes a new instance of the Employee class using the specified name and cardId
 * @param name Name of the employee
 * @param cardId Id of the employee's card
 */
Employee::Employee(string name, int cardId) {
    this->cardId = cardId;
    this->name = name;
}

/**
 * @return The name of the employee
 */
string Employee::getName() const {
    return name;
}

/**
 * Sets the name of the employee to the given name
 * @param name New name of the employee
 */
void Employee::setName(string &name){
    this->name = name;
}

/**
 * @return The id of the employee's card
 */
int Employee::getCardId() const {
    return cardId;
}

/**
 * @return The list of services sorted by date
 */
list<Service> Employee::getServices() {
    services.sort();
    return services;
}

/**
 * Adds the given service to the employee's services list
 * @param service Service to add
 */
void Employee::addService(Service &service) {
    services.push_back(service);
}