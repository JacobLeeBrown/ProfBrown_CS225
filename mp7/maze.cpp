/**
 * @file maze.cpp
 * Implementation of SquareMaze class.
 */

#include "maze.h"

/*const *RGBAPixel BLACK = new RGBAPixel(0, 0, 0);
const *RGBAPixel WHITE = new RGBAPixel(255, 255, 255);
const *RGBAPixel RED = new RGBAPixel(255, 0, 0);*/

SquareMaze::SquareMaze() : _width(0), _height(0), bestX(0), cells(), walls_d(), 
	walls_r()
{
	// Save this space for a rare Pepe
}

void SquareMaze::makeMaze(int width, int height)
{
	// Set private member variables
	_width = width;		
	_height = height;
	bestX = _width - 1;


	cells.deleteElems();
	cells.addelements(_width*_height);

	// Reset private member storage vectors for the walls of the maze
	resetVectors();
	// Random removal of walls from the currently filled maze
	setWalls();
	// Targeted removal of walls to join disjoint sets
	unionStragglers();
}

int SquareMaze::canTravel(int x, int y, int dir) const
{
	// Conversion of 2D to 1D
	int index = x + (y * _width);
	switch(dir)
	{
		// 0 is move right
		case(0):
			// Check we haven't hit the right wall
			if(x + 1 == _width)
				return false;
			// Else return the opposite of whether there is a wall or not
			else
				return !walls_r[index];
			break;
		// 1 is move down
		case(1):
			// Check we haven't hit bottom wall
			if(y + 1 == _height)
				return false;
			else
				return !walls_d[index];
			break;
		// 2 is move left
		case(2):
			// Check we're not along the left wall
			if(x == 0)
				return false;
			// Else check if there is a right wall in the neighbor cell
			else
				return !walls_r[index - 1];
			break;
		// 3 is move up
		case(3):
			// Check we're not along the top wall
			if(y == 0)
				return false;
			// Else check if there is a bottom wall in the neighbor cell
			else
				return !walls_d[index - _width];
			break;
		default:
			// Oh shit, whaddup!
			return false;
	}
}

void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
	int index = x + (y * _width);
	if(dir) // bottom wall case
		walls_d[index] = exists;
	else // else if(!dir) // right wall case
		walls_r[index] = exists; 
}

vector<int> SquareMaze::solveMaze()
{
	vector<int> curBest;
	vector<int> curPath;
	// A previous direction of 2 or 3 will work for the origin
	solveMaze(0, 0, 2, curPath, curBest);
	setWall(bestX, _height-1, 1, false);
	return curBest;
}

PNG * SquareMaze::drawMaze()
{
	PNG * maze = new PNG((_width * 10) + 1, (_height * 10) + 1);
	/* Set the very top row black except for the entrance */
	for(int i = 1; i <= (_width * 10); i++)
	{
		RGBAPixel * cur = (*maze)(i, 0);
		if(i < 10)
		{
			// Do nothing, already white
		}
		else
		{
			cur->red = 0;
			cur->green = 0;
			cur->blue = 0;
		}
	}
	/* Set the very left-most wall black */
	for(int j = 0; j <= (_height * 10); j++)
	{
		RGBAPixel * cur = (*maze)(0, j);
		cur->red = 0;
		cur->green = 0;
		cur->blue = 0;
	}

	// Iterate through every cell and draw walls where appropriate
	for(int yi = 0; yi < _height; yi++)
	{
		for(int xi = 0; xi < _width; xi++)
		{
			// Convert from 2D to 1D
			int index = xi + (yi * _width);
			if(walls_r[index])
			{
				for(int k = 0; k <= 10; k++)
				{
					RGBAPixel * cur = (*maze)((xi + 1) * 10, (yi * 10) + k);
					cur->red = 0;
					cur->green = 0;
					cur->blue = 0;
				}
			}
			if(walls_d[index])
			{
				for(int k = 0; k <= 10; k++)
				{
					RGBAPixel * cur = (*maze)((xi * 10) + k, (yi + 1) * 10);
					cur->red = 0;
					cur->green = 0;
					cur->blue = 0;
				}
			}
		}
	}
	return maze;
}

PNG * SquareMaze::drawMazeWithSolution()
{
	PNG * maze = drawMaze();
	vector<int> soln = solveMaze();

	/* Take care of very first pixel of the solution trail */
	int curX = 5;
	int curY = 5;
	RGBAPixel * cur = (*maze)(curX, curY);
	cur->red = 255;
	cur->green = 0;
	cur->blue = 0;

	// Iterate over all of the solution's directions
	for(int i = 0; i < (int)soln.size(); i++)
	{
		// Will control how to increment the current coordinates
		int incX = 0;
		int incY = 0;
		// Set increments based on direction we're going
		switch(soln[i])
		{
			case(0):
				incX = 1;
				break;
			case(1):
				incY = 1;
				break;
			case(2):
				incX = -1;
				break;
			case(3):
				incY = -1;
				break;
			default:
				; // Jet fuel can't melt steal beams
		}
		// Draw the solution line in the proper direction
		for(int j = 0; j < 10; j++)
		{
			curX += incX;
			curY += incY;
			RGBAPixel * cur = (*maze)(curX, curY);
			cur->red = 255;
			cur->green = 0;
			cur->blue = 0;
		}
	}
	// Finally, open up the exit
	for(int k = 1; k < 10; k++)
	{
		RGBAPixel * cur = (*maze)((bestX * 10) + k, _height * 10);
		cur->red = 255;
		cur->green = 255;
		cur->blue = 255;
	}

	return maze;
}

