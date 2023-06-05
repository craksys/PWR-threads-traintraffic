#include "train.hpp"
#include <iostream>
#include <iostream>
#include <cstdlib>  // for rand() and srand()
#include <ctime>    // for time()



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

void Train::get_off_map( int x, int y)
{
    map.unlock_mutex(x, y);
    distance_map = -1;
    draw_on_map = false;
    is_on_map = false;
}

void Train::get_on_track(World_map& city_map, int x, int y)
{
    city_map.lock_mutex(x, y);
    draw_in_city = true;
    distance_tr = 0;
}

void Train::ride_on_track(World_map& city_map, int x, int y)
{
    x = city_map.getRoutes()[from_tr][to_tr][distance_tr+1].x;
    y = city_map.getRoutes()[from_tr][to_tr][distance_tr+1].y;
    city_map.lock_mutex(x, y);
    distance_tr++;

    x = city_map.getRoutes()[from_tr][to_tr][distance_tr-1].x;
    y = city_map.getRoutes()[from_tr][to_tr][distance_tr-1].y;
    city_map.unlock_mutex(x, y);
}


void Train::get_off_track(World_map& city_map, int x, int y)
{
    city_map.unlock_mutex(x, y);
    distance_tr = -1;
    draw_in_city = false;
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

int Train::form_track()
{
    return from_tr;
}

int Train::to_track()
{
    return to_tr;
}

int Train::distance_track()
{
    return distance_tr;
}

void Train::run_in_city(World_map& city_map){
    srand(time(0));
    int breaker = 0;
    int xt = 0;
    int yt = 0;
    from_tr = 0;
    to_tr = 1;
    while(true){ //cos innego
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            if(distance_tr==-1){
                xt = city_map.getRoutes()[from_tr][to_tr][0].x;
                yt = city_map.getRoutes()[from_tr][to_tr][0].y;
                get_on_track(city_map, xt, yt);
            }else if(city_map.getRoutes()[from_tr][to_tr].size()<distance_tr+2){
                if(to == 7) {
                    xt = city_map.getRoutes()[from_tr][to_tr][distance_tr].x;
                    yt = city_map.getRoutes()[from_tr][to_tr][distance_tr].y;
                    breaker = getFromOlesnica(to_tr, city_map);
                    if (breaker == -1) {
                        get_off_track(city_map, xt, yt);
                        break;
                    }
                    from_tr = breaker;
                    to_tr = getToOlesnica(to_tr, city_map);
                    get_off_track(city_map, xt, yt);
                }else if (to == 8){
                    xt = city_map.getRoutes()[from_tr][to_tr][distance_tr].x;
                    yt = city_map.getRoutes()[from_tr][to_tr][distance_tr].y;
                    breaker = getFromZgorzelec(to_tr, city_map);
                    if (breaker == -1) {
                        get_off_track(city_map, xt, yt);
                        break;
                    }
                    from_tr = breaker;
                    to_tr = getToZgorzelec(to_tr, city_map);
                    get_off_track(city_map, xt, yt);
                }
            }else{
                xt = city_map.getRoutes()[from_tr][to_tr][distance_tr].x;
                yt = city_map.getRoutes()[from_tr][to_tr][distance_tr].y;
                ride_on_track(city_map, xt, yt);
            }
    }
}

int Train::getFromZgorzelec(int to, World_map& city_map){
    switch(to){
        case 1:
            if (city_map.counter[0]){
                return 4;
            }else{
                return 6;
            }
        case 7:
            return 32;//koniec pierwszego toru
        case 5:
            if (city_map.counter[1]){
                return 10;
            }else{
                return 14;
            }
        case 15:
            return 30;
        case 11:
            return 12;
        case 13:
            if (city_map.counter[2]){
                return 16;
            }else{
                return 20;
            }
        case 21:
            return 28;
        case 17:
            return 18;
        case 19:
            if (city_map.counter[3]){
                return 22;
            }else{
                return 26;
            }
        case 23:
            return 24;
            //tutaj powrot sie zaczyna
        case 49:
            return 46;
        case 47:
            return 42;
        case 41:
            return 36;
        case 37:
            return 34;
        case 35:
            return 2;
        case 51:
            return 42;
        case 45:
            return 36;
        case 39:
            return 2;
        case 43:
            return 40;
        case 3:
            return -1;
        default:
            city_map.intcounter = rand() % 4;
            switch(city_map.intcounter){
                case 0:
                    return 48;
                    break;
                case 1:
                    return 50;
                    break;
                case 2:
                    return 24;
                    break;
                case 3:
                    return 38;
                    break;
                default:
                    return 0;
                    break;
            }

    }
}

int Train::getToZgorzelec(int to, World_map& city_map){
    switch(to){
        case 1:
            if (city_map.counter[0]){
                city_map.counter[0] = false;
                return 5;
            }else{
                city_map.counter[0] = true;
                return 7;
            }
        case 7:
            return 33;//koniec pierwszego toru
        case 5:
            if (city_map.counter[1]){
                city_map.counter[1] = false;
                return 11;
            }else{
                city_map.counter[1] = true;
                return 15;
            }
        case 15:
            return 31;
        case 11:
            return 13;
        case 13:
            if (city_map.counter[2]){
                city_map.counter[2] = false;
                return 17;
            }else{
                city_map.counter[2] = true;
                return 21;
            }
        case 21:
            return 29;
        case 17:
            return 19;
        case 19:
            if (city_map.counter[3]){
                city_map.counter[3] = false;
                return 23;
            }else{
                city_map.counter[3] = true;
                return 27;
            }
        case 23:
            return 25;
        case 49:
            return 47;
        case 47:
            return 43;
        case 41:
            return 37;
        case 37:
            return 35;
        case 35:
            return 3;
        case 51:
            return 43;
        case 45:
            return 37;
        case 39:
            return 3;
        case 43:
            return 41;

        default:
            switch(city_map.intcounter){
                case 0:
                    return 49;
                    break;
                case 1:
                    return 51;
                    break;
                case 2:
                    return 25;
                    break;
                case 3:
                    return 39;
                    break;
                default:
                    return 1;
                    break;
            }

    }
}

int Train::getFromOlesnica(int to, World_map& city_map){
    switch(to){
        case 1:
            if (city_map.counter[0]){
                return 4;
            }else{
                return 6;
            }
            break;
        case 5:
            return 26;
            break;
        case 27:
            if (city_map.counter[1]){
                return 32;
            }else{
                return 34;
            }
            break;
        case 7:
            if (city_map.counter[2]){
                return 30;
            }else{
                return 28;
            }
            break;
        case 13:
            return 10;
            break;
        case 11:
            return 2;
            break;
        case 21:
            return 14;
        case 19:
            return 14;
        case 15:
            return 10;
        case 25:
            return 16;
        case 23:
            return 16;
        case 17:
            return 8;
        case 9:
            return 2;
        case 3:
            return -1;
        default:
            city_map.intcounter = rand() % 5;
            switch(city_map.intcounter){
                case 0:
                    return 12;
                    break;
                case 1:
                    return 20;
                    break;
                case 2:
                    return 18;
                    break;
                case 3:
                    return 24;
                    break;
                case 4:
                    return 22;
                    break;
                default:
                    return 12;
                    break;
            }

            return 0;
            break;
    }

}

int Train::getToOlesnica(int to, World_map& city_map){
    switch(to){
        case 1:
            if (city_map.counter[0]){
                city_map.counter[0] = false;
                return 5;
            }else{
                city_map.counter[0] = true;
                return 7;
            }
            break;
        case 5:
            return 27;
            break;
        case 27:
            if (city_map.counter[1]){
                city_map.counter[1] = false;
                return 33;
            }else{
                city_map.counter[1] = true;
                return 35;
            }
            break;
        case 7:
            if (city_map.counter[2]){
                city_map.counter[2] = false;
                return 31;
            }else{
                city_map.counter[2] = true;
                return 29;
            }
        case 13:
            return 11;
            break;
        case 11:
            return 3;
            break;
        case 21:
            return 15;
        case 19:
            return 15;
        case 15:
            return 11;
        case 25:
            return 17;
        case 23:
            return 17;
        case 17:
            return 9;
        case 9:
            return 3;


        default:
            switch(city_map.intcounter){
                case 0:
                    return 13;
                    break;
                case 1:
                    return 21;
                    break;
                case 2:
                    return 19;
                    break;
                case 3:
                    return 25;
                    break;
                case 4:
                    return 23;
                    break;
                default:
                    return 13;
                    break;
            }
            return 1;
            break;
    }


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
                run_in_city(olesnica);
                break;

            case 8:
                run_in_city(zgorzelec);
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
