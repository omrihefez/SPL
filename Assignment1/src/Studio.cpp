//
// Created by Omri on 09/11/2021.
//

using namespace std;

#include <iostream>
#include <string>
#include <fstream>
#include "../include/Studio.h"


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
                case 0:
                    string _numOfTrainers = "";
                    for (int i = 0; i < line.length(); i++)
                        _numOfTrainers += line[i];
                    numOfTrainers = stoi(_numOfTrainers);
                    lineNumber++;
                    break;
                case 1:
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
                case 2:
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


void Studio::start() {
    open = true;
    cout << "Studio is now open!" << endl;
    string s;
    cin << s;
    switch (s) {
        case s.substr(0,s.find_first_of(" ")-1) == "open":
            int firstSpace= find_first_of(" ");
            vector<Customer *> &customers;
            int trainerId= stoi(s.substr[firstSpace+1,(s.substr(firstSpace+1,s.length-1)).find_first_of(" ")-1]);
            int start = firstspace + 3;
            while (start < s.length()) {
                string name = "";
                string customerIdString = "";
                for (int i = start; i < (s.substr(start,s.length-1)).find_first_of(","); i++) {
                    name += s[i];
                    start = i;
                }
                for (int i = start+1 ; i < (s.substr(start,s.length-1)).find_first_of(" "); i++){
                    customerIdString += s[i];
                    start = i
                }
                Customer toAdd =  Customer(name,stoi(customerIdString));
                customers.push_back(toAdd);
                start ++;
                start ++;
           }
            BaseAction a = OpenTrainer(trainerId,customers);
            a.act(this);
        case s.substr(0,s.find_first_of(" ")-1) == "order":
            string trainerId = "";
            for (int i = s.find_first_of(" ")+1 ; i < s.length() ; i++ )
                trainerId += s[i];
            BaseAction a = order(stoi(trainerId));
            a.act(this);
        case s.substr(0,s.find_first_of(" ")-1) == "move":
            string src = "";
            string dst = "";
            string customerId = "";
            start = s.find_first_of(" ")+1
            for (int i = start; i < s.length() && s[i] != " "; i++) {
                src += s[i];
                start++;
            }
            for (int i = start++ ; i < s.length() && s[i] != " " ; i++){
                dst += s[i];
                start++;
            }
            for (int i= start++ ; i < s.length() ; i++){
                customerId += s[i];
            }
            BaseAction a = MoveCustomer(stoi(src), stoi(dst), stoi(customerId));
            a.act(this);
        case s.substr(0,s.find_first_of(" ")-1) == "close":
            int trainerId = stoi(s.substring(6,s.length()-1));
            BaseAction a = close(trainerId);
            a.act(this);
        case s.substr(0,s.find_first_of(" ")-1) == "status":
            int trainerId = stoi(s.substring(7,s.length()-1));
            BaseAction a = PrintTrainerStatus(trainerId);
            a.act(this);
        case s == "workout_options":
            BaseAction a = PrintWorkoutOptions();
            a.act(this);
        case s == "log":
            BaseAction a = PrintActionsLog();
            a.act(this);
        case s == "backup":
            BaseAction a = BackupStudio();
            a.act(this);
        case s == "restore":
            BaseAction a = RestoreStudio();
            a.act(this);
        case s == "closeall":
            BaseAction a = CloseAll();
            a.act(this);
            open = false;
            break;

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

