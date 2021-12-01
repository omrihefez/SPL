//
// Created by Omri on 09/11/2021.
//

using namespace std;

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <sstream>
#include "../include/Studio.h"

int customerId = 0;


Studio::Studio(): open(false), trainers(), workout_options(), actionsLog() {}

Workout buildWorkout(int id, string _line) {
    string workoutName;
    string workoutType;
    WorkoutType type;
    string priceString;
    int price;
    int index;
    for (index = 0; _line[index] != ','; index++)
        workoutName += _line[index];
    index += 2;
    while (_line[index] != ',') {
        workoutType += _line[index];
        index++;
    }
    if (workoutType[0] == 'A')
        type = ANAEROBIC;
    else if (workoutType[0] == 'C')
        type = CARDIO;
    else
        type = MIXED;
    index += 2;
    while ((size_t)index < _line.length()){
        priceString += _line[index];
        index++;
    }
    price = stoi(priceString);
    return Workout(id, workoutName, price, type);
}

Studio::Studio(const std::string &configFilePath): open(false), trainers(), workout_options(), actionsLog() {
    string line = "";
    ifstream f(configFilePath);
    int lineNumber = 0;
    while (getline(f, line)) {
        if (line[0] == '#'){
            (getline(f, line));
            switch (lineNumber) {
                case 0: {
//                    string _numOfTrainers = "";
//                    for (int i = 0; i < line.length(); i++)
//                        _numOfTrainers += line[i];
                    lineNumber++;
                    break;
                }
                case 1: {
                    string capacity = "";
                    for (size_t i = 0; i <= line.length(); i++) {
                        if ((i < line.length()) && (line[i] != ',')  & (line[i] != ' ')) {
                            capacity += line[i];
                        }
                        else {
                            int n = 0;
                            stringstream j(capacity);
                            j >> n;
                            int tId = n;
                            Trainer *t = new Trainer(tId);
                            trainers.push_back(t);
                            t = nullptr;
                            capacity = "";
                        }
                    }
                    lineNumber++;
                    break;
                }
                case 2: {
                    int id = 0;
                    workout_options.push_back(buildWorkout(id, line));
                    id++;
                    while (getline(f, line) && line != "") {
                        workout_options.push_back(buildWorkout(id, line));
                        id++;
                    }
                    break;
                }
            }
        }
    }

}


