#include <iostream>

#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace physics
{
    double g {9.8};
    double getHeightNow(double sec, double initialHeight)
    {
        return initialHeight - g*sec*sec/2; 
    }
}

#endif