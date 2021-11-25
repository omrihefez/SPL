//
// Created by Omri on 09/11/2021..
//

#include "../include/Trainer.h"
#include <iostream>

using namespace std;
int idCounter = 0;

Trainer::Trainer (int t_capacity) : id(idCounter++), capacity(t_capacity), open(false), salary(0), origCapacity(t_capacity) {}

// Copy Constructor
Trainer::Trainer( Trainer &other) {
    copy(other.capacity, other.open, other.id, other.salary, other.origCapacity, other.customersList, other.orderList);
}

void Trainer::copy(int &other_capacity, bool &other_open, int &other_id, int &other_salary, int &other_origCapacity, vector<Customer*> other_customersList, vector<OrderPair> other_orderList )
{
    capacity = other_capacity;
    open = other_open;
    id = other_id;
    salary = other_salary;
    origCapacity = other_origCapacity;
    for (int i=0 ; i < other_customersList.size() ; i++)
        customersList.push_back(other_customersList[i]);
    for (int j=0 ; j < other_orderList.size() ; j++)
        orderList.push_back(other_orderList[j]);
}

// Copy Assignment
Trainer& Trainer::operator=(Trainer& other) {
    if (this != &other) {
        clear();
        copy(other.capacity, other.open, other.id, other.salary, other.origCapacity,other.customersList,other.orderList);
    }
    return *this;
}

// Destructor
Trainer::~Trainer() { clear(); }

void Trainer::clear() {
    if (!customersList.empty())
        for (int i=0 ; i < customersList.size() ; i++)
            delete (customersList[i]);
}

// Move Constructor
Trainer::Trainer(Trainer&& other)
        : id(other.id), capacity(other.capacity), open(other.open), salary(other.salary), origCapacity(other.origCapacity)
{
    other.capacity = 0 ;
    other.open = false ;
    other.id = -1 ;
    other.salary = 0 ;
    other.origCapacity = 0 ;
    for (int i=0 ; i < customersList.size() ; i++)
        customersList[i] = nullptr;
    customersList.clear();
    orderList.clear();

}

// Move Assignment
Trainer& Trainer::operator=(Trainer &&other){

  for (int i=0 ; i < customersList.size() ; i++) {
      customersList.push_back(other.customersList[i]);
      delete (other.customersList[i]);
  }
  other.customersList.clear();
  orderList = other.orderList;
  other.orderList.clear();
  capacity = other.capacity;
  open = other.open;
  id = other.id;
  salary = other.salary;
  origCapacity = other.origCapacity;

  return *this;
}


int Trainer::getCapacity() const {
    return capacity;
}


void Trainer::addCustomer(Customer *customer) {
    customersList.push_back(customer);
    capacity--;
}

void Trainer::removeCustomer(int id) {
    for (int i=0 ; i < customersList.size() ; i++)
        if (customersList[i]->getId() == id) {
            delete(customersList[i]);
            customersList.erase(customersList.begin() + i);
            capacity++;
        }
    for (int j=0 ; j < orderList.size() ; j++)
        if (orderList[j].first == id){
            salary -= orderList[j].second.getPrice();
            orderList.erase(orderList.begin()+j);
        }
}

Customer *Trainer::getCustomer(int id) {
    for (int i=0 ; i< customersList.size() ; i++)
        if (customersList[i]->getId() == id)
            return customersList[i];
}

std::vector<Customer *> &Trainer::getCustomers() {
    return customersList;
}

std::vector<OrderPair> &Trainer::getOrders() {
    return orderList;
}

void
Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout> &workout_options) {
    for (int i=0 ; i < workout_ids.size() ; i++){
        orderList.push_back(make_pair(customer_id,workout_options[workout_ids[i]]));
        salary += workout_options[workout_ids[i]].getPrice();
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
