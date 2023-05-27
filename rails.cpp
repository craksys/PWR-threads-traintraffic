#include "rails.hpp"

bool Rail::go_forward()
{
    Rail* next_t = turn ? turn_track : next_track;
    //Tutaj to sobie musisz poprawić w zeleżniści jak ma to jeździć
    if(next_t->is_green_light){
        next_t->is_green_light = false;
        is_green_light = true;
    }

    return false;
}

void Rail::start_travel()
{
    is_green_light = false;
}

void Rail::stop_travel()
{
    is_green_light = true;
}

void Rail::change_crossovers()
{
    if(is_crossover) turn = !turn;
    return;
}
