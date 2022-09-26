#ifndef UNTITLED2_EMPLOYEE_H
#define UNTITLED2_EMPLOYEE_H

#include <iostream>
#include <list>
#include "Service.h"

using namespace std;

class Employee {
    string name;
    int cardId;
    list<Service> services;
public:
    Employee();
    Employee(string name, int cardId);
    string getName() const;
    void setName(string &name);
    int getCardId() const;
    list<Service> getServices();
    void addService(Service &service);
};

#endif //UNTITLED2_EMPLOYEE_H
