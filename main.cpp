#include "alloc.hpp"


int main()
{
    std::cout << "Standart Map:" << std::endl;
    StandartExample test1{10};
    test1.printmap();

    std::cout << "My alloc Map:" << std::endl;
    MyExample test2{10};
    test2.printmap();

    std::cout << "My container:" << std::endl;
    MyContainer test3;
    for (auto i = 0; i < 10; i++)
    {
        test3.push_back(i);
    }
    test3.printall();
}