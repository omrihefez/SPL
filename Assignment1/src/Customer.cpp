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
    return std::string();
}

CheapCustomer::CheapCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> CheapCustomer::order(const std::vector<Workout> &workout_options) {
    vector<int> orders;
    int cheapestPrice = -1;
    int idToReturn = -1;
    for (vector<Workout>::iterator it = workout_options.begin(); it < workout_options.end(); it++){
        if (it->getPrice() < cheapestPrice){
            idToReturn = it->getId();
            cheapestPrice = it->getPrice();
        }
    }
    if (idToReturn != -1)
        orders.push_back(idToReturn);
    return orders;
}

std::string CheapCustomer::toString() const {
    return std::string();
}

HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id) : Customer(name, id) {

}

bool compareWorkoutByPrice(Workout &a, Workout &b){
    return a.getPrice() > b.getPrice();
}

std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options) {
    std::vector<int> orders;
    vector<Workout> anaerobics;
    for (vector<Workout>::iterator it = workout_options.begin(); it < workout_options.end(); it++){
        if (it->getType() == ANAEROBIC)
            anaerobics.push_back(it);
    }
    std::sort(anaerobics.begin(), anaerobics.end(), compareWorkoutByPrice);
    for (vector<Workout>::iterator it = anaerobics.begin(); it < anaerobics.end(); it++){
        orders.push_back(it->getId());
    }
    return orders;
}



std::string HeavyMuscleCustomer::toString() const {
    return std::string();
}

FullBodyCustomer::FullBodyCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> FullBodyCustomer::order(const std::vector<Workout> &workout_options) {
    return std::vector<int>();
}

std::string FullBodyCustomer::toString() const {
    return std::string();
}


