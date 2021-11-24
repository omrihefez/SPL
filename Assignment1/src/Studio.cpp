//
// Created by Omri on 09/11/2021.
//

using namespace std;

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "../include/Studio.h"

int customerId = 0;


Studio::Studio() {
int customersIdCounter = -1;
}

void buildWorkout(int id, string _line) {
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
    Workout(id, workoutName, price, type);
}

Studio::Studio(const std::string &configFilePath) {
    open = false;
    string line;
    fstream fstream1(configFilePath);
    int lineNumber = 0;
    while (getline(fstream1, line)) {
        if (line[0] == '#'){
            (getline(fstream1, line));
            switch (lineNumber) {
                case 0: {
                    string _numOfTrainers = "";
                    for (int i = 0; i < line.length(); i++)
                        _numOfTrainers += line[i];
                    numOfTrainers = stoi(_numOfTrainers);
                    lineNumber++;
                    break;
                }
                case 1: {
                    string capacity = "";
                    for (int i = 0; i < line.length(); i++) {
                        if (line[i] != ',' & line[i] != ' ')
                            capacity += line[i];
                        else if (line[i] == ',') {
                            Trainer(stoi(capacity));
                            capacity = "";
                        }
                    }
                    lineNumber++;
                    break;
                }
                case 2: {
                    int id = 0;
                    buildWorkout(id, line);
                    id++;
                    while (getline(fstream1, line)) {
                        buildWorkout(id, line);
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
    std::cin >> s;
    int caseNumber;
    if (s.substr(0,s.find_first_of(" ")-1) == "open")
        caseNumber = 0;
    else if (s.substr(0,s.find_first_of(" ")-1) == "order")
        caseNumber = 1;
    else if (s.substr(0,s.find_first_of(" ")-1) == "move")
        caseNumber = 2;
    else if (s.substr(0,s.find_first_of(" ")-1) == "close")
        caseNumber = 3;
    else if (s.substr(0,s.find_first_of(" ")-1) == "status")
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
            Trainer* t = getTrainer(trainerId);
            start = secondSpace + 1;
            string customerName = "";
            enum customerType {swt, chp, mcl, fbd};
            customerType ct;
            for (start; start < s.length(); start++){
                int index = start;
                while (&s[index] != ",") {
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
                        SweatyCustomer temp = SweatyCustomer(customerName, customerId);
                        customerId++;
                        t->addCustomer(&temp);
                    }
                    case (1): {
                        CheapCustomer temp = CheapCustomer(customerName, customerId);
                        customerId++;
                        t->addCustomer(&temp);
                    }
                    case (2): {
                        HeavyMuscleCustomer temp = HeavyMuscleCustomer(customerName, customerId);
                        customerId++;
                        t->addCustomer(&temp);
                    }
                    case (3): {
                        FullBodyCustomer temp = FullBodyCustomer(customerName, customerId);
                        customerId++;
                        t->addCustomer(&temp);
                    }
                }
                start = index++;
                }
            }
        case (1): {
            string trainerId = "";
            for (int i = s.find_first_of(" ") + 1; i < s.length(); i++)
                trainerId += s[i];
            Order a = Order(stoi(trainerId));
            a.act(*this);
        }
        case (2): {
            string src = "";
            string dst = "";
            string customerId = "";
            int start = s.find_first_of(" ") + 1;
            for (int i = start; i < s.length() && &s[i] != " "; i++) {
                src += s[i];
                start++;
            }
            for (int i = start++; i < s.length() && &s[i] != " "; i++) {
                dst += s[i];
                start++;
            }
            for (int i = start++; i < s.length(); i++) {
                customerId += s[i];
            }
            MoveCustomer a = MoveCustomer(stoi(src), stoi(dst), stoi(customerId));
            a.act(*this);
        }
        case (3): {
            int trainerId = stoi(s.substr(6, s.length() - 1));
            Close a = Close(trainerId);
            a.act(*this);
        }
        case (4): {
            int trainerId = stoi(s.substr(7, s.length() - 1));
            PrintTrainerStatus a = PrintTrainerStatus(trainerId);
            a.act(*this);
        }
        case (5): {
            PrintWorkoutOptions a = PrintWorkoutOptions();
            a.act(*this);
        }
        case (6): {
            PrintActionsLog a = PrintActionsLog();
            a.act(*this);
        }
        case (7): {
            BackupStudio a = BackupStudio();
            a.act(*this);
        }
        case (8): {
            RestoreStudio a = RestoreStudio();
            a.act(*this);
        }
        case (9): {
            CloseAll a = CloseAll();
            a.act(*this);
            open = false;
            break;
        }

    }
}


int Studio::getNumOfTrainers() const {
    return trainers.size();
}

Trainer *Studio::getTrainer(int tid) {
    if (tid > trainers.size())
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

bool isOpen(){
    return open;
}

//rule of 5
virtual ~Studio(){
    clear();
}

void clear(){
    if (this.trainers){
        for (int i = 0; i < this.trainers.lenth(); i++)
            delete this.trainers[i];
    }

    if (this.actionsLog){
        for (int i = 0; i < this.actionsLog.lenth(); i++)
            delete this.actionsLog[i];
    }
}

Studio (const Studio &other){
    numOfTrainers = other.getNumOfTrainers();
    open = other.isOpen();
    trainers = vector<Trainer*>(numOfTrainers);
    for (int i = 0; i < numOfTrainers; i++){
        trainers.push_back(other.getTrainer(i));
    }
    workout_options = other.getWorkoutOptions();
    actionsLog = other.getActionsLog();
}

Studio& operator=(const Studio &other){

}