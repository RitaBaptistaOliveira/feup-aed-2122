#include "Time.h"

/**
 * Class Time constructor.
 * Initializes a new instance of the Time class with default value 0 for the hours and for the minutes
 */
Time::Time(){
    hours = 0;
    minutes = 0;
}

/**
 * Class Time constructor.
 * Initializes a new instance of the Time class using the specified time if valid.
 * @param time String with the time inf the format hh:mm
 */
Time::Time(string time){
    int hours_temp = stoi(time.substr(0, 2));
    int minutes_temp = stoi(time.substr(3, 2));
    if (validHours(hours_temp) && validMinutes(minutes_temp)){
        hours = hours_temp;
        minutes = minutes_temp;
    }
    else throw InvalidTime();
}

/**
 * Class Time constructor.
 * Initializes a new instance of the Time class using the specified hours and minutes
 * @param hours Hours in 24 hour clock format to be used
 * @param minutes Minutes to be used
 */
Time::Time(int hours, int minutes) {
    if(validHours(hours) && validMinutes(minutes)){
        this->hours = hours;
        this->minutes = minutes;
    }
    else throw InvalidTime();
}

/**
 * @return The Time's hours in a 24 hour clock format
 */
int Time::getHours() const{
    return hours;
}

/**
 * Sets the Time's hours to the given hours
 * @param hours New hours
 */
void Time::setHours(int hours){
    if(validHours(hours))
        this->hours = hours;
    else
        throw InvalidTime();
}

/**
 * @return The Time's minutes
 */
int Time::getMinutes() const{
    return minutes;
}

/**
 * Sets the Time's minutes to the given minutes
 * @param minutes New minutes
 */
void Time::setMinutes(int minutes){
    if(validMinutes(minutes))
        this->minutes = minutes;
    else
        throw InvalidTime();
}

/**
 * Turns the Time into a string with the format "hh:mm"
 * @return The time in string format
 */
string Time::getTime() const {
    string hour = to_string(hours);
    string minute =  to_string(minutes);
    if(hour.size() < 2)
        hour = "0" + hour;
    if(minute.size() < 2)
        minute = "0" + minute;
    return hour + ":" + minute;
}

/**
 * Checks if the hours given are valid
 * @param hours Hours to be checked
 * @return true if the hours are between 0 and 23, inclusive, or false otherwise
 */
bool Time::validHours(int hours) {
    return 0<=hours && hours<=23;
}

/**
 * Checks if the minutes given are valid
 * @param minutes Minutes to be checked
 * @return true if the minutes are between 0 and 59, inclusive, or false otherwise
 */
bool Time::validMinutes(int minutes) {
    return 0<=minutes && minutes<=59;
}

/**
 * Overloaded < operator
 * @param t Time to compare to
 * @return true if Time is earlier than the given time or false otherwise
 */
bool Time::operator<(const Time &t) const{
    if(this->hours == t.hours)
        return this->minutes < t.minutes;
    return this->hours < t.hours;
}

/**
 * Overloaded == operator
 * @param time time to compare to
 * @return  true if the Time's hours and minutes are the same as the hours and minutes of the given time or false otherwise
 */
bool Time::operator==(const Time &time) const{
    return hours == time.getHours() && minutes == time.getMinutes();
}
