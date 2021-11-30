//
// Created by Omri on 09/11/2021..
//

#include "../include/Trainer.h"
#include <iostream>

using namespace std;
static int idCounter = 0;

Trainer::Trainer (int t_capacity) : id(idCounter), capacity(t_capacity), open(false), salary(0), origCapacity(t_capacity),
                                    customersList(), orderList() {idCounter++;}

// Copy Constructor
Trainer::Trainer(const Trainer &other) : id(other.id), capacity(other.capacity), open(other.open), salary(other.salary),
                                    origCapacity(other.origCapacity), customersList(), orderList() {
    copy(other.customersList, other.orderList);
}

void Trainer::copy(vector<Customer*> other_customersList, vector<OrderPair> other_orderList ){
        for (size_t i = 0; i < other_customersList.size(); i++) {
            if (dynamic_cast<SweatyCustomer *>(other_customersList[i])) {
                SweatyCustomer *c = new SweatyCustomer(other_customersList[i]->getName(),
                                                       other_customersList[i]->getId());
                customersList.push_back(c);
            } else if (dynamic_cast<CheapCustomer *>(other_customersList[i])) {
                CheapCustomer *c = new CheapCustomer(other_customersList[i]->getName(),
                                                     other_customersList[i]->getId());
                customersList.push_back(c);
            } else if (dynamic_cast<HeavyMuscleCustomer *>(other_customersList[i])) {
                HeavyMuscleCustomer *c = new HeavyMuscleCustomer(other_customersList[i]->getName(),
                                                                 other_customersList[i]->getId());
                customersList.push_back(c);
            } else { // FullBodyCustomer
                FullBodyCustomer *c = new FullBodyCustomer(other_customersList[i]->getName(),
                                                           other_customersList[i]->getId());
                customersList.push_back(c);
            }
        }
        for (size_t j = 0; j < other_orderList.size(); j++) {
            Workout w = Workout(other_orderList[j].second.getId(), other_orderList[j].second.getName(),
                                other_orderList[j].second.getPrice(), other_orderList[j].second.getType());
            OrderPair o = OrderPair(other_orderList[j].first, w);
            orderList.push_back(o);
        }
}

// Copy Assignment
Trainer& Trainer::operator=(Trainer& other) {
    if (this != &other) {
        id = other.id;
        capacity = other.capacity;
        open = other.open;
        salary = other.salary;
        origCapacity = other.origCapacity;
        copy(other.customersList,other.orderList);
    }
    return *this;
}

// Destructor
Trainer::~Trainer() {
    id = -1;
    capacity = 0;
    open = false;
    salary = 0;
    origCapacity = 0;
    for (size_t i = 0; i < customersList.size(); i++)
        delete customersList[i];
    customersList.clear();
    orderList.clear();
}

// Move Constructor
Trainer::Trainer(Trainer&& other): id(other.id), capacity(other.capacity), open(other.open), salary(other.salary),
                                    origCapacity(other.origCapacity), customersList(), orderList() {
    other.capacity = 0 ;
    other.open = false ;
    other.id = -1 ;
    other.salary = 0 ;
    other.origCapacity = 0 ;
    for (size_t i=0 ; i < customersList.size() ; i++) {
        delete customersList[i];
    }
    customersList.clear();
    orderList.clear();

}

// Move Assignment
Trainer& Trainer::operator=(Trainer &&other){

  for (size_t i=0 ; i < other.customersList.size() ; i++) {
      customersList.push_back(other.customersList[i]);
      other.customersList[i] = nullptr;
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
    std::vector<Customer*> temp;
    for (size_t i = 0 ; i < customersList.size() ; i++) {
        if (customersList[i]->getId() == id) {
            delete customersList[i];
            //customersList.erase(customersList.begin() + i);
            capacity++;
        } else
            temp.push_back(customersList[i]);
    }
    customersList.clear();
    for (size_t i = 0; i < temp.size(); i++)
        customersList.push_back(temp[i]);
    temp.clear();

    removeOrdersOfCustomerById(id);
//    for (size_t j=0 ; j < orderList.size() ; j++)
//        if (orderList[j].first == id){
//            salary -= orderList[j].second.getPrice();
//            vector<OrderPair> temp;
//            for (size_t i = 0; i < orderList.size(); i++)
//                if (i != j)
//                    temp.push_back(orderList[i]);
//            orderList.clear();
//            for (size_t i = 0; i < temp.size(); i++)
//                orderList.push_back(temp[i]);
//            temp.clear();
//        }
    if (customersList.empty())
        closeTrainer();
}

void Trainer::addOrdersAfterMove(std::vector<OrderPair> v){
    for (size_t i = 0 ; i < v.size(); i++){
        orderList.push_back(v[i]);
        salary += v[i].second.getPrice();
    }
}

Customer *Trainer::getCustomer(int id) {
    for (size_t i = 0 ; i< customersList.size() ; i++)
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

std::vector<OrderPair> Trainer::removeOrdersOfCustomerById(int customerId) {
    std::vector<OrderPair> temp;
    std::vector<OrderPair> toReturn;
    for (size_t i = 0; i < orderList.size(); i++){
        if (orderList[i].first != customerId)
            temp.push_back(orderList[i]);
        else {
            salary -= orderList[i].second.getPrice();
            toReturn.push_back(orderList[i]);
        }
    }
    orderList.clear();
    for (size_t i = 0; i < temp.size(); i++){
        orderList.push_back(temp[i]);
    }
    return toReturn;
}

void Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout> &workout_options) {
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
    for (size_t i=0 ; i < customersList.size() ; i++)
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
