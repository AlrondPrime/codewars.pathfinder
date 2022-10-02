//
// Created by alrond on 10/1/22.
//
#include "Labyrinth.hpp"

bool Labyrinth::Crawler::operator++()
{
    do
    {
        switch (counter++)
        {
            case 0:
                ++y;
                direction='D';
                break;
            case 1:
                ++x;
                --y;
                direction='R';
                break;
            case 2:
                --x;
                --y;
                direction='U';
                break;
            case 3:
                --x;
                ++y;
                direction='L';
                break;
            default:
                return false;
        }
    } while (!Crawler::is_valid(x, y) || Crawler::is_wall(x, y));

    point = &parent.map[y][x];
    if(!point->checked)
        point->came_from = direction;

    return true;
}

bool Labyrinth::Crawler::is_wall(const int _x, const int _y) const
{
    printf("Is x(%d), y(%d) a wall: %d\n", _x, _y,
           parent.map.at(_y).at(_x).wall);

    return parent.map.at(_y).at(_x).wall;
}

bool Labyrinth::Crawler::is_valid(const int _x, const int _y) const
{
    printf("Is x(%d), y(%d) is valid: %d\n", _x, _y,
           _x >= 0 && _y >= 0 && _x < parent.dimension && _y < parent.dimension);
    return _x >= 0 && _y >= 0 && _x < parent.dimension && _y < parent.dimension;
}