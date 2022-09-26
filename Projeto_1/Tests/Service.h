#ifndef UNTITLED2_SERVICE_H
#define UNTITLED2_SERVICE_H

#include <string>
#include "Date.h"

using namespace std;

class Service {
    string type;
    int employeeId;
    Date date;
public:
    Service(string type, int employeeId, string date);
    string getType() const;
    void setType(string type);
    bool validType(const string &type);
    int getEmployeeId() const;
    Date getDate() const;
    void setDate(string date);
    bool operator<(const Service &s) const;
};

class InvalidType : public exception {
public:
    InvalidType() {
        cout << "Invalid type!" << endl;
    }
};

#endif //UNTITLED2_SERVICE_H