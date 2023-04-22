#ifndef GUI_MAP_HEADER
#define GUI_MAP_HEADER

#include "../map.hpp"
#include <ncurses.h>
#include <vector>
#include <string>
#include <map>


class GUImap {
private:
    std::vector<City> cities;
    std::map<int, occupied_track> trains;
    std::vector<std::vector<std::vector<Track>>> routes;
    int xOffset = -2;
    int yOffset = 1;

public:
    void setUpGUImap(const std::vector<City>& cities_ref, const std::map<int, occupied_track>& trains_ref, 
          const std::vector<std::vector<std::vector<Track>>>& routes_ref) ;
    void drawCities(WINDOW *win);
    void drawConnections(WINDOW *win);
    void drawTrains(WINDOW *win);
};

#endif
