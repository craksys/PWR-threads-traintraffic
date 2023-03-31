#include <ncurses.h>
#include <vector>
#include <string>
#include <array>

class GUImap {
private:
    std::vector<std::vector<std::array<int, 2> >> routes;
    std::vector<int> x_coords;
    std::vector<int> y_coords;
    std::vector<std::string> names;

public:
    void addLocation(int x, int y, const std::string& name);
    void drawMap(WINDOW *win);
    void drawConnection(int cityB, int cityA, WINDOW *win);
};
