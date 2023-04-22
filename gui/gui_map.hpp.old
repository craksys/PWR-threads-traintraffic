#ifndef GUI_MAP_HEADER
#define GUI_MAP_HEADER

#include <ncurses.h>
#include <vector>
#include <string>
#include <array>

struct Track {
    int x;
    int y;
    char typeOfTrack;

    Track(int x, int y, char track) : x(x), y(y), typeOfTrack(track) {}
};


class GUImap {
private:
    std::vector<std::vector<std::vector<Track>>> routes;
    std::vector<int> x_coords;
    std::vector<int> y_coords;
    std::vector<std::string> names;
    int xffset = 0;
    int yOffset = 2;

public:
    std::vector<Track> line(int Ax, int Ay, int Bx, int By, int trackInLine, bool up);
    std::vector<std::vector<std::vector<Track>>> getRoutes();
    void matrix();
    void addLocation(int x, int y, const std::string& name);
    void drawMap(WINDOW *win);
    void connect(int cityB, int cityA, int trackInLine, bool up);
    void revers(int cityA, int cityB, bool up);
    void drawConnections(WINDOW *win);
    
};

#endif
