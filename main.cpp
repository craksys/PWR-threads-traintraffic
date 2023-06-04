#include "gui/gui.hpp"
#include "map.hpp"
#include "train.hpp"
#include "control_map.hpp"
#include "control_train.hpp"
#include <cstdlib> 
#include <ctime>
#include <vector>
#include <iostream>

/*
Podczas pisania tego kodu byliśmy obecni we trójke Ja, Kami i Bóg.
Kiedyś wszyscy wiedzieliśmy jak on działa.
Teraz tylko Bóg wie co sie dzieje w tym kodzie :)

Counter godzin spędzonych na czytaniu kodu: 10
Prosze zwiększać jak podjeło sie próbe.
*/

void createZgorzelec(World_map &zgorzelec);

void createOlesnica(World_map &olesnica);

int main()
{
    World_map olesnica;
    createOlesnica(olesnica);

    World_map zgorzelec;
    createZgorzelec(zgorzelec);


    World_map map;
    std::vector<Train> trains;
    std::vector<std::thread> threads;
    Control_map map_controler;
    Control_train train_controler;
    std::srand(std::time(0));

    map.addLocation(120,20,"Wroclaw");   //0
    map_controler.addLocation(500,5,10);
    map.addLocation(115,5,"Rawicz");     //1
    map_controler.addLocation(120,2,6);
    map.addLocation(125,7,"Trzebnica");  //2
    map_controler.addLocation(150,1,5);
    map.addLocation(20,7,"Zagan");       //3
    map_controler.addLocation(50,1,4);
    map.addLocation(70,20,"Legnica");    //4
    map_controler.addLocation(400,4,8);
    map.addLocation(70,36,"Walbrzych");  //5
    map_controler.addLocation(300,3,7);
    map.addLocation(125,40,"Klodzko");   //6
    map_controler.addLocation(400,2,6);
    map.addLocation(150,15,"Olesnica");  //7
    map_controler.addLocation(20,3,4);
    map.addLocation(10,30,"Zgorzelec");  //8
    map_controler.addLocation(30,2,4);
    map.addLocation(70,5,"Glogow");      //9
    map_controler.addLocation(0,1,5);
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


    map_controler.setUpConnections(map.getAreConnections());
    
    train_controler.test(trains, map, map_controler,zgorzelec, olesnica);
    train_controler.test(trains, map, map_controler, zgorzelec, olesnica);

    std::cout<<map.getAreConnections().size()<<std::endl;

    GUI gui;
    gui.setUpGUI(map.getCities(), map.getRoutes());
  
    gui.setUpGUIOlesnica(olesnica.getCities(), olesnica.getRoutes());
    gui.setUpGUIZgorzelec(zgorzelec.getCities(), zgorzelec.getRoutes());
  
    threads.emplace_back(&Control_map::next_hour, std::ref(map_controler));
    threads.emplace_back(&GUI::show, std::ref(gui), std::ref(trains), std::ref(map_controler));
    for (auto& train : trains) {
        threads.emplace_back(&Train::run, &train);
    }

    gui.keyboard();

    for (auto& thread : threads) {
        thread.join();
    }



    return 0;
}

void createOlesnica(World_map &olesnica) {
    olesnica.addLocation(-1, 18, ""); //min -1 // tor wyjsciowy gorny
    olesnica.addLocation(20, 18, "Tor 1"); //max 210

    olesnica.addLocation(-1, 26, ""); //tor wyjsciowy dolny
    olesnica.addLocation(20, 26, "Tor 2");

    olesnica.addLocation(18, 18, "");
    olesnica.addLocation(40, 16, "Tor 3");//od toru 1 w górę

    olesnica.addLocation(22, 18, "");
    olesnica.addLocation(40, 18, "Tor 4");

    olesnica.addLocation(18, 26, "");
    olesnica.addLocation(40, 28, "Tor 5");

    olesnica.addLocation(22, 26, "");
    olesnica.addLocation(40, 26, "Tor 6");

    olesnica.addLocation(38, 26, "");
    olesnica.addLocation(100, 24, "Tor 7");

    olesnica.addLocation(42, 26, "");
    olesnica.addLocation(56, 26, "Tor 8");

    olesnica.addLocation(38, 28, "");
    olesnica.addLocation(80, 34, "Tor 9");

    olesnica.addLocation(54, 26, "");
    olesnica.addLocation(100, 30, "Tor 10");

    olesnica.addLocation(58, 26, "");
    olesnica.addLocation(100, 26, "Tor 11");

    olesnica.addLocation(78, 34, "");
    olesnica.addLocation(100, 38, "Tor 12");

    olesnica.addLocation(82, 34, "");
    olesnica.addLocation(100, 34, "Tor 13");

    olesnica.addLocation(38, 16, "");
    olesnica.addLocation(60, 11, "Tor 14");

    olesnica.addLocation(38, 18, "");
    olesnica.addLocation(100, 20, "Tor 15");

    olesnica.addLocation(42, 18, "");
    olesnica.addLocation(100, 18, "Tor 16");

    olesnica.addLocation(58, 11, "");
    olesnica.addLocation(100, 6, "Tor 17");

    olesnica.addLocation(62, 11, "");
    olesnica.addLocation(100, 11, "Tor 18");

    olesnica.matrixes();
    olesnica.connect_without_revers(0, 1, 3);
    olesnica.connect_without_revers(2, 3, 3);
    olesnica.connect_without_revers(4, 5, 3);
    olesnica.connect_without_revers(6, 7, 3);
    olesnica.connect_without_revers(8, 9, 3);
    olesnica.connect_without_revers(10, 11, 3);
    olesnica.connect_without_revers(12, 13, 3);
    olesnica.connect_without_revers(14, 15, 3);
    olesnica.connect_without_revers(16, 17, 3);
    olesnica.connect_without_revers(18, 19, 3);
    olesnica.connect_without_revers(20, 21, 3);
    olesnica.connect_without_revers(22, 23, 3);
    olesnica.connect_without_revers(24, 25, 3);
    olesnica.connect_without_revers(26, 27, 3);
    olesnica.connect_without_revers(28, 29, 3);
    olesnica.connect_without_revers(30, 31, 3);
    olesnica.connect_without_revers(32, 33, 3);
    olesnica.connect_without_revers(34, 35, 3);
    olesnica.create_rails();
}

