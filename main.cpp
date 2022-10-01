#include <iostream>

#include "Labyrinth.hpp"



int main()
{
    Labyrinth lb;

    lb.read_map("../map");
    if(lb.find_path())
        std::cout << "Escape is reachable";
    else
        std::cout << "Escape is NOT reachable";
    return 0;
}
