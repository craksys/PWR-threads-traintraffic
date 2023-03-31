#include "gui_map.hpp"
#include <ncurses.h>
#include <cmath>
#include <vector>
#include <string>

void GUImap::addLocation(int x, int y, const std::string& name) {
    x_coords.push_back(x);
    y_coords.push_back(y);
    names.push_back(name);
}

void GUImap::drawMap(WINDOW *win) {
    for (size_t i = 1; i < x_coords.size(); i++) {
        mvwprintw(win, y_coords[i], x_coords[i], names[i].c_str());
    }
}

void GUImap::drawConnection(int cityB, int cityA, WINDOW *win) {
    // Obliczanie odległości między punktami
    int dx = abs(x_coords[cityB] - x_coords[cityA]);
    int dy = abs(y_coords[cityB] - y_coords[cityA]);
    int steps = std::max(std::abs(dx), std::abs(dy));
    float x_increment = (float)dx / (float)steps;
    float y_increment = (float)dy / (float)steps;

    // Rysowanie linii
    float x = x_coords[cityB], y = y_coords[cityB];
    for (int i = 0; i <= steps; i++) {
        int round_x = std::round(x);
        int round_y = std::round(y);
        mvwprintw(win, y_coords[i], x_coords[i], names[i].c_str());
        x += x_increment;
        y += y_increment;
    }

    // Wypisywanie koordynatów punktów na linii
    int line_x = x_coords[cityB], line_y = y_coords[cityB];
    for (int i = 0; i <= steps; i++) {
        mvprintw(line_y, line_x, "(%d, %d)", line_x, line_y);
        line_x += std::round(x_increment);
        line_y += std::round(y_increment);
    }
}
