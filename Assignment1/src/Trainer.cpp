//
// Created by Omri on 09/11/2021..
//

#include "../include/Trainer.h"
#include <iostream>

using namespace std;
static int idCounter = 0;

Trainer::Trainer (int t_capacity) : id(idCounter), capacity(t_capacity), open(false), salary(0), origCapacity(t_capacity) {idCounter++;}

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
    for (size_t i=0 ; i < other_customersList.size() ; i++)
        customersList.push_back(other_customersList[i]);
    for (size_t j=0 ; j < other_orderList.size() ; j++)
        orderList.push_back(other_orderList[j]);
}

// Copy Assignment
Trainer& Trainer::operator=(Trainer& other) {
    if (this != &other) {
        //clear();
        copy(other.capacity, other.open, other.id, other.salary, other.origCapacity,other.customersList,other.orderList);
    }
    return *this;
}

// Destructor
Trainer::~Trainer() { customersList.clear(); }

//void Trainer::clear() {
//    if (!customersList.empty())
//        for (size_t i=0 ; i < customersList.size() ; i++)
//            delete (customersList[i]);
//}

// Move Constructor
Trainer::Trainer(Trainer&& other)
        : id(other.id), capacity(other.capacity), open(other.open), salary(other.salary), origCapacity(other.origCapacity)
{
    other.capacity = 0 ;
    other.open = false ;
    other.id = -1 ;
    other.salary = 0 ;
    other.origCapacity = 0 ;
    for (size_t i=0 ; i < customersList.size() ; i++)
        customersList[i] = nullptr;
    customersList.clear();
    orderList.clear();

}

// Move Assignment
Trainer& Trainer::operator=(Trainer &&other){

  for (size_t i=0 ; i < other.customersList.size() ; i++) {
      customersList.push_back(other.customersList[i]);
//      delete (other.customersList[i]);
  }
  other.customersList.clear();
  for (size_t i = 0; i < other.orderList.size(); i++)
      orderList.push_back(other.orderList[i]);
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
//            delete(customersList[i]);
            customersList.erase(customersList.begin() + i);
            capacity++;
        }
    for (size_t j=0 ; j < orderList.size() ; j++)
        if (orderList[j].first == id){
            salary -= orderList[j].second.getPrice();
            vector<OrderPair> temp;
            for (size_t i = 0; i < orderList.size(); i++)
                if (i != j)
                    temp.push_back(orderList[i]);
            orderList.clear();
            for (size_t i = 0; i < temp.size(); i++)
                orderList.push_back(temp[i]);
            temp.clear();
        }
    if (customersList.empty())
        closeTrainer();
}

Customer *Trainer::getCustomer(int id) {
    for (int i=0 ; i< customersList.size() ; i++)
        if (customersList[i]->getId() == id)
            return customersList[i];
    return nullptr;
}

std::vector<Customer *> &Trainer::getCustomers() {
    return customersList;
}

std::vector<OrderPair> &Trainer::getOrders() {
    return orderList;
}

void
Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout> &workout_options) {
    for (size_t i=0 ; i < workout_ids.size() ; i++){
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
//    for (size_t i=0 ; i < customersList.size() ; i++)
//        delete(customersList[i]);
    customersList.clear();
    orderList.clear();
}

int Trainer::getSalary() {
    return salary;
}

bool Trainer::isOpen() {
    return open;
}
