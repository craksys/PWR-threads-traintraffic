#ifndef GUI_HEADER
#define GUI_HEADER

#include "gui_map.hpp"
#include <ncurses.h>
#include <vector>
#include <string>

class GUI {
private:
    WINDOW *menu_win;
    WINDOW *info_win;
    GUImap gui_map;
    std::vector<std::string> optionsVector;
    int counter = 0;
    int option = 0;

public:
    void setUpGUI(const std::vector<City>& c, const std::map<int, occupied_track>& t, const std::vector<std::vector<std::vector<Track>>>& r);
    int getCounter() const;
    void printOptions() const;
    void show();
};

#endif