//
// Created by Omri on 09/11/2021.
//
using namespace std;

#include <algorithm>
#include "../include/Customer.h"

Customer::Customer(std::string c_name, int c_id) : name(c_name), id(c_id) {}

std::string Customer::getName() const {
    return name;
}

int Customer::getId() const {
    return id;
}

Customer::~Customer(){};

SweatyCustomer::SweatyCustomer(std::string name, int id) : Customer(name, id) {}

std::vector<int> SweatyCustomer::order(const std::vector<Workout> &workout_options) {
    std::vector<int> orders;
    for (size_t i = 0; i < workout_options.size(); i++){
        if (workout_options[i].getType() == CARDIO)
            orders.push_back(workout_options[i].getId());
    }
    return orders;
}

std::string SweatyCustomer::toString() const {
    return getName() + " " + ",swt";
}

SweatyCustomer::~SweatyCustomer() {}

CheapCustomer::CheapCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> CheapCustomer::order(const std::vector<Workout> &workout_options) {
    vector<int> orders;
    int cheapestPrice = std::numeric_limits<int>::max();
    int idToReturn = -1;
    for (size_t i = 0; i < workout_options.size(); i++){
        if ((workout_options[i].getPrice() < cheapestPrice) || ((workout_options[i].getPrice() == cheapestPrice) & (workout_options[i].getId() < idToReturn))){
            idToReturn = workout_options[i].getId();
            cheapestPrice = workout_options[i].getPrice();
        }
    }
    if (idToReturn != -1)
        orders.push_back(idToReturn);
    return orders;
}

std::string CheapCustomer::toString() const {
    return getName() + " " + ",chp";
}

CheapCustomer::~CheapCustomer() {}

HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id) : Customer(name, id) {

}


bool sortPairs(const pair<int,int> &x, const pair<int,int> &y){
    return (x.first > y.first) || (x.first == y.first && x.second < y.second);
}

std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options) {
    vector<int> orders;
    vector<pair<int,int>> anaerobics;
    for (size_t i = 0; i < workout_options.size(); i++)
        if (workout_options[i].getType() == ANAEROBIC)
            anaerobics.push_back(make_pair(workout_options[i].getPrice(),workout_options[i].getId()));
    sort(anaerobics.begin(), anaerobics.end(), sortPairs);
    for (size_t j=0 ; j < anaerobics.size() ; j++)
        orders.push_back(anaerobics[j].second);
    return orders;
}


std::string HeavyMuscleCustomer::toString() const {
    return getName() + " " + ",mcl";
}

HeavyMuscleCustomer::~HeavyMuscleCustomer() {}

FullBodyCustomer::FullBodyCustomer(std::string name, int id) : Customer(name, id) {

}

bool compareWorkoutByType(Workout &a, Workout &b){
    return a.getType() > b.getType();
}

std::vector<int> FullBodyCustomer::order(const std::vector<Workout> &workout_options) {
    vector<int> orders;
    int minCardioId = -1;
    int minCardioPrice = numeric_limits<int>::max();
    int minAnaerobicId = -1;
    int minAnaerobicPrice = numeric_limits<int>::max();
    int maxMixedId = -1;
    int maxMixedPrice = numeric_limits<int>::min();

    for (size_t i = 0; i < workout_options.size(); i++) {
        if (workout_options[i].getType() == CARDIO) {
            if ((workout_options[i].getPrice() < minCardioPrice) ||
                ((workout_options[i].getPrice() == minCardioPrice) && (workout_options[i].getId() < minCardioId))) {
                minCardioId = workout_options[i].getId();
                minCardioPrice = workout_options[i].getPrice();
            }
        }
        if (workout_options[i].getType() == ANAEROBIC){
            if ((workout_options[i].getPrice() < minAnaerobicPrice) || ((workout_options[i].getPrice() == minAnaerobicPrice) && (workout_options[i].getId() < minAnaerobicId))){
                minAnaerobicId = workout_options[i].getId();
                minAnaerobicPrice = workout_options[i].getPrice();
            }
        }
        if (workout_options[i].getType() == MIXED){
            if ((workout_options[i].getPrice() > maxMixedPrice) || ((workout_options[i].getPrice() == maxMixedPrice) && (workout_options[i].getId() < maxMixedId))){
                maxMixedId = workout_options[i].getId();
                maxMixedPrice = workout_options[i].getPrice();
            }
        }
    }
    if (minCardioId != -1)
        orders.push_back(minCardioId);
    if (maxMixedId != -1)
        orders.push_back(maxMixedId);
    if (minAnaerobicId != -1)
        orders.push_back(minAnaerobicId);
    return orders;

}

std::string FullBodyCustomer::toString() const {
    return getName() + " " + ",fbd";
}

FullBodyCustomer::~FullBodyCustomer() {}

