#ifndef UNTITLED2_DATE_H
#define UNTITLED2_DATE_H

#include <iostream>
#include <string>

using namespace std;

class Date {
    unsigned int year;
    unsigned int month;
    unsigned int day;
public:
    Date();
    Date(unsigned int day,unsigned int month, unsigned int year);
    Date(string date);
    unsigned int getYear() const;
    void setYear(unsigned int year);
    unsigned int getMonth() const;
    void setMonth(unsigned int month);
    unsigned int getDay() const;
    void setDay(unsigned int day);
    string getDate() const;
    bool isLeap(unsigned int year);
    bool validDate(int day, int month, int year);
    bool operator<(const Date &d) const;
    bool operator<=(const Date &d) const;
    bool operator==(const Date &d) const;
};

class InvalidDate : public exception{
public:
    InvalidDate() {
        cout << "Invalid date!" << endl;
    }
};

#endif //UNTITLED2_DATE_H
