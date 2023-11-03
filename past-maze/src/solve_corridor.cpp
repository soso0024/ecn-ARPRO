#include <a_star.h>
#include <maze.h>

using namespace std;
using namespace ecn;

// a node is a x-y position, we move from 1 each time
class Position : public Point
{
    typedef std::unique_ptr<Position> PositionPtr;

protected:
    int distance;
    int start_x = maze.start().x;
    int start_y = maze.start().y;
    int goal_y = maze.end().y;
    int goal_x = maze.end().x;

public:
    // constructor from coordinates
    Position(int ax, int by, int _distance)
    {
        x = ax;
        y = by;
        distance = _distance;
    }

    // constructor from base ecn::Point
    Position(ecn::Point p) : Point(p.x, p.y) {}

    int distToParent()
    {
        // in cell-based motion, the distance to the parent is always 1
        return distance;
    }
    bool is_corridor(int ax, int by, int &i, int &j)
    {
        // Dirrections:
        //  x-positive : i=1,j=0
        //  x-negative : i=-1,j=0
        //  y-positive : i=0; j=1
        //  y-negative : i=0; j=-1

        // Moving in x_direction check for corridor
        if (i && maze.isFree(ax + i, by) + maze.isFree(ax, by + 1) + maze.isFree(ax, by - 1) == 1)
        {
            // If top cell is free change direction to top
            if (maze.isFree(ax, by - 1))
            {
                i = 0;
                j = -1;
            }
            // If bottom cell is free change direction to bottom
            else if (maze.isFree(ax, by + 1))
            {
                i = 0;
                j = 1;
            }
            return true;
        }
        // Moving in y-axis direction check for corridor
        else if (j && maze.isFree(ax, by + j) + maze.isFree(ax + 1, by) + maze.isFree(ax - 1, by) == 1)
        {
            // Change direction to left if left cell is free
            if (maze.isFree(ax - 1, by))
            {
                i = -1;
                j = 0;
            }
            // Change direction to right if right cell is free
            else if (maze.isFree(ax + 1, by))
            {
                i = 1;
                j = 0;
            }
            return true;
        }
        return false;
    }

    std::vector<PositionPtr> children()
    {
        // this method should return  all positions reachable from this one
        std::vector<PositionPtr> generated;
        // Define heuristic function

        // Dirrections:
        //  x-positive : i=1,j=0
        //  x-negative : i=-1,j=0
        //  y-positive : i=0; j=1
        //  y-negative : i=0; j=-1

        // Left direction
        if (maze.isFree(x - 1, y))
        {
            int i = -1, j = 0, dist_steps = 1;
            int current_x = x + i;
            int current_y = y + j;
            while (is_corridor(current_x, current_y, i, j) && (current_x != goal_x || current_y != goal_y))
            {
                current_x += i;
                current_y += j;
                dist_steps++;
            }
            generated.push_back(std::make_unique<Position>(current_x, current_y, dist_steps));
        }
        // right
        if (maze.isFree(x + 1, y))
        {
            int i = 1, j = 0, dist_steps = 1;
            int current_x = x + i;
            int current_y = y + j;
            while (is_corridor(current_x, current_y, i, j) && (current_x != goal_x || current_y != goal_y))
            {
                current_x += i;
                current_y += j;
                dist_steps++;
            }
            generated.push_back(std::make_unique<Position>(current_x, current_y, dist_steps));
        }
        // top
        if (maze.isFree(x, y - 1))
        {
            int i = 0, j = -1, dist_steps = 1;
            int current_x = x + i;
            int current_y = y + j;
            while (is_corridor(current_x, current_y, i, j) && (current_x != goal_x || current_y != goal_y))
            {
                current_x += i;
                current_y += j;
                dist_steps++;
            }
            generated.push_back(std::make_unique<Position>(current_x, current_y, dist_steps));
        }
        // down
        if (maze.isFree(x, y + 1))
        {
            int i = 0, j = 1, dist_steps = 1;
            int current_x = x + i;
            int current_y = y + j;
            while (is_corridor(current_x, current_y, i, j) && (current_x != goal_x || current_y != goal_y))
            {
                current_x += i;
                current_y += j;
                dist_steps++;
            }
            generated.push_back(std::make_unique<Position>(current_x, current_y, dist_steps));
        }
        return generated;
    }

    void print(const Point &parent)
    {
        if (parent.x || parent.y)
        {
            std::vector<std::pair<int, int>> path;
            for (const auto &direction : std::vector<std::pair<int, int>>{{-1, 0}, {1, 0}, {0, -1}, {0, 1}})
            {
                path.clear();
                int i = direction.first;
                int j = direction.second;
                int current_x = x + i, current_y = y + j;
                int dist_parent = 0;

                if (maze.isFree(current_x, current_y))
                {
                    path.push_back({current_x, current_y});
                    dist_parent = 1;
                    while (is_corridor(current_x, current_y, i, j) && (current_x != start_x || current_y != start_y))
                    {
                        current_x += i;
                        current_y += j;
                        dist_parent++;
                        path.push_back({current_x, current_y});
                    }

                    if (current_x == parent.x && current_y == parent.y)
                    {
                        for (auto p = path.rbegin(); p != path.rend(); p++)
                            maze.passThrough(p->first, p->second);
                        break;
                    }
                }
            }
        }
        maze.passThrough(x, y);
    }
    void show(bool closed, const Point &parent)
    {
        const int b = closed ? 255 : 0, r = closed ? 0 : 255;
        if (parent.x || parent.y)
        {
            std::vector<std::pair<int, int>> path;
            for (const auto &direction : vector<Pair>({{-1, 0}, {1, 0}, {0, -1}, {0, 1}}))
            {
                path.clear();
                int i = direction.first;
                int j = direction.second;
                int current_x = x + i, current_y = y + j;
                int dist_parent = 0;

                if (maze.isFree(current_x, current_y))
                {
                    path.push_back({current_x, current_y});
                    dist_parent = 1;
                    while (is_corridor(current_x, current_y, i, j) && (current_x != start_x || current_y != start_y))
                    {
                        current_x += i;
                        current_y += j;
                        dist_parent++;
                        path.push_back({current_x, current_y});
                    }

                    if (current_x == parent.x && current_y == parent.y)
                    {
                        for (const auto &p : path)
                            maze.write(p.first, p.second, r, 0, b, false);
                        break;
                    }
                }
            }
        }
        maze.write(x, y, r, 0, b);
    }
};

typedef std::pair<int, int> Pair;

int main(int argc, char **argv)
{
    // load file
    std::string filename = "maze_corridor.png";
    if (argc == 2)
        filename = std::string(argv[1]);

    // let Point know about this maze
    Position::maze.load(filename);

    // initial and goal positions as Position's
    Position start = Position::maze.start(),
             goal = Position::maze.end();

    // call A* algorithm
    ecn::Astar(start, goal);

    // save final image
    Position::maze.saveSolution("corridor");
    cv::waitKey(0);
}
