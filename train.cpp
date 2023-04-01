#include <iostream>
#include <chrono>
#include <thread>
#include "train.h"
#include "rails.h"

void Train::createOutsideTrain(railStruct* rails_array, int start_position, int speed = 250) { //optymalna predkosc to 250km/h -> 4s
    if (speed <= 0){
        printError("Too low speed");
        return;
    }
    if (start_position < 0){
        printError("Wrong start position");
        return;
    }
    //tworzonko zmiennych pociagu
    int current_rail_id = start_position;
    int prev_rail_id = -1;
    while(1){
        if (!rails_array[current_rail_id].mtx.try_lock()){
            printError("Nastąpiła kolizja!!!");
            return;
        }

        while (!isGreenLight(rails_array, current_rail_id)){
            sleepTrain(speed);
        }

        if (rails_array[current_rail_id].is_crossover){
            //tutaj dopisz zachowanie jak tor jest rozjazdem
        }else{
            prev_rail_id = current_rail_id;
            current_rail_id = rails_array[current_rail_id].next_right_id;
            rails_array[prev_rail_id].mtx.unlock();
        }
    }

}

void Train::sleepTrain(int speed) const { std::this_thread::sleep_for(std::chrono::seconds(10000 / speed)); }

void Train::printError(std::string error_name){
    std::cerr << error_name << std::endl;
}

bool Train::isCrossover(railStruct* arr, int position){
    if (arr->is_crossover){
        return true;
    }else{
        return false;
    }
}

bool Train::isGreenLight(railStruct* arr, int position){
    if (arr->is_green_light){
        return true;
    }else{
        return false;
    }
}