//
// Created by alrond on 9/4/22.
//

#ifndef PATHFINDER_1_PATHFINDER_H
#define PATHFINDER_1_PATHFINDER_H

#include <fstream>
#include <string>
#include <queue>
#include <algorithm>
#include <unistd.h>
#include <sstream>

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

    /*class Crawler
    {
        int x, y;
        int dimension{};
        int counter{};
        Point& p;

    public:
        Crawler(Point& p, const int dimension):
                x(p.x), y(p.y), p(p), dimension(dimension)
        {}

        int getX() const
        {
            return x;
        }

        int getY() const
        {
            return y;
        }

        bool is_checked() const
        {
            switch (counter)
            {
                case 1:
                    p.D = false;
                    return p.D;

                case 2:
                    p.R = false;
                    return p.R;

                case 3:
                    p.U = false;
                    return p.U;

                case 4:
                    p.L = false;
                    return p.L;
            }
        }

        bool is_valid() const
        {
            return y < dimension && x < dimension &&
                   y >= 0 && x >= 0;
        }

        bool operator++()
        {
            switch (counter)
            {
                case 0:
                    ++y;
                    ++counter;
                    return true;
                case 1:
                    ++x;
                    --y;
                    ++counter;
                    return true;
                case 2:
                    --x;
                    --y;
                    ++counter;
                    return true;
                case 3:
                    --x;
                    ++y;
                    ++counter;
                    return false;
            }
        }
    };*/

    int dimension{};
    std::vector<Point> q;
    std::vector<std::string> map;


public:
    Pathfinder()= default;

    explicit Pathfinder(const std::string& map)
    {
        std::string buf;
        std::stringstream ss(map);
        while (std::getline(ss, buf))
        {
            this->map.push_back(buf);
        }
        dimension = this->map.size();
    }

    void read_map(std::string_view path)
    {
        std::string buf;
        std::ifstream file;
        file.open(path.data(), std::ios_base::in);
        if (!file.is_open())
        {
            perror("open failure");
            char dir[256];
            getcwd(dir, sizeof(dir));
            printf("pwd: %s\n", dir);
            return;
        }
        while (std::getline(file, buf))
        {
            map.push_back(buf);
        }

        dimension = map.size();
    }

    bool find_path()
    {
        q.emplace_back(0, 0);

        while (true)
        {
            Point &currentPoint = q.back();

            if (is_exit(currentPoint))
                return true;

            /*Crawler crawler(currentPoint, dimension);
            while(++crawler)
            {
                if(!crawler.is_checked() && crawler.is_valid() &&
                !is_wall(Point(crawler.getX(), crawler.getY())))
                {
                    q.emplace_back(crawler.getX(), crawler.getY());
                    break;
                }
            }*/

            if (currentPoint.D && currentPoint.y + 1 < dimension &&
                !already_queued(Point(currentPoint.x, currentPoint.y + 1)) &&
                !is_wall(Point(currentPoint.x, currentPoint.y + 1)))
            {
                q.emplace_back(currentPoint.x, currentPoint.y + 1);
                currentPoint.D = false;
                continue;
            }

            if (currentPoint.R && currentPoint.x + 1 < dimension &&
                !already_queued(Point(currentPoint.x + 1, currentPoint.y)) &&
                !is_wall(Point(currentPoint.x + 1, currentPoint.y)))
            {
                q.emplace_back(currentPoint.x + 1, currentPoint.y);
                currentPoint.R = false;
                continue;
            }

            if (currentPoint.U && currentPoint.y - 1 >= 0 &&
                !already_queued(Point(currentPoint.x, currentPoint.y - 1)) &&
                !is_wall(Point(currentPoint.x, currentPoint.y - 1)))
            {
                q.emplace_back(currentPoint.x, currentPoint.y - 1);
                currentPoint.U = false;
                continue;
            }

            if (currentPoint.L && currentPoint.x - 1 >= 0 &&
                !already_queued(Point(currentPoint.x - 1, currentPoint.y)) &&
                !is_wall(Point(currentPoint.x - 1, currentPoint.y)))
            {
                q.emplace_back(currentPoint.x - 1, currentPoint.y);
                currentPoint.L = false;
                continue;
            }

            q.pop_back();
            print_path();

            if (q.empty())
                return false;
        }
    }

private:
    void print_path() const
    {
        printf("Current path: \n");
        for(const auto &p : q)
            printf("x:%d, y:%d\n", p.x, p.y);
        printf("\n");
    }

    bool already_queued(const Point &point) const
    {
        return std::any_of(q.begin(), q.end(),
                    [&](Point p)
                    { return p.x == point.x && p.y == point.y; });
    }

    bool is_exit(const Point &point) const
    {
        return point.x == dimension - 1 && point.y == dimension - 1;
    }

    bool is_wall(const Point &point) const
    {
        printf("Is x:%d y:%d a wall: %s\n", point.x, point.y,
               (map.at(point.y).at(point.x) == 'W')? "true" : "false");

        return map.at(point.y).at(point.x) == 'W';
    }


};




#endif //PATHFINDER_1_PATHFINDER_H
