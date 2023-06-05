#include "gui_map.hpp"
#include <ncurses.h>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>

void GUImap::setUpGUImap(const std::vector<City>& c, const std::vector<std::vector<std::vector<Track>>>& r) {
    cities = c;
    routes = r;
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

void GUImap::drawReverseRailsName(WINDOW *win) {
    for (auto&& city : cities) {
        mvwprintw(win, city.y, city.x + 2, city.name.c_str());
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

void GUImap::drawTrains(WINDOW *win, std::vector<Train>& trains){
    for (auto &&train : trains)
    {
        if(train.get_draw_on_map()){
            mvwprintw(win, 
            routes[train.form_city()][train.to_city()][train.distance()].y,
            routes[train.form_city()][train.to_city()][train.distance()].x, 
            "%c",
            routes[train.form_city()][train.to_city()][train.distance()].typeOfTrack);
        }
    }
    
}

void GUImap::drawTrainsOnStation(WINDOW *win, std::vector<Train>& trains, int c){
    for (auto &&train : trains)
    {
        if(train.get_draw_in_city(c)){
            mvwprintw(win, 
            routes[train.form_track()][train.to_track()][train.distance_track()].y,
            routes[train.form_track()][train.to_track()][train.distance_track()].x, 
            "%c",
            routes[train.form_track()][train.to_track()][train.distance_track()].typeOfTrack);
        }
    }
    
}

void GUImap::drawStatiscick(WINDOW *win, Control_map &contr)
{
    int x = 165;
    int y = 2;
    std::vector<City_data> cities_data = contr.getCitiesData();
    for (int i=0; i<cities.size(); i++)
    {
        mvwprintw(win, y, x, "%s:  %2d   %2d", cities[i].name.c_str(), cities_data[i].sended_here, cities_data[i].pasangers-cities_data[i].sended_here*100);
        y++;
        mvwprintw(win, y, x, "%s %2d/%2d", "  Pociagi:   ", cities_data[i].trains_in_city, cities_data[i].train_capacity);
        y++;
        mvwprintw(win, y, x, "%s %2d/%2d", "  Pasarzerowie:   ", cities_data[i].pasangers, cities_data[i].pasangers_capisity);
        y++;
        y++;
    }
    
}

void GUImap::drawNiceStatiscic(WINDOW *win, Control_map &contr)
{

    int x = 165;
    int y = 2;
    std::vector<City_data> cities_data = contr.getCitiesData();
    for (int i=0; i<cities.size(); i++)
    {
        
        mvwprintw(win, y, x, "%s:", cities[i].name.c_str());
        std::string str = bar(cities_data[i].train_capacity);
        mvwprintw(win, y+1, x, "  %s %s", "Pociagi:", str.c_str());
        str = bar(15);
        mvwprintw(win, y+2, x, "  %s %s", "Pasarzerowie:", str.c_str());

        wattron(win, COLOR_PAIR(3));
        str = bar(cities_data[i].trains_in_city);
        mvwprintw(win, y+1, x+11, "%s", str.c_str());
        str = bar(int(15*(float(cities_data[i].pasangers)/float(cities_data[i].pasangers_capisity))));
        mvwprintw(win, y+2, x+15, "  %s", str.c_str());
        wattroff(win, COLOR_PAIR(3));
        y+=4;
    }
}

std::string GUImap::bar(int num)
{
    std::string result;
    for (int i = 0; i < num; i++) {
        result += '#';
    }
    return result;
}
