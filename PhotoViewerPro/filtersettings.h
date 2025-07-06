#ifndef FILTERSETTINGS_H
#define FILTERSETTINGS_H

#include "constants.h"


struct FilterSettings {
    int brightness = START_VALUE;
    int sepia = START_VALUE;
    int blur = START_VALUE;
    bool negative = false;
};


#endif // FILTERSETTINGS_H
