#ifndef CONTROL_HEADER
#define CONTROL_HEADER

#include <thread>
#include <vector>
#include <mutex>


struct City_data {
    int pasangers_capisity;
    int pasangers;
    int train_capacity;
    int trains_in_city;
    int city_size;
    int sended_here;
    
    City_data(int pas, int tr_cap, int city_size)
        : pasangers_capisity(2000),
          pasangers(pas),
          train_capacity(tr_cap),
          trains_in_city(0),
          city_size(city_size),
          sended_here(0)
    {}
};


class Control_map{
    private:
    std::vector<City_data> cities_data;
    std::vector<std::vector<bool>> is_connections;
    std::mutex city_mutex[20];
    public:
    const std::vector<City_data>& getCitiesData() const {return cities_data;}
    void addLocation(int pas, int tr_cap, int ct_s);
    void setUpConnections(std::vector<std::vector<bool>> c);
    void take_passangers(int tr_pass_cap, int city);
    void next_hour();
    void exit_city(int city);
    bool enter_city(int city);
    int where_to_go(int from);
    int start_destination(int from);
};

#endif