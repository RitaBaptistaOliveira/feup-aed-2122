#include "Date.h"

const int MAX_VALID_YEAR = 9999;
const int MIN_VALID_YEAR = 1900;

/**
 * Class Date constructor.
 * Initializes a new instance of the Date class with default value 1 for the day and for the month, and MIN_VAlID_YEAR for the year
 */
Date::Date() {
    day = 1;
    month = 1;
    year = MIN_VALID_YEAR;
}

/**
 * Class Date constructor.
 * Initializes a new instance of the Date class using the specified day, month and year if valid
 * @param day Day for the Date
 * @param month Month for the Date
 * @param year Year for the Date
 */
Date::Date(unsigned int day, unsigned int month, unsigned int year) {
    if (validDate(day, month, year)) {
        this->day = day;
        this->month = month;
        this->year = year;
    } else
        throw InvalidDate();
}

/**
 * Class Date constructor.
 * Initializes a new instance of the Date class using the specified date, if valid
 * @param date String with the date in the format dd/mm/yyyy
 */
Date::Date(string date) {
    unsigned int d = stoi(date.substr(0, 2));
    unsigned int m = stoi(date.substr(3, 2));
    unsigned int y = stoi(date.substr(6, 4));
    if (validDate(d, m, y)) {
        day = d;
        month = m;
        year = y;
    }
}

/**
 * @return The Date's year
 */
unsigned int Date::getYear() const {
    return year;
}

/**
 * Sets the Date's year to the given year, if valid
 * @param year New year for the Date
 */
void Date::setYear(unsigned int year) {
    if (validDate(day, month, year))
        this->year = year;
    else
        throw InvalidDate();
}

/**
 * @return The Date's Month
 */
unsigned int Date::getMonth() const {
    return month;
}

/**
 * Sets the Date's month to the given month, if valid
 * @param month New month for the Date
 */
void Date::setMonth(unsigned int month) {
    if (validDate(day, month, year))
        this->month = month;
    else
        throw InvalidDate();
}

/**
 * @return The Date's Day
 */
unsigned int Date::getDay() const {
    return day;
}

/**
 * Sets the Date's day to the given day, if valid
 * @param day New day for the Date
 */
void Date::setDay(unsigned int day) {
    if (validDate(day, month, year))
        this->day = day;
    else
        throw InvalidDate();
}

/**
 * Turns the Date into a string with the format "dd/mm/yyyy"
 * @return The date in string format
 */
string Date::getDate() const {
    string d = to_string(day);
    string m = to_string(month);
    string y = to_string(year);
    if (m.size() < 2)
        m = "0" + m;
    if (d.size() < 2)
        d = "0" + d;
    return d + "/" + m + "/" + y;
}

/**
 * Checks if the year is a leap year
 * @param year Year to be checked
 * @return true if the year is a leap year or false otherwise
 */
bool Date::isLeap(unsigned int year) {
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0)
                return true;
            else
                return false;
        } else
            return true;
    }
    return false;
}

/**
 * Checks if the day, month and year create a valid Date
 * @param day Day to be checked
 * @param month Month to be checked
 * @param year Year to be checked
 * @return true if the given day, month and year form a valid Date or false otherwise
 */
bool Date::validDate(int day, int month, int year) {
    if (year < MIN_VALID_YEAR || year > MAX_VALID_YEAR || month < 1 || month > 12 || day < 1 || day > 31)
        return false;
    if (month == 2) {
        if (isLeap(year)) {
            return (day < 30);
        }
        return (day < 29);
    }
    if (month == 4 || month == 6 || month == 9 || month == 11)
        return (day < 31);
    return true;
}

/**
 * Overloaded < operator
 * @param d Date to compare to
 * @return true if the Date is earlier than the given date or false otherwise
 */
bool Date::operator<(const Date &d) const {
    if (year == d.getYear()) {
        if (month == d.getMonth())
            return day < d.getDay();
        else return month < d.getMonth();
    }
    return year < d.getYear();
}

/**
 * Overloaded <= operator
 * @param d Date to compare to
 * @return true if the Date is earlier or the same as the given date or false otherwise
 */
bool Date::operator<=(const Date &d) const {
    if (year == d.getYear()) {
        if (month == d.getMonth())
            return day <= d.getDay();
        else return month <= d.getMonth();
    }
    return year <= d.getYear();
}

/**
 * Overloaded == operator
 * @param d Date to compare to
 * @return true if the Date is the same as the given date
 */
bool Date::operator==(const Date &d) const {
    return year==d.getYear() && month==d.getMonth() && day==d.getDay();
}

