#include "Coordinates.h"

using namespace std;

/**
 * @return The latitude of the coordinates
 */
double Coordinates::getLatitude() const {
    return latitude;
}

/**
 * @return The longitude of the coordinates
 */
double Coordinates::getLongitude() const {
    return longitude;
}

/**
 * Haversine algorithm.
 * Given two coordinates, it returns the distance between the two locations
 * Time complexity: O(1)
 * @param coordinates Given coordinates
 * @return The distance in meters
 */
double Coordinates::haversine(Coordinates coordinates) {
    double latitude1 = latitude, longitude1 = longitude;
    double latitude2 = coordinates.getLatitude(), longitude2 = coordinates.getLongitude();

    double distanceLatitudes = (latitude2 - latitude1) * M_PI / 180.0;
    double distanceLongitudes = (longitude1 - longitude2) * M_PI / 180.0;

    latitude1 = (latitude1) * M_PI / 180.0;
    latitude2 = (latitude2) * M_PI / 180.0;

    double a = pow(sin(distanceLatitudes / 2), 2) + pow(sin(distanceLongitudes / 2), 2) * cos(latitude1) * cos(latitude2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c * 1000;
}

