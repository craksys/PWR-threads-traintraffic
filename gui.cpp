#include "gui_map.hpp"
#include "rails.h"
#include "train.h"
#include <ncurses.h>
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>


class GUI {
private:
    WINDOW *menu_win;
    WINDOW *info_win;
    GUImap gui_map;
    std::vector<std::string> optionsVector;
    int counter = 0;
    int option = 0;

public:
    GUI(){}

    void addElement(int x, int y, const std::string& element) {
        optionsVector.push_back(element);
        gui_map.addLocation(x,y,element);
        counter++;
    }

    int getCounter() const {
        return counter;
    }

    void printOptions() const {
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

    void show(){
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);

        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLUE);
        init_pair(2, COLOR_WHITE, COLOR_BLACK);

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
                        gui_map.drawMap(info_win);
                        // gui_map.drawConnection(2,1,info_win);
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
};
/* INSTRUKCJA TWORZENIA POCIAGU
    Rails rails;
    Train train;
    railStruct* arr = rails.createRailStructArray(11);
    rails.createStraightSection(arr,0,10);
    std::thread myThread([&train, arr]() {
        train.createOutsideTrain(arr, 0, 250);
});*/
/*SYF DO WYŚWIETLANIA TORÓW
 while(true){
        for(int i = 0; i < 11; i++){
            std::cout << "tor: " << i << " " << arr[i].is_mtx_locked << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "-------------------------------------------" << std::endl;
    }*/

int main()
{

    GUI gui;
    gui.addElement(0,0,"Mapa");
    gui.addElement(120,20,"Wroclaw");
    gui.addElement(120,5,"Rawicz");
    gui.addElement(140,7,"Trzebnica");
    gui.addElement(20,7,"Zagan");
    gui.addElement(70,20,"Legnica");
    gui.addElement(70,40,"Walbrzych");
    gui.addElement(120,40,"Klodzko");
    gui.addElement(150,15,"Olesnica");
    gui.addElement(10,30,"Zgorzelec");
    gui.addElement(70,5,"Glogow");

    gui.show();
    return 0;
}


