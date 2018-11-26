//
// Created by Hannah Lee on 2018-11-25.
//

#include "City.hpp"
#include <iostream>
#include <cmath>

using namespace std;

City::City(string name, double x, double y) : name(name), x_coordinate(x), y_coordinate(y) {}

double City::distance(const City& c) {

    return sqrt(pow(c.get_x() - get_x(), 2.0) + pow(c.get_y() - get_y(), 2.0));
}

bool operator==(const City & lhs, const City & rhs) {
    if(lhs.name == rhs.name &&
    lhs.x_coordinate == rhs.x_coordinate &&
    lhs.y_coordinate == rhs.y_coordinate)
        return true;
    return false;
}