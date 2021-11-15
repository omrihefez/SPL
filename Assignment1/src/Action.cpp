//
// Created by Omri on 09/11/2021.
//

#include "../include/Action.h"

BaseAction::BaseAction() {}

ActionStatus BaseAction::getStatus() const {return status;}

OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList): BaseAction(),
trainerId(id), customers(customersList) {}

void OpenTrainer::act(Studio &studio) {}

std::string OpenTrainer::toString() const {
    std::string s = "";
    return s;
}

Order::Order(int id): BaseAction(), trainerId(id) {}

void Order::act(Studio &studio) {}

std::string Order::toString() const {
    std::string s = "";
    return s;
}