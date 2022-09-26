#ifndef UNTITLED2_TIME_H
#define UNTITLED2_TIME_H

#include <iostream>

using namespace std;

class Time {
    int hours;
    int minutes;
public:
    Time();
    Time(string time);
    Time(int hours, int minutes);
    int getHours() const;
    void setHours(int hours);
    int getMinutes() const;
    void setMinutes(int minutes);
    string getTime() const;
    bool validHours(int hours);
    bool validMinutes(int minutes);
    bool operator<(const Time &time) const;
    bool operator==(const Time &time) const;
};

class InvalidTime : public exception{
public:
    InvalidTime(){
        cout << "Invalid time!" << endl;
    }
};

#endif //UNTITLED2_TIME_H