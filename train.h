#ifndef UNTITLED_TRAIN_H
#define UNTITLED_TRAIN_H

#include "rails.h"

class Train {
public:
    void createOutsideTrain(railStruct *rails_array, int start_position, int speed);

    bool isCrossover(railStruct *rails_array, int position);

private:
    void sleepTrain(int speed) const;

    bool isGreenLight(railStruct *arr, int position);

    void printError(std::string error_name);
};

#endif //UNTITLED_TRAIN_H
