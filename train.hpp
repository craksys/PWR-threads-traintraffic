#ifndef TRAIN_HEADER
#define TRAIN_HEADER

#include "map.hpp"
#include "control_map.hpp"
#include <thread>

class Train{
    private:
    bool draw_on_map = false;
    bool draw_in_city = false;
    bool is_on_map;
    int train_id;
    int train_cap = 100;
    int distance_map;
    int distance_tr;
    int speed;
    int from;
    int to;
    int from_tr;
    int to_tr;
    Control_map& controler;
    World_map& map;
    World_map& zgorzelec;
    World_map& olesnica;

    public:
    Train(int id, int speed, World_map& worldMap, Control_map& contr, World_map& zgorzelec, World_map& olesnica)
    : train_id(id), speed(speed), distance_map(-1), from(-1), to(-1), distance_tr(-1), from_tr(-1), to_tr(-1), map(worldMap), zgorzelec(zgorzelec), olesnica(olesnica), controler(contr) {}
    void run();
    void run_in_city(World_map& map);
    void start(int f);

    void set_up_route(int f, int t);
    void get_on_map(int x, int y);
    void ride_on_map(int x, int y);
    void get_off_map(int x, int y);

    void get_on_track(World_map& city_map, int x, int y);
    void ride_on_track(World_map& city_map, int x, int y);
    void get_off_track(World_map& city_map, int x, int y);

    bool get_draw_on_map() {return draw_on_map;};
    bool get_draw_in_city(int c) {return draw_in_city && c==to;};
    bool get_is_on_map() {return is_on_map;};
    void set_is_on_map(bool is);
    int form_city();
    int to_city();
    int distance();
    int form_track();
    int to_track();
    int distance_track();

    int getFromOlesnica(int to, World_map &city_map);

    int getToOlesnica(int to, World_map &city_map);

    int getFromZgorzelec(int to, World_map &city_map);

    int getToZgorzelec(int to, World_map &city_map);
};

#endif