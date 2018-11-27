/*
 * C++ Assignment02 Main.cpp file.
 */
#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <random>
#include <vector>
#include <algorithm>
#include "City.hpp"
#include "Tour.hpp"

using namespace std;

int main() {
    const int CITIES_IN_TOUR = 32;
    const int POPULATION_SIZE = 32;
    const int MAP_BOUNDARY = 1000;
    const int NUM_OF_ELITES = 1;
    const int IMPROVEMENT_FACTOR = 2;

    map<int, City> master_list;
    vector<tour> population(POPULATION_SIZE);

    default_random_engine generator(static_cast<long unsigned int>(time(nullptr)));
    uniform_int_distribution<int> distribution(0, MAP_BOUNDARY);

    //Initialize master list with cities that have random coordinates
    for(int i = 0; i < CITIES_IN_TOUR; ++i) {
        City c("City" + to_string(i), distribution(generator), distribution(generator));
        master_list.insert(make_pair(i, c));
    }

    //Create tours with random order of cities
    for(int i = 0; i < POPULATION_SIZE; ++i) {
        tour t;
        for(int o = 0; o < CITIES_IN_TOUR; ++o) {
            t.adding_city(master_list.at(o));
        }
        t.shuffle();
        t.determine_fitness();
        population.at((unsigned long)i) = t;
    }

    sort(population.begin(), population.end(), greater<>());

    //Start of Genetic Algorithm
    double base_distance = population.at(0).get_fitness();
    double best_distance = base_distance;
    int generation = 0;
    double improvement;

    while((improvement = best_distance / base_distance) <= IMPROVEMENT_FACTOR) {
        cout << "Generation " << generation << " Best : " << best_distance << " Improvement : " << improvement << endl;

        for(int i = NUM_OF_ELITES; i < population.size(); ++i) {
            population.at(i) = population.at(i).crossover(population.at(i).select_parents(population));
            population.at(i).mutate();
            population.at(i).determine_fitness();
        }

        sort(population.begin(), population.end(), greater<>());
        best_distance = population.at(0).get_fitness();
        ++generation;
    }

    cout << endl << "Improvment factor has been reached :" << endl;
    cout << "Generation " << generation << " Base : " << base_distance << " Best : " << best_distance << " Improvement : " << improvement << endl;

    return 0;
}