void createZgorzelec(World_map &zgorzelec) {
    zgorzelec.addLocation(170, 14, "Tor 1");
    zgorzelec.addLocation(211, 14, "");

    zgorzelec.addLocation(170, 36, "Tor 2");
    zgorzelec.addLocation(211, 36, "");

    zgorzelec.addLocation(150, 10, "Tor 3");
    zgorzelec.addLocation(172, 14, "");

    zgorzelec.addLocation(130, 14, "Tor 4");
    zgorzelec.addLocation(158, 14, "");

    zgorzelec.addLocation(130, 10, "Tor 5");
    zgorzelec.addLocation(152, 10, "");

    zgorzelec.addLocation(120, 8, "Tor 6");
    zgorzelec.addLocation(132, 10, "");

    zgorzelec.addLocation(100, 8, "Tor 7");
    zgorzelec.addLocation(122, 8, "");

    zgorzelec.addLocation(100, 10, "Tor 8");
    zgorzelec.addLocation(126, 10, "");

    zgorzelec.addLocation(90, 6, "Tor 9");
    zgorzelec.addLocation(102, 8, "");

    zgorzelec.addLocation(70, 6, "Tor 10");
    zgorzelec.addLocation(92, 6, "");

    zgorzelec.addLocation(70, 8, "Tor 11");
    zgorzelec.addLocation(96, 8, "");

    zgorzelec.addLocation(60, 4, "Tor 12");
    zgorzelec.addLocation(72, 6, "");

    zgorzelec.addLocation(40, 4, "Tor 13");
    zgorzelec.addLocation(62, 4, "");

    zgorzelec.addLocation(40, 6, "Tor 14");
    zgorzelec.addLocation(66, 6, "");

    zgorzelec.addLocation(40, 8, "Tor 15");
    zgorzelec.addLocation(72, 8, "");

    zgorzelec.addLocation(40, 10, "Tor 16");
    zgorzelec.addLocation(102, 10, "");

    zgorzelec.addLocation(40, 14, "Tor 17");
    zgorzelec.addLocation(156, 14, "");

    zgorzelec.addLocation(160, 34, "Tor 18");
    zgorzelec.addLocation(172, 36, "");

    zgorzelec.addLocation(140, 34, "Tor 19");
    zgorzelec.addLocation(162, 34, "");

    zgorzelec.addLocation(40, 36, "Tor 20");
    zgorzelec.addLocation(166, 36, "");

    zgorzelec.addLocation(130, 32, "Tor 21");
    zgorzelec.addLocation(142, 34, "");

    zgorzelec.addLocation(110, 32, "Tor 22");
    zgorzelec.addLocation(132, 32, "");

    zgorzelec.addLocation(40, 34, "Tor 23");
    zgorzelec.addLocation(136, 34, "");

    zgorzelec.addLocation(100, 30, "Tor 24");
    zgorzelec.addLocation(112, 32, "");

    zgorzelec.addLocation(40, 30, "Tor 25");
    zgorzelec.addLocation(102, 30, "");

    zgorzelec.addLocation(40, 32, "Tor 26");
    zgorzelec.addLocation(106, 32, "");

    zgorzelec.matrixes();
    zgorzelec.connect_without_revers(0, 1, 3);
    zgorzelec.connect_without_revers(2, 3, 3);
    zgorzelec.connect_without_revers(4, 5, 3);
    zgorzelec.connect_without_revers(6, 7, 3);
    zgorzelec.connect_without_revers(8, 9, 3);
    zgorzelec.connect_without_revers(10, 11, 3);
    zgorzelec.connect_without_revers(12, 13, 3);
    zgorzelec.connect_without_revers(14, 15, 3);
    zgorzelec.connect_without_revers(16, 17, 3);
    zgorzelec.connect_without_revers(18, 19, 3);
    zgorzelec.connect_without_revers(20, 21, 3);
    zgorzelec.connect_without_revers(22, 23, 3);
    zgorzelec.connect_without_revers(24, 25, 3);
    zgorzelec.connect_without_revers(26, 27, 3);
    zgorzelec.connect_without_revers(28, 29, 3);
    zgorzelec.connect_without_revers(30, 31, 3);
    zgorzelec.connect_without_revers(32, 33, 3);
    zgorzelec.connect_without_revers(34, 35, 3);
    zgorzelec.connect_without_revers(36, 37, 3);
    zgorzelec.connect_without_revers(38, 39, 3);
    zgorzelec.connect_without_revers(40, 41, 3);
    zgorzelec.connect_without_revers(42, 43, 3);
    zgorzelec.connect_without_revers(44, 45, 3);
    zgorzelec.connect_without_revers(46, 47, 3);
    zgorzelec.connect_without_revers(48, 49, 3);
    zgorzelec.connect_without_revers(50, 51, 3);

    zgorzelec.create_rails();
}
