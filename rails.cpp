#include "rails.h"

railStruct* Rails::createRailStructArray(int size) {
    railStruct* arr = new railStruct[size];
    for (int i = 0; i < size; i++) {
        arr[i].is_green_light = true;
        arr[i].is_direction_left = false;
        arr[i].is_crossover = false;
        arr[i].prev_id = -1;
        arr[i].next_right_id = -1;
        arr[i].next_left_id = -1;
    }
    return arr;
}

railStruct* Rails::createStraightSection(railStruct* arr, int start_id, int end_id){
    int xdd = sizeof(arr) / sizeof(arr[0]);
    for (int i = start_id; i <= end_id; i++){
        if (i != end_id) {
            arr[i].next_right_id = i + 1;
        }
        if (i != start_id){
            arr[i].prev_id = i - 1;
        }
    }
    return arr;
}