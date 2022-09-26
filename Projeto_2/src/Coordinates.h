#ifndef FEUP_AED_PROJ2_COORDINATES_H
#define FEUP_AED_PROJ2_COORDINATES_H

#include <cmath>
#include <iostream>

using namespace std;

class Coordinates {
    double latitude;
    double longitude;

public:
    Coordinates() {};
    Coordinates(double latitude, double longitude) : latitude(latitude), longitude(longitude) {};
    double getLatitude() const;
    double getLongitude() const;
    double haversine(Coordinates coordinates);
};

#endif