//
// Created by Omri on 09/11/2021.
//

#include "../include/Trainer.h"

Trainer::Trainer(int t_capacity) : capacity(t_capacity), open(false) {}

int Trainer::getCapacity() const {
    return capacity;
}

void Trainer::addCustomer(Customer *customer) {

}

void Trainer::removeCustomer(int id) {

}

Customer *Trainer::getCustomer(int id) {
    return nullptr;
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
