#include "constants.h"
//----------------------------------------------------------------
void printHeight(double height, double time)
{
    if (height > 0)
    {
        std::cout << "Height later " << time << " sec: " << height << std::endl;
    }
    else
    {
        std::cout << "On the ground" << std::endl;
    }
}
int main()
{
    std::cout << "Input initial height: ";
    double initialHeight {0};
    std::cin >> initialHeight;
    {
        double time {0};
        int heightNow = initialHeight;
        while (heightNow > 0)
        {
            printHeight(heightNow = physics::getHeightNow(time, initialHeight), time);
            time++;
        }
    }
    return 0;
}