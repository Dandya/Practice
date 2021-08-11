#ifndef IO_H
#define IO_H

#include <iostream>

const int readNumber()
{
    std::cout << "Input number: ";
    int number;
    std::cin >> number;
    return number;
}

void writeAnswer(int firstNum, int secondNum)
{
    std::cout << "Result:" << firstNum + secondNum << std::endl;
}

#endif