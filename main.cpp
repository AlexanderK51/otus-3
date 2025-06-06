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

    std::cout << "My container alloc:" << std::endl;
    
    //MyContainerZ test4{10};
    // for (auto i = 0; i < 10; i++)
    // {
    //     test4.push_back2(i);
    // }
    // test4.printall();
    // test4.clear();

    // std::cout << "My container alloc+My alloc:" << std::endl;


    newcont::MyContainer<int> test5;

    for (auto i = 0; i < 10; i++)
    {
        test5.push_back(i);
    }
    test5.printall();
}