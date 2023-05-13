#include "gui_map.hpp"
#include <ncurses.h>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>

void GUImap::setUpGUImap(const std::vector<City>& c,const std::map<int, occupied_track>& t, const std::vector<std::vector<std::vector<Track>>>& r){
    cities = c;
    trains = t;
    routes = r;
    
    // for (auto&& city : cities) {
    //     std::cout<<std::endl<<city.x<<" "<<city.y<<" "<<city.name<<std::endl
    // }
}

void GUImap::drawCities(WINDOW *win) {
    for (auto&& city : cities) {
        mvwprintw(win, city.y - yOffset, city.x, city.name.c_str());
        mvwprintw(win, city.y, city.x,"%s","XX");
        mvwprintw(win, city.y+1, city.x,"%s","XX");
    }
}
void GUImap::drawRailsName(WINDOW *win) {
    for (auto&& city : cities) {
        mvwprintw(win, city.y, city.x - 6, city.name.c_str());
    }
}

void GUImap::drawConnections(WINDOW *win) {
    for (int i = 0; i < cities.size(); i++) {
        for (int j = 0; j < cities.size(); j++) {
            for (auto &&point : routes[i][j])
            {
                mvwprintw(win, point.y, point.x, "%c", point.typeOfTrack);
            }
        }
    }
}

void GUImap::drawTrains(WINDOW *win){

}
