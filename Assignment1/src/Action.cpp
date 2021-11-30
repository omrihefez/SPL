//
// Created by Omri on 09/11/2021.
//

#include "../include/Action.h"
#include "../include/Studio.h"
using namespace std;
extern Studio* backup;

BaseAction::BaseAction() : errorMsg(""), status(ERROR) {}

ActionStatus BaseAction::getStatus() const {return status;}

void BaseAction::complete() {status = COMPLETED;}

void BaseAction::error(std::string errorMsg) {status = ERROR; this->errorMsg = errorMsg;}

std::string BaseAction::getErrorMsg() const {
    return errorMsg;
}

BaseAction::~BaseAction() {}

OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList): BaseAction(),
trainerId(id), customers(customersList) {}

void OpenTrainer::act(Studio &studio) {
    Trainer* t = studio.getTrainer(trainerId);
    if (t == nullptr || t->isOpen()){
        error("Workout session does not exist or is already open.");
    }
    else{
        t->openTrainer();
        int i = 0;
        if ((size_t)t->getCapacity() < customers.size())
            for (size_t j = t->getCapacity(); j < customers.size(); j++)
                delete customers[j];
        while ((t->getCapacity() > 0) & ((size_t)i < customers.size())){
            t->addCustomer(customers[i]);
            i++;
        }
    complete();
    }
    t = nullptr;
}


std::string OpenTrainer::toString() const {
    std::string s = "open " + std::to_string(trainerId);
    for(size_t i = 0 ; i < customers.size() ; i++)
        s += " " + customers[i]->toString();
    if (getStatus() == COMPLETED)
        s += " Completed";
    else
        s += " Error: " + getErrorMsg();
    return s;
}

OpenTrainer::~OpenTrainer() {}

int OpenTrainer::getTrainerId() {return trainerId;}

std::vector<Customer *>& OpenTrainer::getCustomers() {return customers;}

BaseAction& OpenTrainer::clone() {
    vector<Customer*> c;
    for (size_t i = 0; i < this->getCustomers().size(); i++){
        if (dynamic_cast<SweatyCustomer *>(this->getCustomers()[i])) {
            SweatyCustomer *c1 = new SweatyCustomer(this->getCustomers()[i]->getName(),
                                                    this->getCustomers()[i]->getId());
            c.push_back(c1);
        } else if (dynamic_cast<CheapCustomer *>(this->getCustomers()[i])) {
            CheapCustomer *c1 = new CheapCustomer(this->getCustomers()[i]->getName(),
                                                  this->getCustomers()[i]->getId());
            c.push_back(c1);
        } else if (dynamic_cast<HeavyMuscleCustomer *>(this->getCustomers()[i])) {
            HeavyMuscleCustomer *c1 = new HeavyMuscleCustomer(this->getCustomers()[i]->getName(),
                                                              this->getCustomers()[i]->getId());
            c.push_back(c1);
        } else { // FullBodyCustomer
            FullBodyCustomer *c1 = new FullBodyCustomer(this->getCustomers()[i]->getName(),
                                                        this->getCustomers()[i]->getId());
            c.push_back(c1);
        }
    }
    OpenTrainer* o = new OpenTrainer(this->getTrainerId(), c);
    return *o;
}

Order::Order(int id): BaseAction(), trainerId(id) {}

void Order::act(Studio &studio) {
    Trainer* t = studio.getTrainer(trainerId);
    if (t == nullptr || !(t->isOpen())){
        error("Workout session does not exist or is already open.");
    }
    else{
        std::vector<Workout>& options = studio.getWorkoutOptions();
        for (size_t i = 0; i < t->getCustomers().size(); i++){
            std::vector<int> o = t->getCustomers()[i]->order(options);
            t->order(t->getCustomers()[i]->getId(), o, options);
        }
        for (size_t i = 0; i < t->getOrders().size(); i++){
            cout << t->getCustomer(t->getOrders()[i].first)->getName() << " Is Doing " << t->getOrders()[i].second.getName() << endl;
        }
        complete();
        }
    t = nullptr;
}

std::string Order::toString() const {
    string s = "order " + std::to_string(trainerId);
    if (getStatus() == COMPLETED)
        s += " Completed";
    else
        s += " Error: " + getErrorMsg();
    return s;
}

