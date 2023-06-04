#include "gui_map.hpp"
#include "gui.hpp"
#include <ncurses.h>
#include <vector>
#include <string>
#include <thread>
#include <iostream>

void GUI::setUpGUI(const std::vector<City>& c, const std::vector<std::vector<std::vector<Track>>>& r){
    optionsVector.push_back("Mapa");
    counter++;
    for (auto& city : c) {
        if(city.name == "Zgorzelec" || city.name == "Olesnica"){
            optionsVector.push_back(city.name);
            counter++;
        }
    }
    gui_map.setUpGUImap(c, r);
}

void GUI::setUpGUIOlesnica(const std::vector<City>& c, const std::vector<std::vector<std::vector<Track>>>& r){

    olesnica_map.setUpGUImap(c, r);
}

void GUI::setUpGUIZgorzelec(const std::vector<City>& c, const std::vector<std::vector<std::vector<Track>>>& r){

    zgorzelec_map.setUpGUImap(c, r);
}

int GUI::getCounter() const {
    return counter;
}

void GUI::printOptions() const {
    int len = 0;
    for (int i=0; i<getCounter(); i++) {
        if (i == option) {
            wattron(menu_win, A_REVERSE);
        }
        if (i==0) mvwprintw(menu_win, 2, 20, optionsVector[0].c_str());
        else mvwprintw(menu_win, 2, 44 + i*5 + len, optionsVector[i].c_str());
        len += optionsVector[i].length();
        wattroff(menu_win, A_REVERSE);
    }
}

void GUI::keyboard(){
    int ch;
    while ((ch = getch()) != KEY_F(1))
    {
        switch(ch) {
            case KEY_DOWN:
                option--;
                if (option < 0) {
                    option = getCounter() - 1;
                }
                break;
            case KEY_UP:
                option++;
                if (option >= getCounter()) {
                    option = 0;
                }
                break;
        }

        
    }
    
    
}



void GUI::show(std::vector<Train>& trains, Control_map& contr){
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);

    menu_win = newwin(5, COLS, 0, 0);
    info_win = newwin(LINES-5, COLS, 5, 0);

    wbkgd(menu_win, COLOR_PAIR(1));
    wbkgd(info_win, COLOR_PAIR(2));

    printOptions();

    refresh();
    wrefresh(menu_win);
    wrefresh(info_win);

    while(true) {
        
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        wclear(info_win);
        if(option == 0){
            gui_map.drawConnections(info_win);
            gui_map.drawCities(info_win);
            // gui_map.drawStatiscick(info_win, contr);
            gui_map.drawNiceStatiscic(info_win, contr);
            wattron(info_win, COLOR_PAIR(3));
            gui_map.drawTrains(info_win, trains);
            wattroff(info_win, COLOR_PAIR(3));
        } else if(option == 1){
            olesnica_map.drawConnections(info_win);
            olesnica_map.drawRailsName(info_win);
            wattron(info_win, COLOR_PAIR(3));
            // olesnica_map.drawTrains(info_win);
            wattroff(info_win, COLOR_PAIR(3));
        } else if(option == 2){
            zgorzelec_map.drawConnections(info_win);
            zgorzelec_map.drawReverseRailsName(info_win);
            wattron(info_win, COLOR_PAIR(3));
            // zgorzelec_map.drawTrains(info_win);
            wattroff(info_win, COLOR_PAIR(3));
        }
      
      else{
            mvwprintw(info_win, 2, 20, optionsVector[option].c_str());
        }
        wrefresh(info_win);

        printOptions();

        wrefresh(menu_win);

    }

    delwin(menu_win);
    delwin(info_win);
    endwin();

}