//
// Created by Omri on 09/11/2021.
//

#include "../include/Trainer.h"

using namespace std;
int idCounter = 0;

Trainer::Trainer (int t_capacity) : capacity(t_capacity), open(false), id(idCounter++), salary(0), origCapacity(t_capacity) {}

// Copy Constructor
Trainer::Trainer(const Trainer& other) { copy(other.capacity, other.open, other.id, other.salary, other.origCapacity); }

// Copy Assignment
Trainer& Trainer::operator=(const Trainer& other) {
    if (this != &other) {
        clear();
        copy(other.capacity, other.open, other.id, other.salary, other.origCapacity);
    }
    return *this;
}

int Trainer::getCapacity() const {
    return capacity;
}

&Trainer getTrainer (int _id){
    if (id == _id)
        return &this;
}

void Trainer::addCustomer(Customer *customer) {
    customersList.push_back(customer);
    capacity--;
}

void Trainer::removeCustomer(int id) {
    for (int i=0 ; i < customersList.size() ; i++)
        if (customersList[i].getID() == id) {
            delete(customersList[i]);
            customersList.erase(customersList[i]);
            capacity++;
        }
    for (int j=0 ; j < orderList.size() ; j++)
        if (orderList[j][1] == id){
            salary -= orderlist[j][1].getPrice();
            orderList.erase(orderList[j]);
        }

}

Customer *Trainer::getCustomer(int id) {
    for (int i=0 ; i< customersList.size() ; i++)
        if (customersList[i].getID() == id)
            return customersList[i];
}

std::vector<Customer *> &Trainer::getCustomers() {
    return &customersList;
}

std::vector<OrderPair> &Trainer::getOrders() {
    return &orderList;
}

void
Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout> &workout_options) {
    for (int i=0 ; i < workout_ids.size() ; i++){
        orderList.push_back(customer_id,workout_options[workout_id[i]]);
        salary += workout_options[workout_id[i]].getPrice();
    }
}

void Trainer::openTrainer() {
    if (open)
        throw "Workout session does not exist or is already open.";
    open = true;

}

void Trainer::closeTrainer() {
    open = false;
    capacity = origCapacity;
    for (int i=0 ; i < customersList.size() ; i++)
        delete(customersList[i]);
    customersList.clear();
    orderList.clear();
}

int Trainer::getSalary() {
    return salary;
}

bool Trainer::isOpen() {
    return open;
}
