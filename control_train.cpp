#include "control_train.hpp"

void Control_train::test(std::vector<Train> &trains, World_map &map, Control_map& contr, World_map &zgorzelec, World_map &olesnica)
{
    auto cities = map.getCities();
    auto routes = map.getRoutes();
    for (int i = 0; i < cities.size(); i++) {
        for (int j = 0; j < cities.size(); j++) {
                if(routes[i][j].size()>0){
                Train train = Train(i,5,map, contr, zgorzelec, olesnica);
                // train.set_up_route(i,j);
                train.start(i);
                
                // std::cout<<routes[i][j].size()<<"  "<<i<<"->"<<j<<std::endl;
                // train.set_is_on_map(true);
                
                trains.push_back(train);
            }
        }
    }
    // Train train1 = Train(123,1,map,contr);
    // train1.set_up_route(0, 4);
                
    // // std::cout<<routes[i][j].size()<<"  "<<i<<"->"<<j<<std::endl;
    // train1.set_is_on_map(true);
                
    // trains.push_back(train1);
    // Train train2 = Train(123,5,map);
    // train2.set_up_route(4, 0);
                
    // // std::cout<<routes[i][j].size()<<"  "<<i<<"->"<<j<<std::endl;
    // train2.set_is_on_map(true);
                
    // trains.push_back(train2);
}

// void Control_train::control_trains(std::vector<Train> &trains)
// {

// }