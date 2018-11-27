/*
 *  C++ Assignment02 Tour.hpp file.
 */

#include <vector>
#include "City.hpp"

using namespace std;

class tour {
    vector<City> route;
    double fitness = 0.0;
public:
    tour() = default;
    tour(const tour& t);
    void adding_city(const City& c);
    void shuffle_cities();
    double get_fitness();
    // Fitness rating
    void determine_fitness();
    bool contains_city(const City& c);
    void mutate();
    vector<tour> select_parents(const vector<tour>& every);
    tour crossover(vector<tour> parents);
    bool operator<(const tour& rhs);
    bool operator>(const tour& rhs);
    bool operator=(const tour& rhs);
};