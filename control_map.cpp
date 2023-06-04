#include "control_map.hpp"
#include <iostream>

void Control_map::addLocation(int pas, int tr_cap, int ct_s)
{
    cities_data.push_back(City_data(pas,tr_cap,ct_s));
}

void Control_map::setUpConnections(std::vector<std::vector<bool>> c)
{
    is_connections = c;
}

void Control_map::take_passangers(int tr_pass_cap, int city)
{
    cities_data[city].pasangers -= tr_pass_cap;
    if(cities_data[city].pasangers < 0) cities_data[city].pasangers = 0;
}

void Control_map::next_hour()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(20));
        for (auto &&city : cities_data)
        {
            city.pasangers += 150 * (std::rand()%city.city_size);
            if(city.pasangers>city.pasangers_capisity) city.pasangers = city.pasangers_capisity;
        }
    }
}

void Control_map::exit_city(int city)
{
    cities_data[city].trains_in_city--;
    cities_data[city].sended_here--;
}

bool Control_map::enter_city(int city)
{
    city_mutex[city].lock();
    if(cities_data[city].trains_in_city<cities_data[city].train_capacity){
        cities_data[city].trains_in_city++;
        city_mutex[city].unlock();
        return true;
    }else{
        city_mutex[city].unlock();
        return false;
    }
}

int Control_map::where_to_go(int from)
{
    // std::cout<<is_connections.size()<<std::endl;
    int conn_to;
    int am_of_pass = -10000;
    
    for(int i = 0, j = std::rand() % cities_data.size(); i<cities_data.size(); i++, j++){
        if (j == cities_data.size()) j=0;
        if (j == from) continue;
        if(is_connections[from][j]){
            if(am_of_pass<cities_data[j].pasangers-(cities_data[j].sended_here*100)){
                // std::cout<<i<<"  "<<cities_data[i].pasangers<<std::endl;
                am_of_pass = cities_data[j].pasangers;
                conn_to = j;
                // std::cout<<from<<"->"<<conn_to<<std::endl;
            }
        }
    }
    // std::cout<<from<<"->"<<conn_to<<std::endl;
    cities_data[conn_to].sended_here++;
    return conn_to;
}

int Control_map::start_destination(int from)
{
    int conn_to;
    for(int i = 0, j = std::rand() % cities_data.size(); i<cities_data.size(); i++, j++){
        if (j == cities_data.size()) j=0;
        if (j == from) continue;
        if(is_connections[from][j]){
            // std::cout<<i<<"  "<<cities_data[i].pasangers<<std::endl;
            conn_to = j;
            // std::cout<<from<<"->"<<conn_to<<std::endl;
            
        }
    }
    // std::cout<<from<<"->"<<conn_to<<std::endl;
    cities_data[conn_to].sended_here++;
    return conn_to;
}
