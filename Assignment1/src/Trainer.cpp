//
// Created by Omri on 09/11/2021.
//

#include "../include/Trainer.h"

using namespace std;
idCounter = 0;

Trainer::Trainer(int t_capacity) : capacity(t_capacity), open(false), id(idCounter++) {}

int Trainer::getCapacity() const {
    return capacity;
}

&Trainer getTrainer (int _id){
    if (id == _id)
        return &this;
}

void Trainer::addCustomer(Customer *customer) {
    customersList.push_back(customer);
}

void Trainer::removeCustomer(int id) {
    for (int i=0 ; i< customersList.size() ; i++)
        if (customersList[i].getID() == id)
            customersList.erase(customersList[i]);
}

Customer *Trainer::getCustomer(int id) {
    for (int i=0 ; i< customersList.size() ; i++)
        if (customersList[i].getID() == id)
            return customersList[i];
}

std::vector<Customer *> &Trainer::getCustomers() {
    return <#initializer#>;
}

std::vector<OrderPair> &Trainer::getOrders() {
    return <#initializer#>;
}

void
Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout> &workout_options) {

}

void Trainer::openTrainer() {
    if (open)
        throw "Workout session does not exist or is already open.";
    open = true;

}

void Trainer::closeTrainer() {
    open = false;

}

int Trainer::getSalary() {
    return 0;
}

bool Trainer::isOpen() {
    return open;
}
