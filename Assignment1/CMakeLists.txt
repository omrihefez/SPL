cmake_minimum_required(VERSION 3.20)
project(Assignment1)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(Assignment1
        include/Action.h
        include/Customer.h
        include/Studio.h
        include/Trainer.h
        include/Workout.h
        src/main.cpp)
