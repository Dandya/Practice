/*
 *Напишите следующую программу. Сначала пользователю предлагается ввести 2 числа
 *типа с плавающей точкой (используйте тип double). Затем предлагается ввести 
 *один из следующих математических символов: +, -, * или /. Программа выполняет 
 *выбранную пользователем математическую операцию между двумя числами, а затем 
 *выводит результат на экран. Если пользователь ввел некорректный символ, 
 *то программа ничего не должна выводить. 
 */ 
#include <iostream>
//*********************
const double readNumber()
{
    std::cout << "Input number: ";
    double number {0};
    std::cin >> number;
    return number;
}
//*********************
const char readAction()
{
    std::cout << "Input action (+, -, *, or /): ";
    char action;
    std::cin >> action;
    return action; 
}
//*********************
int main()
{
    double firstNum {readNumber()};
    double secondNum {readNumber()};
    char action {readAction()}; 
    double result;
    switch (action)
    {
        case '+': result = firstNum + secondNum; break;
        case '-': result = firstNum - secondNum; break;
        case '*': result = firstNum * secondNum; break;
        case '/': result = firstNum / secondNum; break;
        default: std::cout << "Unknown action" << std::endl; return 1;
    }
    std::cout << result << std::endl;
    return 0;
}