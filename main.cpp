#include "gui/gui.hpp"
#include "map.hpp"
#include <iostream>

int main()
{
    World_map map;
    map.addLocation(120,20,"Wroclaw");   //0
    map.addLocation(115,5,"Rawicz");     //1
    map.addLocation(125,7,"Trzebnica");  //2
    map.addLocation(20,7,"Zagan");       //3
    map.addLocation(70,20,"Legnica");    //4
    map.addLocation(70,36,"Walbrzych");  //5
    map.addLocation(125,40,"Klodzko");   //6
    map.addLocation(150,15,"Olesnica");  //7
    map.addLocation(10,30,"Zgorzelec");  //8
    map.addLocation(70,5,"Glogow");      //9
    map.matrixes();
    
    map.connect(4, 0, 1);
    map.connect(9, 0, 15);
    map.connect(5, 0, 10);
    map.connect(0, 1, 7);
    map.connect(0, 2, 1);
    map.connect(0, 7, 5);
    map.connect(3, 9, 40);
    map.connect(3, 4, 4);
    map.connect(8, 4, 27);
    map.connect(8, 5, 35);
    map.connect(6, 0, 4);
    map.create_rails();
    // GUI gui;
    // gui.setUpGUI(map.getCities(), map.getTrainsOnMap(), map.getRoutes());
    // gui.show();

    return 0;
}