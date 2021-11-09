//
// Created by Omri on 09/11/2021.
//

using namespace std;
#include "../include/Studio.h"


Studio::Studio() {

}

Studio::Studio(const std::string &configFilePath) {


}

void Studio::start() {
    open = true;
    cout << "Studio is now open!" << endl;

    }

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
