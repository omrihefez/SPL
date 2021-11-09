//
// Created by Omri on 09/11/2021.
//

using namespace std;

#include <iostream>
#include <string>
#include <fstream>
#include "../include/Studio.h"


Studio::Studio() {

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

    }


int Studio::getNumOfTrainers() const {
    return 0;
}

Trainer *Studio::getTrainer(int tid) {
    return nullptr;
}

const std::vector<BaseAction *> &Studio::getActionsLog() const {
    return <#initializer#>;
}

std::vector<Workout> &Studio::getWorkoutOptions() {
    return <#initializer#>;
}

