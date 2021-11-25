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

SweatyCustomer::SweatyCustomer(std::string name, int id) : Customer(name, id) {}

std::vector<int> SweatyCustomer::order(const std::vector<Workout> &workout_options) {
    std::vector<int> orders;
    for (int i = 0; i < workout_options.size(); i++){
        if (workout_options[i].getType() == CARDIO)
            orders.push_back(workout_options[i].getId());
    }
    return orders;
}

std::string SweatyCustomer::toString() const {
    return getName() + " " + ",swt";
}

CheapCustomer::CheapCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> CheapCustomer::order(const std::vector<Workout> &workout_options) {
    vector<int> orders;
    int cheapestPrice = -1;
    int idToReturn = -1;
    for (size_t i = 0; i < workout_options.size(); i++){
        if (workout_options[i].getPrice() < cheapestPrice | (workout_options[i].getPrice() == cheapestPrice & workout_options[i].getId() < idToReturn)){
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

HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id) : Customer(name, id) {

}

bool compareWorkoutByPrice(Workout &a, Workout &b){
    return a.getPrice() > b.getPrice();
}

bool compareWorkoutByID (Workout &a, Workout &b){
    return a.getId() > b.getId();
}

std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options) {
    std::vector<int> orders;
    vector<Workout> anaerobics;
    for (size_t i = 0; i < workout_options.size(); i++){
        if (workout_options[i].getType() == ANAEROBIC)
            anaerobics.push_back(workout_options[i]);
    }
    std::sort(anaerobics.begin(), anaerobics.end(), compareWorkoutByPrice);
    int currPrice = anaerobics[0].getPrice();
    vector<Workout> samePriceWorkouts;
    for (size_t i = 0; i < anaerobics.size(); i++){
        if (anaerobics[i].getPrice() == currPrice){
            samePriceWorkouts.push_back(anaerobics[i]);
        }
        else {
            sort(samePriceWorkouts.begin(), samePriceWorkouts.end(), compareWorkoutByID);
            while (!samePriceWorkouts.empty()) {
                orders.push_back(samePriceWorkouts[samePriceWorkouts.end()]);
                samePriceWorkouts.pop_back();
            }
        currPrice = anaerobics[i].getPrice();
        samePriceWorkouts.push_back(anaerobics[i]);
        }
    }
    while (!samePriceWorkouts.empty())
        orders.push_back(samePriceWorkouts[samePriceWorkouts.size()-1]);
    return orders;
}


std::string HeavyMuscleCustomer::toString() const {
    return getName() + " " + ",mcl";
}

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
    int maxMixedPrice = numeric_limits<int>::max();

    for (size_t i = 0; i < workout_options.size(); i++) {
        if (workout_options[i].getType() == CARDIO) {
            if (workout_options[i].getPrice() < minCardioPrice |
                (workout_options[i].getPrice() == minCardioPrice && workout_options[i].getId() < minCardioId)) {
                minCardioId = workout_options[i].getId();
                minCardioPrice = workout_options[i].getPrice();
            }
        }
        if (workout_options[i].getType() == ANAEROBIC){
            if (workout_options[i].getPrice() < minAnaerobicPrice | (workout_options[i].getPrice() == minAnaerobicPrice && workout_options[i].getId() < minAnaerobicId){
                minAnaerobicId = workout_options[i].getId();
                minAnaerobicPrice = workout_options[i].getPrice();
            }
        }
        if (workout_options[i].getType() == MIXED){
            if (workout_options[i].getPrice() < maxMixedPrice | (workout_options[i].getPrice() == maxMixedPrice && workout_options[i].getId() < maxMixedId){
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

//    Workout minAnaerobic = Workout(-1,"minAnaerobic",numeric_limits<int>::max(),ANAEROBIC);
//    Workout maxMixed = Workout(-1,"maxMixed",numeric_limits<int>::min(),MIXED);
//    Workout minCardio = Workout(-1,"minCardio",numeric_limits<int>::max(),CARDIO);

//    for (size_t i = 0; i < workout_options.size(); i++){
//        if (workout_options[i].getType() == CARDIO){
//            if (workout_options[i].getPrice() < minCardio.getPrice() | (workout_options[i].getPrice() == minCardio.getPrice() && workout_options[i].getId() < minCardio.getId()))
//                minCardio = workout_options[i];
//        }
//        if (workout_options[i].getType() == ANAEROBIC){
//            if (workout_options[i].getPrice() < minAnaerobic.getPrice() | (workout_options[i].getPrice() == minAnaerobic.getPrice() && workout_options[i].getId() < minAnaerobic.getId()))
//                minAnaerobic = workout_options[i];
//        }
//        if (workout_options[i].getType() == MIXED){
//            if (workout_options[i].getPrice() < maxMixed.getPrice() | (workout_options[i].getPrice() == maxMixed.getPrice() && workout_options[i].getId() < maxMixed.getId()))
//                maxMixed = workout_options[i];
//        }
//    }
//    if (minCardio.getId() != -1)
//        orders.push_back(minCardio.getId());
//    if (maxMixed.getId() != -1)
//        orders.push_back(maxMixed.getId());
//    if (minAnaerobic.getId() != -1)
//        orders.push_back(minAnaerobic.getId());
//    return orders;
}

std::string FullBodyCustomer::toString() const {
    return getName() + " " + ",fbd";
}


