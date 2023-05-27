#ifndef MAP_HEADER
#define MAP_HEADER

#include "rails.hpp"
#include <vector>
#include <map>
#include <string>

struct occupied_track {
    int to;
    int from;
    int position = 0;
    Rail* rail;

    occupied_track(int to, int from, Rail* rail) : to(to), from(from), rail(rail) {}
};

struct Track {
    int x;
    int y;
    char typeOfTrack;
    
    Track(int x, int y, char track) : x(x), y(y), typeOfTrack(track) {}
};

struct City {
    int x;
    int y;
    std::string name;

    City(int x, int y, std::string name ) : x(x), y(y), name(name) {}
};

class World_map {
    private:
    std::vector<City> cities;
    std::map<int, occupied_track> trains_on_map;
    std::vector<std::vector<std::vector<Track>>> routes;
    std::vector<std::vector<Rail*>> rails;
    std::vector<std::vector<Rail*>> crossovers;
    bool is_next_track_the_same(std::vector<int>& track_ids);
    void build_railtrack();
    
    public:
    const std::vector<City> getCities() const {return cities;}
    const std::map<int, occupied_track> getTrainsOnMap() const {return trains_on_map;}
    const std::vector<std::vector<std::vector<Track>>> getRoutes() const {return routes;}
    const std::vector<std::vector<Rail*>> getRails() const {return rails;}
    const std::vector<std::vector<Rail*>> getCrossovers() const {return crossovers;}
    
    std::vector<Track> line(int cityA, int cityB, int trackInLine);

    void addLocation(int x, int y, const std::string name);
    void matrixes();
    void connect(int cityB, int cityA, int trackInLine);
    void revers(int cityA, int cityB);
    void create_rails();
    void start_train_on_map(int train_id, int cityA, int cityB);
    void move_train_forvard(int train_id);

    void connect_without_revers(int cityA, int cityB, int trackInLine);
};

#endif