void Studio::start() {
    open = true;
    cout << "Studio is now open!" << endl;
    string s;
    while (open) {
        getline(cin, s);
        int caseNumber;
        if (s.substr(0, s.find_first_of(" ")) == "open")
            caseNumber = 0;
        else if (s.substr(0, s.find_first_of(" ")) == "order")
            caseNumber = 1;
        else if (s.substr(0, s.find_first_of(" ")) == "move")
            caseNumber = 2;
        else if (s.substr(0, s.find_first_of(" ")) == "close")
            caseNumber = 3;
        else if (s.substr(0, s.find_first_of(" ")) == "status")
            caseNumber = 4;
        else if (s == "workout_options")
            caseNumber = 5;
        else if (s == "log")
            caseNumber = 6;
        else if (s == "backup")
            caseNumber = 7;
        else if (s == "restore")
            caseNumber = 8;
        else if (s == "closeall")
            caseNumber = 9;


        switch (caseNumber) {
            case (0): { //open trainer
                int start = 0;
                int firstSpace = s.find_first_of(" ");
                int secondSpace = s.find_first_of(" ", firstSpace + 1);
                int trainerId = stoi(s.substr(firstSpace, secondSpace));
                std::vector<Customer *> customersToAdd;
                start = secondSpace + 1;
                string customerName = "";
                enum customerType {
                    swt, chp, mcl, fbd
                };
                customerType ct;
                int numOfCustomersAdded = 0;
                while (((size_t)start < s.length()) & (getTrainer(trainerId)->getCapacity() != numOfCustomersAdded)) {
                    int index = start;
                    while (s[index] != ',') {
                        customerName += s[index];
                        index++;
                    }
                    index++;
                    string customerTypeString = s.substr(index, 3);
                    if (customerTypeString == "swt")
                        ct = swt;
                    else if (customerTypeString == "chp")
                        ct = chp;
                    else if (customerTypeString == "mcl")
                        ct = mcl;
                    else if (customerTypeString == "fbd")
                        ct = fbd;
                    switch (ct) {
                        case (0): {
                            SweatyCustomer* temp = new SweatyCustomer(customerName, customerId);
                            customerId++;
                            customersToAdd.push_back(temp);
                            temp = nullptr;
                            customerName = "";
                            numOfCustomersAdded++;
                            break;
                        }
                        case (1): {
                            CheapCustomer* temp = new CheapCustomer(customerName, customerId);
                            customerId++;
                            customersToAdd.push_back(temp);
                            temp = nullptr;
                            customerName = "";
                            numOfCustomersAdded++;
                            break;
                        }
                        case (2): {
                            HeavyMuscleCustomer* temp = new HeavyMuscleCustomer(customerName, customerId);
                            customerId++;
                            customersToAdd.push_back(temp);
                            temp = nullptr;
                            customerName = "";
                            numOfCustomersAdded++;
                            break;
                        }
                        case (3): {
                            FullBodyCustomer* temp = new FullBodyCustomer(customerName, customerId);
                            customerId++;
                            customersToAdd.push_back(temp);
                            temp = nullptr;
                            customerName = "";
                            numOfCustomersAdded++;
                            break;
                        }
                    }
                    start = index + 4;
                }
                OpenTrainer* a = new OpenTrainer(trainerId, customersToAdd);
                customersToAdd.clear();
                a->act(*this);
                if (a->getStatus() == ERROR)
                    cout << "Error: Workout session does not exist or is already open." << endl;
                BaseAction* clone = &(a->clone());
                actionsLog.push_back(clone);
                delete a;
                s = "";
                caseNumber = -1;
                break;
            }
            case (1): { //order
                string trainerId = "";
                for (size_t i = s.find_first_of(" ") + 1; i < s.length(); i++)
                    trainerId += s[i];
                Order* a = new Order(stoi(trainerId));
                a->act(*this);
                if (a->getStatus() == ERROR)
                    cout << "Error: Workout session does not exist or is already open." << endl;
                BaseAction* clone = &(a->clone());
                actionsLog.push_back(clone);
                delete a;
                s = "";
                caseNumber = -1;
                break;
            }
            case (2): { //move customer
                string src = "";
                string dst = "";
                string customerId = "";
                int start = s.find_first_of(" ") + 1;
                for (size_t i = start; i < s.length() && s[i] != ' '; i++) {
                    src += s[i];
                    start++;
                }
                start++;
                for (size_t i = start; i < s.length() && s[i] != ' ' ; i++) {
                    dst += s[i];
                    start++;
                }
                start++;
                for (size_t i = start; i < s.length(); i++) {
                    customerId += s[i];
                }
                MoveCustomer* a = new MoveCustomer(stoi(src), stoi(dst), stoi(customerId));
                a->act(*this);
                if (a->getStatus() == ERROR)
                    cout << "Cannot move customer." << endl;
                BaseAction* clone = &(a->clone());
                actionsLog.push_back(clone);
                delete a;
                s = "";
                caseNumber = -1;
                break;
            }
            case (3): { // close trainer
                int trainerId = stoi(s.substr(6, s.length() - 1));
                Close* a = new Close(trainerId);
                a->act(*this);
                if (a->getStatus() == ERROR)
                    cout << "Error: Trainer does not exist or is not open" << endl;
                BaseAction* clone = &(a->clone());
                actionsLog.push_back(clone);
                delete a;
                s = "";
                caseNumber = -1;
                break;
            }
            case (4): { // print trainer status
                int trainerId = stoi(s.substr(7, s.length() - 1));
                PrintTrainerStatus* a = new PrintTrainerStatus(trainerId);
                a->act(*this);
                BaseAction* clone = &(a->clone());
                actionsLog.push_back(clone);
                delete a;
                s = "";
                caseNumber = -1;
                break;
            }
            case (5): { // print workout options
                PrintWorkoutOptions* a = new PrintWorkoutOptions();
                a->act(*this);
                BaseAction* clone = &(a->clone());
                actionsLog.push_back(clone);
                delete a;
                s = "";
                caseNumber = -1;
                break;
            }
            case (6): { // print action log
                PrintActionsLog* a = new PrintActionsLog();
                a->act(*this);
                BaseAction* clone = &(a->clone());
                delete a;
                actionsLog.push_back(clone);
                s = "";
                caseNumber = -1;
                break;
            }
            case (7): { // backup studio
                BackupStudio* a = new BackupStudio();
                a->act(*this);
                BaseAction* clone = &(a->clone());
                actionsLog.push_back(clone);
                delete a;
                s = "";
                caseNumber = -1;
                break;
            }
            case (8): { // restore studio
                RestoreStudio* a = new RestoreStudio();
                a->act(*this);
                if (a->getStatus() == ERROR)
                    cout << "Error: No backup available" << endl;
                BaseAction* clone = &(a->clone());
                actionsLog.push_back(clone);
                delete a;
                s = "";
                caseNumber = -1;
                break;
            }
            case (9): { // close all
                CloseAll* a = new CloseAll();
                a->act(*this);
                BaseAction* clone = &(a->clone());
                actionsLog.push_back(clone);
                delete a;
                open = false;
                s = "";
                caseNumber = -1;
                break;
            }

        }
    }
}


int Studio::getNumOfTrainers() const {
    return trainers.size();
}

Trainer *Studio::getTrainer(int tid) {
    if (tid < 0 || (size_t)tid > trainers.size())
        return nullptr;
    else
        return trainers[tid];
}

