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
    void addElement(int x, int y, const std::string &element);
    int getCounter() const;
    bool drawTrainOnMap(int a, int b, int possition);
    void printOptions() const;
    void GUIParams();
    void show();
};

#endif