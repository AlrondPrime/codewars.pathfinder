//
// Created by alrond on 9/4/22.
//

#ifndef PATHFINDER_1_PATHFINDER_H
#define PATHFINDER_1_PATHFINDER_H

#include <fstream>
#include <string>
#include <queue>
#include <algorithm>

class Pathfinder
{
    struct Point
    {
        int x, y;
        bool D{true}, R{true}, U{true}, L{true};// true means the way is not checked

        Point(int x, int y) :
                x(x), y(y)
        {}
    };

    size_t dimension{};
    std::vector<Point> q;
    std::vector<std::string> map;


public:
    void read_map(std::string_view path)
    {
        std::string buf;
        std::ifstream file;
        file.open(path.data());
        while (std::getline(file, buf))
        {
            map.push_back(buf);
        }

        dimension = map.size();
    }

    bool already_queued(const Point &point)
    {
        std::any_of(q.begin(), q.end(),
                    [&](Point p)
                    { return p.x == point.x || p.y == point.y; });

    }

    bool is_exit(const Point &point) const
    {
        return point.x == dimension - 1 && point.y == dimension - 1;
    }

    bool is_wall(const Point &point) const
    {
        return map.at(point.y).at(point.x) == 'W';
    }

    bool find_path()
    {
        q.emplace_back(0, 0);

        while (true)
        {

            Point currentPoint = q.back();

            if(is_exit(currentPoint))
                return true;

            if (currentPoint.D && currentPoint.y + 1 <= dimension && !already_queued(currentPoint))
            {
                q.emplace_back(currentPoint.x, currentPoint.y + 1);
                currentPoint.D = false;
                continue;
            }

            if (currentPoint.R && currentPoint.x + 1 <= dimension && !already_queued(currentPoint))
            {
                q.emplace_back(currentPoint.x + 1, currentPoint.y);
                currentPoint.R = false;
                continue;
            }

            if (currentPoint.U && currentPoint.y - 1 >= 0 && !already_queued(currentPoint))
            {
                q.emplace_back(currentPoint.x, currentPoint.y - 1);
                currentPoint.U = false;
                continue;
            }

            if (currentPoint.L && currentPoint.x - 1 >= 0 && !already_queued(currentPoint))
            {
                q.emplace_back(currentPoint.x - 1, currentPoint.y);
                currentPoint.L = false;
                continue;
            }

            q.pop_back();
            if(q.empty())
                return false;
        }
    }

};


#endif //PATHFINDER_1_PATHFINDER_H
