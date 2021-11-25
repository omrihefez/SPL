//
// Created by Omri on 09/11/2021.
//

#include "../include/Action.h"

extern Studio* backup;

BaseAction::BaseAction() {}

ActionStatus BaseAction::getStatus() const {return status;}

void BaseAction::complete() {status = COMPLETED;}

void BaseAction::error(int errorMsg) {status = ERROR; this.errorMsg = errorMsg;}

OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList): BaseAction(),
trainerId(id), customers(customersList) {}

void OpenTrainer::act(Studio &studio) {
    (studio.getActionLog).push_back(this);
    Trainer* t = studio.getTrainer(trainerId);
    if (t == nullptr || t->isOpen()){
        error("Workout session does not exist or is already open.");
    }
    else{
        std::vector<Customer *>::iterator iter = customers.begin();
        while (t->getCapacity()>0){
            t->addCustomer(iter);
            iter++;
        }
    complete();
    }
}


std::string OpenTrainer::toString() const {
    std::string s = "open" + std::to_string(trainerId) + " ";
    for(std::vector<Customer*>s::iterator i = customers.begin(); i != customers.end(); i++)
        s += " " + i.toString();
    }
    return s;
}

Order::Order(int id): BaseAction(), trainerId(id) {}

void Order::act(Studio &studio) {
    (studio.getActionLog).push_back(this);
    Trainer* t = studio.getTrainer(trainerId);
    if (t == nullptr || !(t->isOpen())){
        error("Workout session does not exist or is already open.");
    }
    else{
        std::vector<Workout>& options = studio.getWorkoutOptions();
        std::vector<Customer *>&::iterator iter = (t->getCustomers()).begin();
        while (iter != (t->getCustomers()).end()){
            std::vector<int> o = iter->Customer::order();
            t->order(iter.getId(), o, options);
            }
        complete();
        }

}

std::string Order::toString() const {
    return "order " + trainerId;
}

MoveCustomer::MoveCustomer(int src, int dst, int customerId): BaseAction(), srcTrainer(src),
dstTrainer(dst), id(customerId){}

void MoveCustomer::act(Studio &studio) {
    (studio.getActionLog).push_back(this);
    Trainer *sTrainer = studio.getTrainer(srcTrainer);
    Trainer *dTrainer = studio.getTrainer(dstTrainer);
    if (sTrainer == nullptr | dTrainer == nullptr ||
        !sTrainer->isOpen() | !dTrainer->isOpen() | sTrainer->getCustomer(id) == nullptr | dTrainer->getCapacity() == 0)
        error("Cannot move customer.");
    else {
        Costumer *c = sTrainer->getCustomer(id);
        sTrainer->removeCustomer(id);

        dTrainer->addCustomer(c);
        complete();
    }
}

std::string MoveCustomer::toString() const {
    return "move " + srcTrainer + dstTrainer + id;
}

Close::Close(int id): BaseAction(), trainerId(id) {}

void Close::act(Studio &studio) {
    (studio.getActionLog).push_back(this);
    Trainer* t = studio.getTrainer(trainerId);
    if (t == nullptr || !(t->isOpen())) {
        error("Trainer does not exist or is not open");
    }
    else {
        t->closeTrainer();
        cout << "Trainer " << id << " is closed. Salary " << t->getSalary() << "NIS" << endl;
        complete();
    }
}

std::string Close::toString() const {
    return "close " + trainerId;
}

CloseAll::CloseAll(): BaseAction() {}

void CloseAll::act(Studio &studio) {
    (studio.getActionLog).push_back(this);
    int numOfTrainers = studio.getNumOfTrainers();
    for (int i = 0; i < numOfTrainers; i++){
        Trainer* t = studio.getTrainer(i);
        if (t->isOpen()) {
            Close closeT = Close::Close(i);
            closeT.act(studio);
        }
        delete t;
        t = nullptr;
        complete();
    }
}

int CloseAll::toString() const {
    return "closeall";
}

PrintWorkoutOptions::PrintWorkoutOptions(): BaseAction() {}

void PrintWorkoutOptions::act(Studio &studio) {
    (studio.getActionLog).push_back(this);
    std::vector<Workout>& options = studio.getWorkoutOptions();
    std::vector<Workout>&::iterator iter = options.begin();
    while(iter != options.end()){
        cout << iter.getName() << ", " << iter.getType << ", " << iter.getPrice << endl;
        iter++;
    }
    complete();
}

int PrintWorkoutOptions::toString() const {
    return "workout_options";
}

PrintTrainerStatus::PrintTrainerStatus(int id): BaseAction(), trainerId(id) {}

void PrintTrainerStatus::act(Studio &studio) {
    (studio.getActionLog()).push_back(this);
    Trainer* t = studio.getTrainer(trainerId);
    std::string status = t->isOpen() ? "open" : "closed";
    cout << "Trainer " << trainerId << " status: " << status << endl;
    if (t->isOpen()){
        cout << "Costumers:" << endl;
        vector<Costumer *> &c = t->getCustomers();
        for (std::vector<Costumer*>::iterator i = c.begin(); i != c.end(); i++)
            cout << i.getId() << " " << i.getName() << endl;
        vector<OrderPair>& orders = t->getOrders();
        for (std::vector<OrderPair>::iterator i = orders.begin(); int != orders.end(); i++){
            cout << i.second.getName() << " " < i.second.getPrice() << "NIS " << i.first << endl;
        }
        cout << "Current Trainer's Salary: " << t->getSalary() <<"NIS" << endl;
    }
    complete();
}

int PrintTrainerStatus::toString() const {
        return "status " + trainerId;
    }

PrintActionsLog::PrintActionsLog(): BaseAction() {}

void PrintActionsLog::act(Studio &studio) {
    std::vector<BaseAction*>& log = studio.getActionsLog();
    for (std::vector<BaseAction*>::iterator i = log.begin(); i != log.end; i++){
        string status = i.getStatus() == COMPLETED ? "Completed" : "Error: " + i.getErrorMsg();
        cout << i->toString() << " " << status << endl;
    }
    (studio.getActionLog).push_back(this);
    complete();
}

int PrintActionsLog::toString() const {return "log";}

BackupStudio::BackupStudio(): BaseAction() {}

void BackupStudio::act(Studio &studio) {
    (studio.getActionLog).push_back(this);
    backup = studio;
    complete();
}

int BackupStudio::toString() const {return "backup";}

RestoreStudio::RestoreStudio(): BaseAction() {}

void RestoreStudio::act(Studio &studio) {
    (studio.getActionLog).push_back(this);
    if (backup == nullptr)
        error("No backup available");
    else {
        studio = backup;
        complete();
    }
}

int RestoreStudio::toString() const {return "restore";}





