cmake_minimum_required(VERSION 3.16)
project(SPL1)

set(CMAKE_CXX_STANDARD 14)
set(HEADERS include/Action.h include/Trainer.h include/Customer.h include/Studio.h include/Workout.h)

add_executable(SPL src/main.cpp src/Customer.cpp src/Studio.cpp src/Trainer.cpp src/Workout.cpp src/Action.cpp)
