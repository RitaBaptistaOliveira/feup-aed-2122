#include "Service.h"

/**
 * Class Service constructor.
 * Initializes a new instance of the Service class using the specified type, employeeName and date.
 * @param type Type of the service (has to be Cleaning or Maintenance to be valid)
 * @param employeeId Id of the employee's card that is going to make the Service
 * @param date Date of the Service
 */
Service::Service(string type, int employeeId, string date) {
    if (validType(type)) {
        this->type = type;
        setDate(date);
        this->employeeId = employeeId;
    }
    else{
        throw InvalidType();
    }
}

/**
 * @return Returns the type of the Service (Maintenance or Cleaning)
 */
string Service::getType() const {
    return type;
}

/**
 * Sets the type of the Service to the given type if it is valid
 * @param type New type for the Service
 */
void Service::setType(string type) {
    if(validType(type)) {
        this->type = type;
    }
    else{
        throw InvalidType();
    }
}

/**
 * Checks if the type of the Service is valid
 * @param type Type to be checked
 * @return true if the type is either Maintenance or Cleaning or false otherwise
 */
bool Service::validType(const string &type) {
    if (type == "Maintenance" || type == "Cleaning") {
        return true;
    }
    return false;
}

/**
 * @return The id of the employee's card that made/is going to make the Service
 */
int Service::getEmployeeId() const {
    return employeeId;
}

/**
 * @return The date of the Service
 */
Date Service::getDate() const {
    return date;
}

/**
 * Sets the date of the Service to the given date
 * @param date New date for the Service
 */
void Service::setDate(string date) {
    Date tempDate(date);
    this->date = tempDate;
}

/**
 * Overloaded < operator
 * @param s Service to compare to
 * @return true if the date of the Service is earlier than the date of the given service or false otherwise
 */
bool Service::operator<(const Service &s) const {
    return date < s.getDate();
}
