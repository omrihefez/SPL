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


Studio::Studio(): open(false) {}

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
    for (index; _line[index] != ','; index++)
        workoutType += _line[index];
    if (workoutType[0] == 'A')
        type = ANAEROBIC;
    else if (workoutType[0] == 'C')
        type = CARDIO;
    else
        type = MIXED;
    index += 2;
    for (index; index < _line.length(); index++)
        priceString += _line[index];
    price = stoi(priceString);
    return Workout(id, workoutName, price, type);
}

Studio::Studio(const std::string &configFilePath) {
    open = false;
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
                    for (int i = 0; i <= line.length(); i++) {
                        if (i < line.length() && line[i] != ','  & line[i] != ' ') {
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
            case (0): {
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
                for (start; (size_t)start < s.length(); start++) {
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
                            break;
                        }
                        case (1): {
                            CheapCustomer* temp = new CheapCustomer(customerName, customerId);
                            customerId++;
                            customersToAdd.push_back(temp);
                            temp = nullptr;
                            customerName = "";
                            break;
                        }
                        case (2): {
                            HeavyMuscleCustomer* temp = new HeavyMuscleCustomer(customerName, customerId);
                            customerId++;
                            customersToAdd.push_back(temp);
                            temp = nullptr;
                            customerName = "";
                            break;
                        }
                        case (3): {
                            FullBodyCustomer* temp = new FullBodyCustomer(customerName, customerId);
                            customerId++;
                            customersToAdd.push_back(temp);
                            temp = nullptr;
                            customerName = "";
                            break;
                        }
                    }
                    start = index + 3;
                }
                OpenTrainer o = OpenTrainer(trainerId, customersToAdd);
                o.act(*this);
                BaseAction* ba = &o;
                actionsLog.push_back(ba);
                s = "";
                caseNumber = -1;
                break;
            }
            case (1): {
                string trainerId = "";
                for (size_t i = s.find_first_of(" ") + 1; i < s.length(); i++)
                    trainerId += s[i];
                Order a = Order(stoi(trainerId));
                a.act(*this);
                BaseAction* ba = &a;
                actionsLog.push_back(ba);
                s = "";
                caseNumber = -1;
                break;
            }
            case (2): {
                string src = "";
                string dst = "";
                string customerId = "";
                int start = s.find_first_of(" ") + 1;
                for (size_t i = start; i < s.length() && strcmp(&s[i], " ") != 0; i++) {
                    src += s[i];
                    start++;
                }
                for (size_t i = start++; i < s.length() && strcmp(&s[i], " ") != 0 ; i++) {
                    dst += s[i];
                    start++;
                }
                for (size_t i = start++; i < s.length(); i++) {
                    customerId += s[i];
                }
                MoveCustomer a = MoveCustomer(stoi(src), stoi(dst), stoi(customerId));
                a.act(*this);
                BaseAction* ba = &a;
                actionsLog.push_back(ba);
                s = "";
                caseNumber = -1;
                break;
            }
            case (3): {
                int trainerId = stoi(s.substr(6, s.length() - 1));
                Close a = Close(trainerId);
                a.act(*this);
                BaseAction* ba = &a;
                actionsLog.push_back(ba);
                s = "";
                caseNumber = -1;
                break;
            }
            case (4): {
                int trainerId = stoi(s.substr(7, s.length() - 1));
                PrintTrainerStatus a = PrintTrainerStatus(trainerId);
                a.act(*this);
                BaseAction* ba = &a;
                actionsLog.push_back(ba);
                s = "";
                caseNumber = -1;
                break;
            }
            case (5): {
                PrintWorkoutOptions a = PrintWorkoutOptions();
                a.act(*this);
                BaseAction* ba = &a;
                actionsLog.push_back(ba);
                s = "";
                caseNumber = -1;
                break;
            }
            case (6): {
                PrintActionsLog a = PrintActionsLog();
                a.act(*this);
                BaseAction* ba = &a;
                actionsLog.push_back(ba);
                s = "";
                caseNumber = -1;
                break;
            }
            case (7): {
                BackupStudio a = BackupStudio();
                a.act(*this);
                BaseAction* ba = &a;
                actionsLog.push_back(ba);
                s = "";
                caseNumber = -1;
                break;
            }
            case (8): {
                RestoreStudio a = RestoreStudio();
                a.act(*this);
                BaseAction* ba = &a;
                actionsLog.push_back(ba);
                s = "";
                caseNumber = -1;
                break;
            }
            case (9): {
                CloseAll a = CloseAll();
                a.act(*this);
                BaseAction* ba = &a;
                actionsLog.push_back(ba);
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
        for (size_t i = 0; i < trainers.size(); i++)
            delete trainers[i];
    }
    trainers.clear();
    workout_options.clear();
    if (!actionsLog.empty()){
        for (size_t i = 0; i < actionsLog.size(); i++)
            delete actionsLog[i];
    }
    actionsLog.clear();
}

//copy constructor
Studio::Studio (const Studio &other): Studio() {
    vector<Trainer*> trainersOfOther = other.trainers;
    for (size_t i = 0; i < trainersOfOther.size(); i++){
        Trainer t = *trainersOfOther[i];
        trainers.push_back(&t);
    }
    vector<Workout> other_workout_options = other.workout_options;
    for (size_t i = 0; i < other_workout_options.size(); i++)
        workout_options.push_back(other_workout_options[i]);
    vector<BaseAction*> otherActionlog = other.actionsLog;
    for (size_t i = 0; i < actionsLog.size(); i++){
        BaseAction *action = (otherActionlog[i]);
        actionsLog.push_back(action);
    }
}

//copy assignment operator
Studio &Studio::operator=(const Studio &other) {
    if (this == &other)
        return *this;
    open = other.open;
    trainers.clear();
    vector<Trainer*> trainersOfOther = other.trainers;
    for (int i = 0; i < trainersOfOther.size(); i++){
        Trainer t = *trainersOfOther[i];
        trainers.push_back(&t);
    }
    workout_options.clear();
    for (size_t i = 0; i < other.workout_options.size(); i++){
        workout_options.push_back(other.workout_options[i]);
    }
    actionsLog.clear();
    vector<BaseAction*> otherActionlog = other.actionsLog;
    for (size_t i = 0; i < actionsLog.size(); i++){
        BaseAction *action = (otherActionlog[i]);
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