const std::vector<BaseAction *> &Studio::getActionsLog() const {
    return actionsLog;
}

std::vector<Workout> &Studio::getWorkoutOptions() {
    return workout_options;
}

bool Studio::isOpen(){
    return open;
}

//rule of 5
//destructor
Studio::~Studio(){
    open = false;
    if (!trainers.empty()){
        for (size_t i = 0; i < trainers.size(); i++) {
//            for (size_t j = 0; j < trainers[i]->getCustomers().size(); j++)
//                delete trainers[i]->getCustomers()[j];
            delete trainers[i];
        }
    }
    trainers.clear();
    workout_options.clear();
    if (!actionsLog.empty()){
        for (size_t i = 0; i < actionsLog.size(); i++) {
            if (dynamic_cast<OpenTrainer*>(actionsLog[i])) {
                for (size_t j = 0; j < dynamic_cast<OpenTrainer *>(actionsLog[i])->getCustomers().size(); j++) {
                    delete dynamic_cast<OpenTrainer *>(actionsLog[i])->getCustomers()[j];
                    dynamic_cast<OpenTrainer *>(actionsLog[i])->getCustomers()[j] = nullptr;
                }
            }
            else if (dynamic_cast<MoveCustomer*>(actionsLog[i]))
            delete actionsLog[i];
        }
    }
    actionsLog.clear();
}

//copy constructor
Studio::Studio (const Studio &other): Studio() {
    open = other.open;
    for (size_t i = 0; i < other.trainers.size(); i++){
        Trainer* t(other.trainers[i]);
        trainers.push_back(t);
    }
    for (size_t i = 0; i < other.workout_options.size(); i++) {
        Workout w = Workout(other.workout_options[i].getId(), other.workout_options[i].getName(),
                            other.workout_options[i].getPrice(), other.workout_options[i].getType());
        workout_options.push_back(w);
    }
    for (size_t i = 0; i < other.actionsLog.size(); i++){
        BaseAction* action = &other.actionsLog[i]->clone();
        actionsLog.push_back(action);
    }
}

//copy assignment operator
Studio &Studio::operator=(const Studio &other) {
    if (this == &other)
        return *this;
    open = other.open;
    for (size_t i = 0; i < trainers.size(); i++) {
        for (size_t j = 0; j < trainers[i]->getCustomers().size(); j++)
            delete trainers[i]->getCustomers()[j];
        trainers[i]->getCustomers().clear();
        delete trainers[i];
    }
    trainers.clear();
    for (size_t i = 0; i < other.trainers.size(); i++){
        Trainer* t = new Trainer(*other.trainers[i]);
        trainers.push_back(t);
    }
    workout_options.clear();
    for (size_t i = 0; i < other.workout_options.size(); i++) {
        Workout w = Workout(other.workout_options[i].getId(), other.workout_options[i].getName(),
                            other.workout_options[i].getPrice(), other.workout_options[i].getType());
        workout_options.push_back(w);
    }
    for (size_t i = 0; i < actionsLog.size(); i++){
        if (dynamic_cast<OpenTrainer*>(actionsLog[i])) {
            for (size_t j = 0; j < dynamic_cast<OpenTrainer *>(actionsLog[i])->getCustomers().size(); j++) {
                delete dynamic_cast<OpenTrainer *>(actionsLog[i])->getCustomers()[j];
                dynamic_cast<OpenTrainer *>(actionsLog[i])->getCustomers()[j] = nullptr;
            }
        }
        delete actionsLog[i];
    }
    actionsLog.clear();
    for (size_t i = 0; i < other.actionsLog.size(); i++){
        BaseAction* action = &other.actionsLog[i]->clone();
        actionsLog.push_back(action);
    }
    return *this;
}

//move constructor
Studio::Studio(Studio &&other): open(other.open), trainers(std::move(other.trainers)),
                                workout_options(std::move(other.workout_options)), actionsLog(std::move(other.actionsLog)) {
    other.open = false;
    other.workout_options.clear();
    for (size_t i = 0; i < other.trainers.size(); i++)
        other.trainers[i] = nullptr;
    other.trainers.clear();
    for (size_t i = 0; i < other.actionsLog.size(); i++)
        other.actionsLog[i] = nullptr;
    other.actionsLog.clear();

}

//move assignment operator
Studio &Studio::operator=(Studio &&other){
    if (this == &other)
        return *this;
    open = other.open;
    trainers = std::move(other.trainers);
    workout_options = std::move(other.workout_options);
    actionsLog = std::move(other.actionsLog);
    other.open = false;
    other.workout_options.clear();
    for (size_t i = 0; i < other.trainers.size(); i++)
        other.trainers[i] = nullptr;
    other.trainers.clear();
    for (size_t i = 0; i < other.actionsLog.size(); i++)
        other.actionsLog[i] = nullptr;
    other.actionsLog.clear();
    return *this;
}



