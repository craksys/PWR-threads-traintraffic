#ifndef GUI_MAP_HEADER
#define GUI_MAP_HEADER

#include "../map.hpp"
#include "../train.hpp"
#include <ncurses.h>
#include <vector>
#include <string>


class GUImap {
private:
    std::vector<City> cities;
    std::vector<std::vector<std::vector<Track>>> routes;
    int xOffset = -2;
    int yOffset = 1;

public:
    void setUpGUImap(const std::vector<City>& cities_ref, 
            const std::vector<std::vector<std::vector<Track>>>& routes_ref) ;
    void drawCities(WINDOW *win);
    void drawConnections(WINDOW *win);
    void drawTrains(WINDOW *win, std::vector<Train>& trains);
    void drawStatiscick(WINDOW *win, Control_map& contr);
    void drawNiceStatiscic(WINDOW *win, Control_map& contr);
    std::string bar(int num);
};

#endif
