#ifndef CONTROL_TRAIN_HEADER
#define CONTROL_TRAIN_HEADER

#include <thread>
#include <vector>
#include <mutex>
#include "train.hpp"

class Control_train{
    private:

    public:
    void test(std::vector<Train>& trains, World_map& map, Control_map& contr);
    void control_trains(std::vector<Train>& trains);

};

#endif