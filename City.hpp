/*
 * C++ Assignment02 City.hpp file.
 */

#ifndef ASSIGNMENT02_CITY_HPP
#define ASSIGNMENT02_CITY_HPP

#include <algorithm>
#include <vector>
#include <string>

using namespace std;

class City {
    string name;
    pair<int, int> position;
public:
    City(string n, int x, int y);
    int get_x() const;
    int get_y() const;
    double distance(const City& c);
    friend bool operator==(const City& lhs, const City& rhs);
};


#endif //ASSIGNMENT02_CITY_HPP
