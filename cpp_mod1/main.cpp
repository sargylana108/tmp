#include <iostream>

int main()
{
    // here we calculate fibonacci numbers
    double f1 = 0.0; // Первое число Фибоначчи
    double f2 = 1.0; // Второе число Фибоначчи
    double f3 = f1 + f2; // Третье число Фибоначчи
    double f4 = f2 + f3; // Четвёртое число Фибоначчи
    double f5 = f3 + f4; // Пятое число Фибоначчи

    // here the output of the found numbers to the console is performed
    std::cout << "Fibonacci number 1: " << f1 << std::endl;
    std::cout << "Fibonacci number 2: " << f2 << std::endl;
    std::cout << "Fibonacci number 3: " << f3 << std::endl;
    std::cout << "Fibonacci number 4: " << f4 << std::endl;
    std::cout << "Fibonacci number 5: " << f5 << std::endl;

    return 0;
}