void SquareMaze::setWalls()
{
	/* Initalize random seed */
	srand(time(NULL));

	// For every cell in the maze
	for(int yi = 0; yi < _height; yi++)
	{
		for(int xi = 0; xi < _width; xi++)
		{
			int choice = rand() % 5;
			int idx = (xi + yi * _width);
			switch(choice)
			{
				case(0):
					// Not removing any walls, so do nothing
					break;
				case(1):
					/* Remove bottom wall, if possible */
					// setWall(x, y, 1, true)
					if(wallCheck(xi, yi, 1))
					{
						cells.setunion(idx, idx + _width);
						setWall(xi, yi, 1, false);
					}
					break;
				case(2):
					/* Remove right wall, if possible */
					// setWall(x, y, 0, true)
					if(wallCheck(xi, yi, 0))
					{
						cells.setunion(idx, idx + 1);
						setWall(xi, yi, 0, false);
					}
					break;
				case(3):
					/* Remove bottom and right walls, if possible */
					if(wallCheck(xi, yi, 1))
					{
						cells.setunion(idx, idx + _width);
						setWall(xi, yi, 1, false);
					}
					if(wallCheck(xi, yi, 0))
					{
						cells.setunion(idx, idx + 1);
						setWall(xi, yi, 0, false);
					}
					break;
				case(4):
					/* Remove right and bottom walls, if possible */
					// Order matters, so this just helps the randomness
					if(wallCheck(xi, yi, 0))
					{
						cells.setunion(idx, idx + 1);
						setWall(xi, yi, 0, false);
					}
					if(wallCheck(xi, yi, 1))
					{
						cells.setunion(idx, idx + _width);
						setWall(xi, yi, 1, false);
					}
					break;
				default:
					// Uhhhh... Trolly problem?
					break;
			}
		}
	}
}

bool SquareMaze::wallCheck(int x, int y, int dir)
{
	if(dir) // check bottom wall
	{
		// Can't remove bottom wall if along bottom row
		if(y == (_height - 1))
			return false;
		int idx = (x + y * _width);
		// Can't remove wall if it creates a cycle
		if(cells.find(idx) == cells.find(idx + _width))
			return false;
		// Else it's perfectly okay to remove the wall
		return true;
	}
	else // else if(!dir) // check right wall
	{
		// Can't remove right wall if along right column
		if(x == (_width - 1))
			return false;
		int idx = (x + y * _width);
		// Can't remove wall if it creates a cycle
		if(cells.find(idx) == cells.find(idx + 1))
			return false;
		// Else it's perfectly okay to remove the wall
		return true;
	}
}

void SquareMaze::unionStragglers()
{
	// For every cell in the maze
	for(int yi = 0; yi < _height; yi++)
	{
		for(int xi = 0; xi < _width; xi++)
		{
			int idx = (xi + yi * _width);
			// If we can still remove walls (cells are not connected via some
			// path yet), then we have at least 2 disjoint sets and need to fix
			if(wallCheck(xi, yi, 1))
			{
				cells.setunion(idx, idx + _width);
				setWall(xi, yi, 1, false);
			}
			if(wallCheck(xi, yi, 0))
			{
				cells.setunion(idx, idx + 1);
				setWall(xi, yi, 0, false);
			}
		}
	}
}

void SquareMaze::resetVectors()
{
	int size_d = walls_d.size();
	// int size_r = walls_r.size(); // Vectors should be the same size
	// Erase whatever is in the vectors now
	for(int i = 0; i < size_d; i ++)
	{
		walls_d.pop_back();
		// Should be same size
		walls_r.pop_back();
	}
	// Re-instantiate with all values being true
	for(int i = 0; i < _width*_height; i++)
	{
		walls_d.push_back(true);
		walls_r.push_back(true);
	}
}

void SquareMaze::solveMaze(int x, int y, int dir, vector<int> & curPath,
						   vector<int> & curBest)
{
	// Check if we are along the bottom so we can see if we need to update the
	// best path for solving the maze
	int max_height = _height - 1;
	if(y ==  max_height)
	{
		// If the current path is longer than the best, it beats the best
		if(curPath.size() > curBest.size())
		{
			curBest = curPath;
			bestX = x;
		}
		// If they're equal in length, break tie with lower x coordinate
		else if(curPath.size() == curBest.size())
		{
			if(x < bestX)
			{
				curBest = curPath;
				bestX = x;
			}
		}
		// else
			// Do nothing because current path is too small #skinnyShaming
	}

	/* Check each direction for if we can move that way */
	if(canTravel(x, y, 0) && (0 != dir)) // Rightward
	{
		/* Push direction we're going onto current path */
		curPath.push_back(0);
		/* Recursively call that cell with the direction we're coming from */
		solveMaze(x + 1, y, 2, curPath, curBest);
		/* When return from the call, pop the direction off the path */
		curPath.pop_back();
	}
	if(canTravel(x, y, 1) && (1 != dir)) // Downward
	{
		curPath.push_back(1);
		solveMaze(x, y + 1, 3, curPath, curBest);
		curPath.pop_back();
	}
	if(canTravel(x, y, 2) && (2 != dir)) // Leftward
	{
		curPath.push_back(2);
		solveMaze(x - 1, y, 0, curPath, curBest);
		curPath.pop_back();
	}
	if(canTravel(x, y, 3) && (3 != dir)) // Upward
	{
		curPath.push_back(3);
		solveMaze(x, y - 1, 1, curPath, curBest);
		curPath.pop_back();
	}

	// Else we cannot move in any direction, so we just recurse back
}