#ifndef RAILS_H
#define RAILS_H

#include <mutex>

struct railStruct {
    std::mutex mtx;
    bool is_mtx_locked;
    bool is_green_light;
    bool is_direction_left;
    bool is_crossover;
    int prev_id;
    int next_right_id;
    int next_left_id;
};

class Rails {
public:
    railStruct *createStraightSection(railStruct *arr, int start_id, int end_id);

    railStruct *createRailStructArray(int size);
};

#endif //RAILS_H

