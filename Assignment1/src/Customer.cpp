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

SweatyCustomer::SweatyCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> SweatyCustomer::order(const std::vector<Workout> &workout_options) {
    std::vector<int> orders;
    vector<Workout>::iterator it;
    for (it = workout_options.begin(); it < workout_options.end(); it++){
        if (it->getType() == CARDIO)
            orders.push_back(it->getId());
    }
    return orders;
}

std::string SweatyCustomer::toString() const {
    return name+"swt";
}

CheapCustomer::CheapCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> CheapCustomer::order(const std::vector<Workout> &workout_options) {
    vector<int> orders;
    int cheapestPrice = -1;
    int idToReturn = -1;
    for (vector<Workout>::iterator it = workout_options.begin(); it < workout_options.end(); it++){
        if (it.getPrice() < cheapestPrice | (it.getPrice() == cheapestPrice & it.getId < idToReturn)){
            idToReturn = it.getId();
            cheapestPrice = it.getPrice();
        }
    }
    if (idToReturn != -1)
        orders.push_back(idToReturn);
    return orders;
}

std::string CheapCustomer::toString() const {
    return name+"chp";
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
    for (vector<Workout>::iterator it = workout_options.begin(); it < workout_options.end(); it++){
        if (it.getType() == ANAEROBIC)
            anaerobics.push_back(it);
    }
    std::sort(anaerobics.begin(), anaerobics.end(), compareWorkoutByPrice);
    int currPrice = anaerobics.begin().getPrice();
    vector<Workout> samePriceWorkouts;
    for (vector<Workout>::iterator it = anaerobics.begin(); it < anaerobics.end(); it++){
        if (it.getPrice() == currPrice){
            samePriceWorkouts.push_back(it);
        }
        else {
            sort(samePriceWorkouts.begin(), samePriceWorkouts.end(), compareWorkoutByID);
            while (!samePriceWorkouts.empty()) {
                orders.push_back(samePriceWorkouts[samePriceWorkouts.size()-1]);
                samePriceWorkouts.pop_back();
            }
        currPrice = it.getPrice();
        samePriceWorkouts.push_back(it);
        }
    }
    while (!samePriceWorkouts.empty())
        orders.push_back(samePriceWorkouts[samePriceWorkouts.size()-1]);
    return orders;
}


std::string HeavyMuscleCustomer::toString() const {
    return name+"mcl";
}

FullBodyCustomer::FullBodyCustomer(std::string name, int id) : Customer(name, id) {

}

bool compareWorkoutByType(Workout &a, Workout &b){
    return a.getType() > b.getType();
}

std::vector<int> FullBodyCustomer::order(const std::vector<Workout> &workout_options) {
    vector<int> orders;
    Workout minCardio = new Workout(-1,minCardio,numeric_limits<int>::max();,MIXED);
    Workout minAnaerobic = new Workout(-1,minCardio,numeric_limits<int>::max();,MIXED);
    Workout maxMixed = new Workout(-1,minCardio,numeric_limits<int>::min();,MIXED);
    for (vector<Workout>::iterator it = workout_options.begin(); it < workout_options.end(); it++){
        if (it.getType() == CARDIO){
            if (it.getPrice() < minCardio.getPrice() | (it.getPrice() == minCardio.getPrice() && it.getId() < minCardio.getId()))
                minCardio = it;
        }
        if (it.getType() == ANAEROBIC){
            if (it.getPrice() < minAnaerobic.getPrice() | (it.getPrice() == minAnaerobic.getPrice() && it.getId() < minAnaerobic.getId()))
                minAnaerobic = it;
        }
        if (it.getType() == MIXED){
            if (it.getPrice() < maxMixed.getPrice() | (it.getPrice() == maxMixed.getPrice() && it.getId() < maxMixed.getId()))
                maxMixed = it;
        }
    }
    if (minCardio.getId() != -1)
        orders.push_back(minCardio.getId());
    if (maxMixed.getId() != -1)
        orders.push_back(maxMixed.getId());
    if (minAnaerobic.getId() != -1)
        orders.push_back(minAnaerobic.getId());
}

std::string FullBodyCustomer::toString() const {
    return name+"fbd";
}


