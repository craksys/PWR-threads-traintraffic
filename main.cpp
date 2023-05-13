#include "gui/gui.hpp"
#include "map.hpp"
#include <iostream>

int main()
{
    World_map wroclaw;
    wroclaw.addLocation(-1,18,""); //min -1 // tor wyjsciowy gorny
    wroclaw.addLocation(20,18,"Tor 1"); //max 210

    wroclaw.addLocation(-1, 26, ""); //tor wyjsciowy dolny
    wroclaw.addLocation(20, 26, "Tor 2");

    wroclaw.addLocation(18,18,"");
    wroclaw.addLocation(40,16, "Tor 3");//od toru 1 w górę

    wroclaw.addLocation(22, 18,"");
    wroclaw.addLocation(40, 18,"Tor 4");

    wroclaw.addLocation(18,26,"");
    wroclaw.addLocation(40,28,"Tor 5");

    wroclaw.addLocation(22,26,"");
    wroclaw.addLocation(40,26,"Tor 6");

    wroclaw.addLocation(38,26,"");
    wroclaw.addLocation(100,24,"Tor 7");

    wroclaw.addLocation(42,26,"");
    wroclaw.addLocation(56,26,"Tor 8");

    wroclaw.addLocation(38,28,"");
    wroclaw.addLocation(80,34,"Tor 9");

    wroclaw.addLocation(54,26,"");
    wroclaw.addLocation(100,30,"Tor 10");

    wroclaw.addLocation(58,26,"");
    wroclaw.addLocation(100,26,"Tor 11");

    wroclaw.addLocation(78,34,"");
    wroclaw.addLocation(100,38,"Tor 12");

    wroclaw.addLocation(82,34,"");
    wroclaw.addLocation(100,34,"Tor 13");

    wroclaw.matrixes();
    wroclaw.connect_without_revers(0,1,3);
    wroclaw.connect_without_revers(2,3,3);
    wroclaw.connect_without_revers(4,5,3);
    wroclaw.connect_without_revers(6,7,3);
    wroclaw.connect_without_revers(8,9,3);
    wroclaw.connect_without_revers(10,11,3);
    wroclaw.connect_without_revers(12,13,3);
    wroclaw.connect_without_revers(14,15,3);
    wroclaw.connect_without_revers(16,17,3);
    wroclaw.connect_without_revers(18,19,3);
    wroclaw.connect_without_revers(20,21,3);
    wroclaw.connect_without_revers(22,23,3);
    wroclaw.connect_without_revers(24,25,3);
    wroclaw.create_rails();

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
    GUI gui;
    gui.setUpGUI(map.getCities(), map.getTrainsOnMap(), map.getRoutes());

    gui.setUpGUIWroclaw(wroclaw.getCities(),wroclaw.getTrainsOnMap(), wroclaw.getRoutes());


    gui.show();

    return 0;
}