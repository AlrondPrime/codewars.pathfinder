#include "Labyrinth.hpp"

bool Labyrinth::find_path()
{
    return this->search_in_width();
}


bool Labyrinth::search_in_width()
{
    std::vector<Point *> edge{};

    auto print_edge = [&](){
            for (const auto &p: edge)
            printf("    Is x(%d), y(%d) is checked: %b\n", p->x, p->y, p->checked);
            printf("End of edge\n");
    };

    auto already_in_edge = [&](const Point *_point){
        return std::any_of(edge.begin(), edge.end(),
                           [&](const Point *p)
                           { return p->x == _point->x && p->y == _point->y; });
    };

    auto is_exit = [&](const Point *_point)
    {
        printf("Is x(%d), y(%d) is exit: %b\n", _point->x, _point->y,
               _point->x == dimension - 1 && _point->y == dimension - 1);
        return _point->x == dimension - 1 && _point->y == dimension - 1;
    };

    edge.emplace_back(&map[0][0]);

    while (true)
    {
        for (int i{}; i < edge.size(); ++i)
        {
            printf("Edge size: %d\n", edge.size());
            print_edge();
            Point *currentPoint = edge.front();
            Crawler crawler2(*this, currentPoint);

            while (++crawler2)
            {
                Point *currentDirection = crawler2.getDirection();

                if (is_exit(currentDirection))
                    return true;

                if (!currentDirection->checked && !already_in_edge(currentDirection))
                {
                    printf("Adding point x(%d), y(%d) to edge\n",
                           currentDirection->x, currentDirection->y);
                    edge.emplace_back(currentDirection);
                }
            }

            printf("Marking point x(%d), y(%d) as checked\n", currentPoint->x, currentPoint->y);
            currentPoint->checked = true;
            if(edge.front()->x != currentPoint->x && edge.front()->y != currentPoint->y)
                printf("\033[30;41mEverything is bad.\033[0m\n");
            edge.erase(edge.begin());

            print_map();
        }

        if (edge.empty())
            return false;
    }
}


void Labyrinth::read_map(const std::string& path)
{
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

    std::string buf;
    int x{0}, y{0};
    while (std::getline(file, buf))
    {
        map.emplace_back(std::vector<Point>(buf.size()));
        for (const auto &ch: buf)
        {
            map.at(y).at(x).x = x;
            map.at(y).at(x).y = y;
            map.at(y).at(x).wall = ch == 'W';
            ++x;
        }
        x = 0;
        ++y;
    }

    dimension = map.size();

    //print_map();
}


void Labyrinth::parse_map(const std::string &_map)
{
    std::stringstream ss(_map);
    std::string buf;
    int x{0}, y{0};
    while (std::getline(ss, buf))
    {
        map.emplace_back(std::vector<Point>(buf.size()));
        for (const auto &ch: buf)
        {
            map.at(y).at(x).x = x;
            map.at(y).at(x).y = y;
            map.at(y).at(x).wall = ch == 'W';
            ++x;
        }
        x = 0;
        ++y;
    }

    dimension = map.size();
}