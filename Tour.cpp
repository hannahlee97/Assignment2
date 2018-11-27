/*
 * C++ Assignment02 Tour.cpp file.
 */
#include <random>
#include <iostream>
#include "Tour.hpp"
#include <algorithm>
#include <set>

using namespace std;

// Number of times a swap must be effected for a shuffle to finish
const int SHUFFLES = 64;
// Number of members randomly selected from the population when choosing a parent
const int PARENT_POOL_SIZE = 5;
// Actual number of parent tours crossed to generate offspring tour
const int NUMBER_OF_PARENTS = 2;
// Mutation rate
const int MUTATION_RATE = 15;

default_random_engine generator(static_cast<long unsigned int>(time(nullptr)));

// Constructor
tour::tour(const tour &t) {
    route = t.route;
    fitness = t.fitness;
}

void tour::adding_city(const City& c) {
    if(!contains_city(c)) {
        route.push_back(c);
    }
}

// Shuffle cities in a tour
void tour::shuffle_cities() {
    uniform_int_distribution<unsigned long> distribution(0, (route.size() - 1));

    for(int i = 0; i < SHUFFLES; ++i) {
        unsigned long first = distribution(generator);
        unsigned long second = distribution(generator);

        City temp = route.at(first);
        route.at(first) = route.at(second);
        route.at(second) = temp;
    }
}

// Represents quality of the tour
// Shorter tours are better quality, have better fitness
double tour::get_fitness() {
    return fitness;
}

// Evaluate distance travelling salesman would need to travel to visit
// the cities in the order they appear in the tour
void tour::determine_fitness() {
    auto itBegin = route.begin();
    auto itNext = route.begin() + 1;
    auto itEnd = route.end();

    double totalDistance = 0;

    for(; itNext != itEnd; ++itBegin, ++itNext) {
        totalDistance += (*itBegin).distance(*itNext);
    }

    itBegin = route.begin();
    totalDistance += (*itBegin).distance(*(route.end() - 1));

    fitness = 1 / totalDistance * 10000;
}

// Checks if tour contains a specified city
bool tour::contains_city(const City& c) {
    auto itBegin = route.begin();
    auto itEnd = route.end();

    for(; itBegin != itEnd; ++itBegin) {
        if((*itBegin) == c) {
            return true;
        }
    }

    return false;
}

// May mutate a tour
void tour::mutate() {
    uniform_int_distribution<int> distribution(0, 100);

    for(int o = 0; o < route.size(); ++o) {
        if(distribution(generator) < MUTATION_RATE) {
            if(o == 0) {
                City temp = route.at(o);
                route.at(o) = route.at(route.size() - 1);
                route.at(route.size() - 1) = temp;
            } else {
                City temp = route.at(o);
                route.at(o) = route.at(o - 1);
                route.at(o - 1) = temp;
            }
        }
    }
}

// Select the parents for new tour from a population
vector<tour> tour::select_parents(const vector<tour>& every) {
    uniform_int_distribution<int> distribution(0, route.size() - 1);
    set<int> potential_parents_1;

    int pool = PARENT_POOL_SIZE;

    if(PARENT_POOL_SIZE > every.size()) {
        pool = every.size();
    }

    while(potential_parents_1.size() < pool) {
        int index = distribution(generator);
        potential_parents_1.insert(index);
    }

    vector<tour> potential_parents_2;

    for(int p : potential_parents_1) {
        potential_parents_2.push_back(every.at(p));
    }

    sort(potential_parents_2.begin(), potential_parents_2.end(), greater<>());

    vector<tour> parents;

    for(int i = 0; i < NUMBER_OF_PARENTS; ++i) {
        parents.push_back(potential_parents_2.at(i));
    }

    return parents;
}

// Creating new tour from given set of parent tours
tour tour::crossover(vector<tour> parents) {
    vector<int> random_index;
    uniform_int_distribution<int> distribution(0, route.size() - 1);

    for(int o = 0; o < parents.size() - 1; ++o) {
        random_index.push_back(distribution(generator));
    }

    sort(random_index.begin(), random_index.end());

    tour t;
    for(int o = 0; o < parents.size(); ++o) {
        if(o == parents.size() - 1) {
            for(int p = 0; p < parents.at(o).route.size(); ++p) {
                t.adding_city(parents.at(o).route.at(p));
            }
        } else if(o == 0) {
            for(int p = 0; p <= random_index.at(o); ++p) {
                t.adding_city(parents.at(o).route.at(p));
            }
        } else {
            for(int p = random_index.at(o - 1); p <= random_index.at(o); ++p) {
                t.adding_city(parents.at(o).route.at(p));
            }
        }
    }
    return t;
}

bool tour::operator<(const tour &rhs) {
    return fitness < rhs.fitness;
}

bool tour::operator>(const tour &rhs) {
    return fitness > rhs.fitness;
}

bool tour::operator=(const tour &rhs) {
    route = rhs.route;
    fitness = rhs.fitness;
}