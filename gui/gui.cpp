#include "gui_map.hpp"
#include "gui.hpp"
#include <ncurses.h>
#include <vector>
#include <string>

void GUI::addElement(int x, int y, const std::string& element) {
    optionsVector.push_back(element);
    gui_map.addLocation(x,y,element);
    counter++;
}

int GUI::getCounter() const {
    return counter;
}

bool GUI::drawTrainOnMap(int a, int b, int possition)
{
    if(possition>gui_map.getRoutes()[a][b].size()>=0){
        Track tr = gui_map.getRoutes()[a][b][possition];
        mvwprintw(info_win, tr.y, tr.x, "%c", tr.typeOfTrack);
    }
    
    return false;
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

void GUI::show(){
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

    int ch;
    while((ch = getch()) != KEY_F(1)) {
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
            case '\n':
                wclear(info_win);
                if(option == 0){
                    gui_map.drawConnections(info_win);
                    gui_map.drawMap(info_win);
                    //THEN DRAW TRAINS
                    //TODO connect it with threads
                    wattron(info_win, COLOR_PAIR(3));
                    drawTrainOnMap(5,1,6);
                    wattroff(info_win, COLOR_PAIR(3));
                }else{
                    mvwprintw(info_win, 2, 20, optionsVector[option].c_str());
                }
                wrefresh(info_win);
                break;
        }

        printOptions();

        wrefresh(menu_win);

    }

    delwin(menu_win);
    delwin(info_win);
    endwin();

}

void GUI::GUIParams(){
addElement(0,0,"Mapa");
addElement(120,20,"Wroclaw");   //1
addElement(115,5,"Rawicz");     //2
addElement(125,7,"Trzebnica");  //3
addElement(20,7,"Zagan");       //4
addElement(70,20,"Legnica");    //5
addElement(70,36,"Walbrzych");  //6
addElement(125,40,"Klodzko");   //7
addElement(150,15,"Olesnica");  //8
addElement(10,30,"Zgorzelec");  //9
addElement(70,5,"Glogow");      //10
gui_map.matrix();
gui_map.connect(5,1, 1, false);
gui_map.connect(10,1, 15, false);
gui_map.connect(6,1, 10, false);
gui_map.connect(1,2, 7, true);
gui_map.connect(1,3, 1, true);
gui_map.connect(1,8,5,false);
gui_map.connect(4,10,40,false);
gui_map.connect(4,5,4,false);
gui_map.connect(9,5,27,false);
gui_map.connect(9,6,35,false);
gui_map.connect(7,1,4,true);
}