int Order::getTrainerId() {return trainerId;}

BaseAction& Order::clone() {
    Order* o = new Order(this->getTrainerId());
    return *o;
}


Order::~Order() {}

MoveCustomer::MoveCustomer(int src, int dst, int customerId): BaseAction(), srcTrainer(src),
dstTrainer(dst), id(customerId){}

void MoveCustomer::act(Studio &studio) {
    Trainer *sTrainer = studio.getTrainer(srcTrainer);
    Trainer *dTrainer = studio.getTrainer(dstTrainer);
    if ((sTrainer == nullptr) | (dTrainer == nullptr) ||
            (!sTrainer->isOpen()) | (!dTrainer->isOpen()) | (sTrainer->getCustomer(id) == nullptr) | (dTrainer->getCapacity() == 0))
        error("Cannot move customer.");
    else {
        if (dynamic_cast<SweatyCustomer *>(sTrainer->getCustomer(id))) {
            SweatyCustomer *c = new SweatyCustomer(sTrainer->getCustomer(id)->getName(),
                                                   sTrainer->getCustomer(id)->getId());
            dTrainer->addCustomer(c);
        } else if (dynamic_cast<CheapCustomer *>(sTrainer->getCustomer(id))) {
            CheapCustomer *c = new CheapCustomer(sTrainer->getCustomer(id)->getName(),
                                                 sTrainer->getCustomer(id)->getId());
            dTrainer->addCustomer(c);
        } else if (dynamic_cast<HeavyMuscleCustomer *>(sTrainer->getCustomer(id))) {
            HeavyMuscleCustomer *c = new HeavyMuscleCustomer(sTrainer->getCustomer(id)->getName(),
                                                             sTrainer->getCustomer(id)->getId());
            dTrainer->addCustomer(c);
        } else { // FullBodyCustomer
            FullBodyCustomer *c = new FullBodyCustomer(sTrainer->getCustomer(id)->getName(),
                                                       sTrainer->getCustomer(id)->getId());
            dTrainer->addCustomer(c);
        }
//        Customer *c = sTrainer->getCustomer(id);
        vector<OrderPair> toAdd = sTrainer->removeOrdersOfCustomerById(id);
        sTrainer->removeCustomer(id);
//        dTrainer->addCustomer(c);
        dTrainer->addOrdersAfterMove(toAdd);
        complete();
    }
    sTrainer = nullptr;
    dTrainer = nullptr;
}

std::string MoveCustomer::toString() const {
    string s = "move " + std::to_string(srcTrainer) + std::to_string(dstTrainer) + std::to_string(id);
    if (getStatus() == COMPLETED)
        s += " Completed";
    else
        s += " Error: " + getErrorMsg();
    return s;
}

int MoveCustomer::getId() {return id;}
int MoveCustomer::getSrcTrainer() {return srcTrainer;}
int MoveCustomer::getDstTrainer() {return dstTrainer;}

BaseAction& MoveCustomer::clone() {

    MoveCustomer* o = new MoveCustomer(this->getSrcTrainer(),this->getDstTrainer(),this->getId());
    return *o;
}

MoveCustomer::~MoveCustomer() {}

Close::Close(int id): BaseAction(), trainerId(id) {}

void Close::act(Studio &studio) {
    Trainer* t = studio.getTrainer(trainerId);
    if (t == nullptr || !(t->isOpen())) {
        error("Trainer does not exist or is not open");
    }
    else {
        t->closeTrainer();
        cout << "Trainer " << trainerId << " is closed. Salary " << t->getSalary() << "NIS" << endl;
        complete();
    }
    t= nullptr;
}

std::string Close::toString() const {
    string s = "close " + std::to_string(trainerId);
    if (getStatus() == COMPLETED)
        s += " Completed";
    else
        s += " Error: " + getErrorMsg();
    return s;
}

int Close::getTrainerId() {return trainerId;}

BaseAction& Close::clone() {

    Close* o = new Close(this->getTrainerId());
    return *o;
}

Close::~Close() {}

CloseAll::CloseAll(): BaseAction() {}

void CloseAll::act(Studio &studio) {
    int numOfTrainers = studio.getNumOfTrainers();
    for (int i = 0; i < numOfTrainers; i++){
        Trainer* t = studio.getTrainer(i);
        if (t->isOpen()) {
            Close closeT(i);
            closeT.act(studio);
        }
        t = nullptr;
    }
    complete();
}

