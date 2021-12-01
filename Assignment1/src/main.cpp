#include "../include/Studio.h"
#include <iostream>

using namespace std;

Studio* backup = nullptr;


int main(int argc, char** argv){
    if(argc!=2){
        std::cout << "usage: studio <config_path>" << std::endl;
        return 0;
    }
    string configurationFile = argv[1];
    Studio studio(configurationFile);
    studio.start();
    Studio sa(std::move(configurationFile));
    sa.start();
    Studio studio1 = Studio(configurationFile);
    studio1.start();
    if(backup!=nullptr){
    	delete backup;
    	backup = nullptr;
    }
    return 0;

    cout << "Hi";
}