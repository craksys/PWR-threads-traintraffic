#ifndef RAILS_HEADER
#define RAILS_HEADER

// #include <mutex>

class Rail {
    private:
    // std::mutex mtx;
    int rail_number;
    int rail_destination;
    int turn_destination;
    int rail_start;

    bool is_mtx_locked = false;
    bool is_green_light = true;
    bool is_crossover = false;
    bool turn = false;
    
    Rail* next_track;
    Rail* turn_track;   
    Rail* previosu;
    public:
    bool go_forward();
    void start_travel();
    void stop_travel();
    void change_crossovers();
};

#endif