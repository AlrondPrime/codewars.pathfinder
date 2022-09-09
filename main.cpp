#include <iostream>
#include "Pathfinder.h"

int main()
{
    Pathfinder pth;
    pth.read_map("../map");

    if(pth.find_path())
        std::cout << "Escape is reachable";
    else
        std::cout << "Escape is NOT reachable";

    return 0;
}
