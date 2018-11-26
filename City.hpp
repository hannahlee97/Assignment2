//
// Created by Hannah Lee on 2018-11-25.
//

#ifndef ASSIGNMENT02_CITY_HPP
#define ASSIGNMENT02_CITY_HPP

#include <algorithm>
#include <vector>
#include <string>

using namespace std;

class City {
private:
    string name;
    double x_coordinate;
    double y_coordinate;

public:
    City(string name, double x, double y);
    string getName() { return name; }
    double get_x() const { return x_coordinate; }
    double get_y() const { return y_coordinate; }
    friend bool operator==(const City & lhs, const City & rhs);
    double distance(const City& c);

};


#endif //ASSIGNMENT02_CITY_HPP