string CloseAll::toString() const {
    return "closeall Completed";
}

BaseAction& CloseAll::clone() {

    CloseAll* o = new CloseAll();
    return *o;
}

CloseAll::~CloseAll() {}

PrintWorkoutOptions::PrintWorkoutOptions(): BaseAction() {}

void PrintWorkoutOptions::act(Studio &studio) {
    std::vector<Workout>& options = studio.getWorkoutOptions();
    for (size_t i = 0; i < options.size(); i++){
        std::cout << options[i].getName() << ", " << options[i].getType() << ", " << options[i].getPrice() << std::endl;
    }
    complete();
}

string PrintWorkoutOptions::toString() const {
    return "workout_options Completed";
}

BaseAction& PrintWorkoutOptions::clone() {

    PrintWorkoutOptions* o = new PrintWorkoutOptions();
    return *o;
}

PrintWorkoutOptions::~PrintWorkoutOptions() {}

PrintTrainerStatus::PrintTrainerStatus(int id): BaseAction(), trainerId(id) {}

void PrintTrainerStatus::act(Studio &studio) {
    Trainer* t = studio.getTrainer(trainerId);
    std::string status = t->isOpen() ? "open" : "closed";
    cout << "Trainer " << trainerId << " status: " << status << endl;
    if (t->isOpen()){
        cout << "Costumers:" << endl;
        vector<Customer*> &c = t->getCustomers();
        for (size_t i = 0; i < c.size(); i++)
            cout << c[i]->getId() << " " << c[i]->getName() << endl;
        cout << "Orders:" << endl;
        vector<OrderPair>& orders = t->getOrders();
        for (size_t i = 0; i < orders.size(); i++)
            cout << orders[i].second.getName() << " " << orders[i].second.getPrice() << "NIS " << orders[i].first << endl;
        cout << "Current Trainer's Salary: " << t->getSalary() <<"NIS" << endl;
    }
    t = nullptr;
    complete();
}

std::string PrintTrainerStatus::toString() const {
    return "status " + std::to_string(trainerId) + " Completed";
}

int PrintTrainerStatus::getTrainerId() {return trainerId;}

BaseAction& PrintTrainerStatus::clone() {

    PrintTrainerStatus* o = new PrintTrainerStatus(this->getTrainerId());
    return *o;
}

PrintTrainerStatus::~PrintTrainerStatus() {}

PrintActionsLog::PrintActionsLog(): BaseAction() {}

void PrintActionsLog::act(Studio &studio) {
    const std::vector<BaseAction*>& log = studio.getActionsLog();
    for (size_t i = 0; i < log.size(); i++){
        //string status = log[i]->getStatus() == COMPLETED ? "Completed" : "Error: " + getErrorMsg();
        cout << log[i]->toString() << endl;
    }
    complete();
}

string PrintActionsLog::toString() const {return "log Completed";}

BaseAction& PrintActionsLog::clone() {

    PrintActionsLog* o = new PrintActionsLog();
    return *o;
}

PrintActionsLog::~PrintActionsLog() {}

BackupStudio::BackupStudio(): BaseAction() {}

void BackupStudio::act(Studio &studio) {
    if (backup == nullptr) {
        Studio* temp = new Studio();
        backup = temp;
        temp = nullptr;
    }
    *backup = studio;
    complete();
}

string BackupStudio::toString() const {return "backup Completed";}

BaseAction& BackupStudio::clone() {

    BackupStudio* o = new BackupStudio();
    return *o;
}

BackupStudio::~BackupStudio() {}

RestoreStudio::RestoreStudio(): BaseAction() {}

void RestoreStudio::act(Studio &studio) {
    if (backup == nullptr)
        error("No backup available");
    else {
        studio = *backup;
        complete();
    }
}

std::string RestoreStudio::toString() const {
    string s = "restore";
    if (getStatus() == COMPLETED)
        s += " Completed";
    else
        s += " Error: " + getErrorMsg();
    return s;
}

BaseAction& RestoreStudio::clone() {

    RestoreStudio* o = new RestoreStudio();
    return *o;
}

RestoreStudio::~RestoreStudio() {}





