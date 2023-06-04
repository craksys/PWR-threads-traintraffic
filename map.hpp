#ifndef MAP_HEADER
#define MAP_HEADER

// #include "rails.hpp"
#include <vector>
#include <map>
#include <string>
#include <mutex>

// struct occupied_track {
//     int to;
//     int from;
//     int position = 0;
//     Rail* rail;

//     occupied_track(int to, int from, Rail* rail) : to(to), from(from), rail(rail) {}
// };

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
    
    std::mutex mutex_rails[1000];
    std::vector<City> cities;
    std::map<int,int> map_rail;
    // std::map<int, RailMutex> mutex_rails;
    // std::vector<Train> trains_on_map;
    std::vector<std::vector<bool>> areConnections;
    std::vector<std::vector<std::vector<Track>>> routes;
    // std::vector<std::vector<Rail*>> rails;
    // std::vector<std::vector<Rail*>> crossovers;
    // bool is_next_track_the_same(std::vector<int>& track_ids);
    // void build_railtrack();
    
    public:
    int used_mutex = 0;
    const std::vector<City> getCities() const {return cities;}
    // std::mutex (&getMutexArray())[1000] {return mutex_rails;}
    // std::map<int,int> getMaper() {return map_rail;}
    const std::vector<std::vector<std::vector<Track>>> getRoutes() const {return routes;}
    const std::vector<std::vector<bool>> getAreConnections() const {return areConnections;}
    // const std::vector<std::vector<Rail*>> getRails() const {return rails;}
    // const std::vector<std::vector<Rail*>> getCrossovers() const {return crossovers;}
    
    std::vector<Track> line(int cityA, int cityB, int trackInLine);

    void lock_mutex(int x,int y);
    void unlock_mutex(int x,int y);

    void addLocation(int x, int y, const std::string name);
    void matrixes();
    void connect(int cityB, int cityA, int trackInLine);
    void revers(int cityA, int cityB);
    void create_rails();
    // void start_train_on_map(int train_id, int cityA, int cityB);
    // void move_train_forvard(int train_id);
};

#endif