// Code by Jacek Wieczorek

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <maze.h>
#include <point.h>
using namespace ecn;

typedef struct
{
	int x, y;	  // Node position - little waste of memory, but it allows faster generation
	void *parent; // Pointer to parent node
	char c;		  // Character to be displayed
	char dirs;	  // Directions that still haven't been explored

} Node;

Node *nodes;	   // Nodes array
int width, height; // Maze dimensions

// Maze variable
Maze *gen_maze;
double percentage;

int init()
{
	int i, j;
	Node *n;
	gen_maze = new Maze(width, height);
	percentage = 0.01;

	// Allocate memory for maze
	nodes = (Node *)calloc(width * height, sizeof(Node));
	if (nodes == NULL)
		return 1;

	// Setup crucial nodes
	for (i = 0; i < width; i++)
	{
		for (j = 0; j < height; j++)
		{
			n = nodes + i + j * width;
			if (i * j % 2)
			{
				n->x = i;
				n->y = j;
				n->dirs = 15; // Assume that all directions can be explored (4 youngest bits set)
				n->c = ' ';
			}
			else
				n->c = '#'; // Add walls between nodes
		}
	}
	return 0;
}

Node *link(Node *n)
{
	// Connects node to random neighbor (if possible) and returns
	// address of next node that should be visited

	int x, y;
	char dir;
	Node *dest;

	// Nothing can be done if null pointer is given - return
	if (n == NULL)
		return NULL;

	// While there are directions still unexplored
	while (n->dirs)
	{
		// Randomly pick one direction
		dir = (1 << (rand() % 4));

		// If it has already been explored - try again
		if (~n->dirs & dir)
			continue;

		// Mark direction as explored
		n->dirs &= ~dir;

		// Depending on chosen direction
		switch (dir)
		{
		// Check if it's possible to go right
		case 1:
			if (n->x + 2 < width)
			{
				x = n->x + 2;
				y = n->y;
			}
			else
				continue;
			break;

		// Check if it's possible to go down
		case 2:
			if (n->y + 2 < height)
			{
				x = n->x;
				y = n->y + 2;
			}
			else
				continue;
			break;

		// Check if it's possible to go left
		case 4:
			if (n->x - 2 >= 0)
			{
				x = n->x - 2;
				y = n->y;
			}
			else
				continue;
			break;

		// Check if it's possible to go up
		case 8:
			if (n->y - 2 >= 0)
			{
				x = n->x;
				y = n->y - 2;
			}
			else
				continue;
			break;
		}

		// Get destination node into pointer (makes things a tiny bit faster)
		dest = nodes + x + y * width;

		// Make sure that destination node is not a wall
		if (dest->c == ' ')
		{
			// If destination is a linked node already - abort
			if (dest->parent != NULL)
				continue;

			// Otherwise, adopt node
			dest->parent = n;

			// Remove wall between nodes
			nodes[n->x + (x - n->x) / 2 + (n->y + (y - n->y) / 2) * width].c = ' ';

			// Return address of the child node
			return dest;
		}
	}

	// If nothing more can be done here - return parent's address
	return (Node *)n->parent;
}

void draw()
{
	int i, j;

	// Outputs maze to terminal - nothing special
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			printf("%c", nodes[j + i * width].c);
			if (nodes[j + i * width].c == ' ')
				gen_maze->dig(j, i);
		}
		printf("\n");
	}

	gen_maze->save();
}

void erasepercent()
{
	int i, j, no_of_walls = 0;
	int req_walls = 0;
	Node *n;
	std::cout << "Enter the percentage of walls to be removed: " << std::endl;
	std::cin >> percentage;
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			if (nodes[j + i * width].c == '#')
				no_of_walls = no_of_walls + 1;

	req_walls = no_of_walls * percentage;
	std::cout << "Req walls" << req_walls << " No of walls" << no_of_walls << std::endl;

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
		{
			if ((double)rand() / RAND_MAX < percentage && !(i == 0) && !(j == 0) &&
				!(i == height - 1) && !(j == width - 1))
			{
				nodes[j + i * width].c = ' ';
			}
		}
}

int main(int argc, char **argv)
{
	Node *start, *last;

	// Check argument count
	if (argc < 3)
	{
		fprintf(stderr, "%s: please specify maze dimensions!\n", argv[0]);
		exit(1);
	}

	// Read maze dimensions from command line arguments
	if (sscanf(argv[1], "%d", &width) + sscanf(argv[2], "%d", &height) < 2)
	{
		fprintf(stderr, "%s: invalid maze size value!\n", argv[0]);
		exit(1);
	}

	// Allow only odd dimensions
	if (!(width % 2) || !(height % 2))
	{
		fprintf(stderr, "%s: dimensions must be odd!\n", argv[0]);
		exit(1);
	}

	// Do not allow negative dimensions
	if (width <= 0 || height <= 0)
	{
		fprintf(stderr, "%s: dimensions must be greater than 0!\n", argv[0]);
		exit(1);
	}

	// Seed random generator
	srand(time(NULL));

	// Initialize maze
	if (init())
	{
		fprintf(stderr, "%s: out of memory!\n", argv[0]);
		exit(1);
	}

	// Setup start node
	start = nodes + 1 + width;
	start->parent = start;
	last = start;

	// Connect nodes until start node is reached and can't be left
	while ((last = link(last)) !=
		   start)
		;

	erasepercent();
	draw();
	cv::waitKey(0);
}
