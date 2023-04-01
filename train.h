#ifndef UNTITLED_TRAIN_H
#define UNTITLED_TRAIN_H

#include "rails.h"

class Train{
public:
    void createOutsideTrain();

    void createOutsideTrain(railStruct *rails_array, int start_position, int speed);

    void printError(std::string error_name);

    bool isCrossover(railStruct *rails_array, int position);

    void sleepTrain(int speed) const;

    bool isGreenLight(railStruct *arr, int position);
};


#endif //UNTITLED_TRAIN_H
