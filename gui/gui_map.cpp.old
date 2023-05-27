#include "gui_map.hpp"
#include <ncurses.h>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>

typedef std::vector<std::vector<int>> Matrix;

std::vector<std::vector<std::vector<Track>>> GUImap::getRoutes(){
    return routes;
};

void GUImap::addLocation(int x, int y, const std::string& name) {
    x_coords.push_back(x);
    y_coords.push_back(y);
    names.push_back(name);
}

void GUImap::drawMap(WINDOW *win) {
    for (size_t i = 1; i < x_coords.size(); i++) {
        mvwprintw(win, y_coords[i], x_coords[i], names[i].c_str());
        mvwprintw(win, y_coords[i]+yOffset, x_coords[i]-1+names[i].size()/2,"%s","XX");
        mvwprintw(win, y_coords[i]+yOffset+1, x_coords[i]-1+names[i].size()/2,"%s","XX");
    }
}

void GUImap::matrix(){
    int N = x_coords.size();
    std::vector<std::vector<std::vector<Track>>> matrix(N, std::vector<std::vector<Track>>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = std::vector<Track>();
        }
    }
    routes = matrix;
}

std::vector<Track> GUImap::line(int Ax, int Ay, int Bx, int By, int trackInLine, bool up){
    std::vector<Track> points;
    char diagonaChar;
    int slope;
    int step = 1;
    int x = Ax;
    int y = Ay;
    if(up){
        
        By = By+yOffset;
        for(int i=0;i<trackInLine;i++){{
            y -= step;
            points.push_back(Track(x,y,'|'));
            }
        }

        if(Ax < Bx){
            while (x < Bx){
                y += -1;
                points.push_back(Track(x,y,'/'));

                x += 1;
            }
            y += -1;
            points.push_back(Track(x,y,'/'));
        }
        else{
            y += -1;
            points.push_back(Track(x,y,'\\'));
            while (x > Bx){
                x += -1;
                y += -1;
                points.push_back(Track(x,y,'\\'));
            }
        }

        while(y > By){
        y -= step;
        points.push_back(Track(x,y,'|'));
        }
    }else{
        y = y+1;
        Bx = Bx-2;
        By = By+1;
        for(int i=0;i<trackInLine;i++){{
            x += step;
            points.push_back(Track(x,y,'_'));
            }
        }

        if(Ay < By){
            while (y < By){
                x += 1;
                y += 1;
                points.push_back(Track(x,y,'\\'));
            }
        }
        else{
            while (y > By){
                x += 1;
                points.push_back(Track(x,y,'/'));
                y += -1;
            }
        }

        while(x<Bx){
        x += step;
        points.push_back(Track(x,y,'_'));
        }
    }
    return points;
}

void GUImap::revers(int cityA, int cityB, bool up){
    if(up){
        for(int i = routes[cityA][cityB].size(); i >= 0; i--){
        routes[cityB][cityA].push_back(Track(routes[cityA][cityB][i].x-1,routes[cityA][cityB][i].y,routes[cityA][cityB][i].typeOfTrack));
        }
    }else{
        for(int i = routes[cityA][cityB].size(); i >= 0; i--){
        routes[cityB][cityA].push_back(Track(routes[cityA][cityB][i].x,routes[cityA][cityB][i].y-1,routes[cityA][cityB][i].typeOfTrack));
        }
    }
    
}

void GUImap::connect(int cityA, int cityB, int trackInLine, bool up){
    routes[cityA][cityB] = line(x_coords[cityA]+names[cityA].size()/2, y_coords[cityA] + yOffset, x_coords[cityB]+names[cityB].size()/2, y_coords[cityB] + yOffset, trackInLine, up);
    revers(cityA,cityB,up);
}

void GUImap::drawConnections(WINDOW *win) {
    for (int i = 0; i < x_coords.size(); i++) {
        for (int j = 0; j < x_coords.size(); j++) {
            for (auto &&point : routes[i][j])
            {
                mvwprintw(win, point.y, point.x, "%c", point.typeOfTrack);
            }
        }
    }
}
