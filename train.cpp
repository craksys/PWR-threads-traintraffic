#include "train.hpp"
#include <iostream>

void Train::get_on_map(int x, int y)
{
    map.lock_mutex(x, y);
    draw_on_map = true;
    distance_map = 0;
}

void Train::ride_on_map(int x, int y)
{
    x = map.getRoutes()[from][to][distance_map+1].x;
    y = map.getRoutes()[from][to][distance_map+1].y;
    map.lock_mutex(x, y);
    distance_map++;

    x = map.getRoutes()[from][to][distance_map-1].x;
    y = map.getRoutes()[from][to][distance_map-1].y;
    map.unlock_mutex(x, y);
}

void Train::get_off_map(int x, int y)
{
    map.unlock_mutex(x, y);
    distance_map = -1;
    draw_on_map = false;
    is_on_map = false;
}

void Train::set_is_on_map(bool is)
{
    is_on_map = is;
}


int Train::form_city()
{
    return from;
}

int Train::to_city()
{
    return to;
}

int Train::distance()
{
    return distance_map;
}

void Train::run(){
    int x = 0;
    int y = 0;
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(speed*50));
        if(is_on_map){
            
            
            // std::cout<<distance_map<<std::endl;
            if(distance_map==-1){
                x = map.getRoutes()[from][to][0].x;
                y = map.getRoutes()[from][to][0].y;
                get_on_map(x, y);
            }else if(map.getRoutes()[from][to].size()<distance_map+2){
                x = map.getRoutes()[from][to][distance_map].x;
                y = map.getRoutes()[from][to][distance_map].y;
                if(controler.enter_city(to)){
                    get_off_map(x, y);
                }
            }else{
                x = map.getRoutes()[from][to][distance_map].x;
                y = map.getRoutes()[from][to][distance_map].y;
                ride_on_map(x, y);
            }

        }else{
            switch (to)
            {
            case 7:
                /* code */
                break;
            
            case 8:
                /* code */
                break;
            
            default:
                std::this_thread::sleep_for(std::chrono::seconds(5));
                break;
            }
            
            // std::cout<<from<<"->"<<to<<std::endl;
            controler.take_passangers(train_cap, to);
            from = to;
            to = controler.where_to_go(to);
            // std::cout<<from<<"->"<<to<<std::endl;
            is_on_map = true;
            controler.exit_city(from);
        }
    }
}

void Train::start(int f)
{
    from = f;
    to = controler.start_destination(f);
    is_on_map = true;
}

void Train::set_up_route(int f, int t)
{
    to = t;
    from = f;
}
