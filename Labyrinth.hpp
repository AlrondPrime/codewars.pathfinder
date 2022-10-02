//
// Created by alrond on 10/1/22.
//
#include <fstream>
#include <iostream>
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
    bool queued{false};
    char came_from{'.'};

    Point()=default;
    Point(int x, int y, bool is_wall) :
            x(x), y(y), wall(is_wall)
    {}
};

class Labyrinth
{
public:
    Labyrinth()=default;

    explicit Labyrinth(const std::string &_map)
    {
        dimension = count_dimension(_map);
        this->parse_map(_map);
    }

    bool find_path();

    void read_map(const std::string &path);

    void parse_map(const std::string &_map);

private:
    size_t dimension{};
    std::vector<std::vector<Point>> map{};

    class Crawler
    {
        int x, y;
        char direction{'.'};
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
        bool is_wall(int _x, int _y) const;
        bool is_valid(int _x, int _y) const;
    };


    int count_dimension(const std::string &_map)
    {
        return (-1 + sqrt(1 + 4 * _map.size())) / 2;
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
                else if(x.queued)
                    printf("\033[1;44m");
                if(x.came_from == '.')
                    printf(x.wall ? "W" : ".");
                else
                    switch (x.came_from)
                    {
                        case 'U':
                            printf("\u2191");
                            break;
                        case 'L':
                            printf("\u2190");
                            break;
                        case 'D':
                            printf("\u2193");
                            break;
                        case 'R':
                            printf("\u2192");
                            break;
                    }
                printf("\033[0m");
            }
            printf("\n");
        }
        printf("\n");
    }


    bool search_in_width();
};


#define PATHFINDER_1_LABYRINTH_H

#endif //PATHFINDER_1_LABYRINTH_H
