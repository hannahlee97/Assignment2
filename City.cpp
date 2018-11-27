/*
 * C++ Assignment02 City.cpp file.
 */

#include "City.hpp"
#include <iostream>
#include <cmath>

using namespace std;

City::City(string n, int x, int y) : name(n), position(make_pair(x, y)) { }

int City::get_x() const {
    return position.first;
}

int City::get_y() const {
    return position.second;
}

double City::distance(const City& c) {
    return sqrt(pow(c.get_x() - get_x(), 2) + pow(c.get_y() - get_y(), 2));
}

bool operator==(const City& lhs, const City& rhs) {
    return lhs.name == rhs.name;
}