//
// Created by alrond on 10/1/22.
//
#include <fstream>
#include <array>
#include <string>
#include <algorithm>
#include <unistd.h>
#include <valarray>
#include <vector>
#include <sstream>


#ifndef PATHFINDER_1_LABYRINTH_H
struct Point
{
    int x, y;
    bool wall;
    bool checked{false};

    Point()=default;
    Point(int x, int y, bool is_wall) :
            x(x), y(y), wall(is_wall)
    {}
};

class Labyrinth
{
public:
    Labyrinth()=default;

    Labyrinth(const std::string &_map)
    {
        dimension = count_dimension(_map);
        this->parse_map(_map);
    }

    bool find_path();

    void read_map(const std::string &path);

    void parse_map(const std::string &_map);

private:
    int dimension;
    std::vector<std::vector<Point>> map{};

    class Crawler
    {
        int x, y;
        int counter{};
        Point *point;
        Labyrinth & parent;

    public:
        Crawler(Labyrinth & _parent, Point *p) :
                parent(_parent), point(p), x(p->x), y(p->y)
        {}

        Point *getDirection() const
        {
            return point;
        }

        bool operator++();
        bool is_wall(const int _x, const int _y);
        bool is_valid(const int _x, const int _y);
    };


    int count_dimension(const std::string &map)
    {
        return (-1 + sqrt(1 + 4 * map.size())) / 2;
    }

    void print_map()
    {
        printf(" ");
        for(int i{}; i < map.size(); ++i)
            printf("%d", i);

        printf("\n");
        int j{0};
        for (const auto &y: map)
        {
            printf("%d",j++);
            for (const auto &x: y)
            {
                if(x.checked)
                    printf("\033[43m");
                //printf("\033[31m");
                printf(x.wall ? "W" : ".");
                printf("\033[0m");
            }
            printf("\n");
        }
        printf("\n");
        //getchar();
    }


    bool search_in_width();
};


#define PATHFINDER_1_LABYRINTH_H

#endif //PATHFINDER_1_LABYRINTH_H
