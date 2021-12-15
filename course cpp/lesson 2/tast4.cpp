/*
 *Напишите небольшую программу-симулятор падения мячика с башни. Сначала 
 *пользователю предлагается ввести высоту башни в метрах. Не забывайте о 
 *гравитации (9,8м/с2) и о том, что у мячика нет начальной скорости (его держат 
 *в руках). Программа должна выводить расстояние от земли, на котором находится 
 *мячик после 0, 1, 2, 3, 4 и 5 секунд падения. Минимальная высота составляет 0 
 *метров (ниже мячику падать нельзя).
 *В вашей программе должен быть заголовочный файл constants.h с пространством 
 *имен myConstants. В myConstants определите символьную константу для хранения 
 *значения силы тяжести на Земле (9.8).
 */
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
    for (double time {0}; time <= 5; time++)
    {
        printHeight(physics::getHeightNow(time, initialHeight), time);
    }
    return 0;
}