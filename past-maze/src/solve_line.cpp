#include <a_star.h>
#include <maze.h>

using namespace std;
using namespace ecn;

// a node is a x-y position, we move from 1 each time
class Position : public Point
{
    typedef std::unique_ptr<Position> PositionPtr;

public:
    int distance;
    // constructor from coordinates
    Position(int _x, int _y, int _distance)
    {
        x = _x;
        y = _y;
        distance = _distance;
    }

    // constructor from base ecn::Point
    Position(ecn::Point p) : Point(p.x, p.y) {}

    int distToParent()
    {
        // in cell-based motion, the distance to the parent is always 1
        return distance;
    }
    bool is_Line(int ax, int by)
    {
        // Corners,Intersections and Dead end
        if ((maze.isFree(ax + 1, by) && maze.isFree(ax - 1, by)) &&
            (!maze.isFree(ax, by + 1) && !maze.isFree(ax, by - 1)))
            return false;
        else if ((!maze.isFree(ax + 1, by) && !maze.isFree(ax - 1, by)) &&
                 (maze.isFree(ax, by + 1) && maze.isFree(ax, by - 1)))
            return false;
        else
            return true;
    }
    std::vector<PositionPtr> children()
    {
        // this method should return  all positions reachable from this one
        std::vector<PositionPtr> generated;
        // Define heuristic function
        // right
        if (maze.isFree(x + 1, y))
        {
            int i = 1;
            while (!is_Line(x + i, y))
                i++;
            generated.push_back(std::make_unique<Position>(x + i, y, i));
        }
        // left
        if (maze.isFree(x - 1, y))
        {
            int i = 1;
            while (!is_Line(x - i, y))
                i++;
            generated.push_back(std::make_unique<Position>(x - i, y, i));
        }
        // top
        if (maze.isFree(x, y + 1))
        {
            int j = 1;
            while (!is_Line(x, y + j))
                j++;
            generated.push_back(std::make_unique<Position>(x, y + j, j));
        }
        // down
        if (maze.isFree(x, y - 1))
        {
            int j = 1;
            while (!is_Line(x, y - j))
                j++;
            generated.push_back(std::make_unique<Position>(x, y - j, j));
        }
        return generated;
    }
};

int main(int argc, char **argv)
{
    // load file
    std::string filename = "maze_line.png";
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
    Position::maze.saveSolution("line");
    cv::waitKey(0);
}
