/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace. Heavily based on
 * old MP4 by CS225 Staff, Fall 2010.
 *
 * @author Chase Geigle
 * @date Fall 2012
 */
#include "filler.h"
#include <vector>
using std::vector;

animation filler::dfs::fillSolid(PNG& img, int x, int y, RGBAPixel fillColor,
								int tolerance, int frameFreq)
{
	solidColorPicker solid(fillColor);	//Create a solid color
	//Pass all the work to the helper function
	return filler::fill<Stack>(img, x, y, solid, tolerance, frameFreq);
}

animation filler::dfs::fillGrid(PNG& img, int x, int y, RGBAPixel gridColor,
								int gridSpacing, int tolerance, int frameFreq)
{
	gridColorPicker grid(gridColor, gridSpacing);
	//Pass all the work to the helper function
	return filler::fill<Stack>(img, x, y, grid, tolerance, frameFreq);
}

animation filler::dfs::fillGradient(PNG& img, int x, int y,
								RGBAPixel fadeColor1, RGBAPixel fadeColor2,
								int radius, int tolerance, int frameFreq)
{
	gradientColorPicker gradient(fadeColor1, fadeColor2, radius, x, y);
	//Pass all the work to the helper function
	return filler::fill<Stack>(img, x, y, gradient, tolerance, frameFreq);	
}

animation filler::dfs::fill(PNG& img, int x, int y, colorPicker& fillColor,
							int tolerance, int frameFreq)
{
	//If I understand correctly, just pass everything sent in to the helper function
	return filler::fill<Stack>(img, x, y, fillColor, tolerance, frameFreq);
}

animation filler::bfs::fillSolid(PNG& img, int x, int y, RGBAPixel fillColor,
								int tolerance, int frameFreq)
{
	solidColorPicker solid(fillColor);
	//Pass all the work to the helper function. Same as DFS but uses a 
	// Queue instead of a Stack
	return filler::fill<Queue>(img, x, y, solid, tolerance, frameFreq);
}

animation filler::bfs::fillGrid(PNG& img, int x, int y, RGBAPixel gridColor,
                                int gridSpacing, int tolerance, int frameFreq)
{
	gridColorPicker grid(gridColor, gridSpacing);
	//Pass all the work to the helper function
	return filler::fill<Queue>(img, x, y, grid, tolerance, frameFreq);
}

animation filler::bfs::fillGradient(PNG& img, int x, int y,
									RGBAPixel fadeColor1, RGBAPixel fadeColor2,
									int radius, int tolerance, int frameFreq)
{
	gradientColorPicker gradient(fadeColor1, fadeColor2, radius, x, y);
	//Pass all the work to the helper function
	return filler::fill<Queue>(img, x, y, gradient, tolerance, frameFreq);
}

animation filler::bfs::fill(PNG& img, int x, int y, colorPicker& fillColor,
							int tolerance, int frameFreq)
{
	//Same as DFS but uses a Queue instead of a Stack
	return filler::fill<Queue>(img, x, y, fillColor, tolerance, frameFreq);
}

template <template <class T> class OrderingStructure>
animation filler::fill(PNG& img, int x, int y, colorPicker& fillColor,
						int tolerance, int frameFreq)
{	
	// The ordering stucture that will hold the elements as they are processed
	OrderingStructure<RGBAPixel*> dickPix;
	// The same ordering structures that keep track of x and y coords of corresponding points
	OrderingStructure<int> dickPixX;
	OrderingStructure<int> dickPixY;
	// The animation that will show the algorithm
	animation anim;

	// The 2D bool array (implemented with vectors) that will keep track of which pixels are processed
	// Initialize every entry to false since we've yet to check any pixels
	int height = img.height();
	int width = img.width();
	vector<bool> rows(width, false);
	vector<vector<bool>> processed(height, rows);

	// Add the first point and its coordinates to the OrderingStructures
	dickPix.add(img(x, y));
	dickPixX.add(x);
	dickPixY.add(y);
	// Save the RGB values of the first point for tolerance reference
	int fRed = img(x, y)->red;
	int fGreen = img(x, y)->green;
	int fBlue = img(x, y)->blue;

	// Counter for how many pixels have been filled
	int filledPix = 0;
	while(!(dickPix.isEmpty()))
	{
		// obtain current pixel and coordinates
		RGBAPixel* cur = dickPix.remove();
		int curX = dickPixX.remove();
		int curY = dickPixY.remove();

		int euclidian = (int)pow((cur->red - fRed), 2) +
						(int)pow((cur->green - fGreen), 2) +
						(int)pow((cur->blue - fBlue), 2);

		if(euclidian <= tolerance && !processed[curY][curX])
		{
			img(curX, curY)->red = fillColor(curX, curY).red;
			img(curX, curY)->green = fillColor(curX, curY).green;
			img(curX, curY)->blue = fillColor(curX, curY).blue;

			filledPix++;
			if(filledPix == frameFreq)
			{
				anim.addFrame(img);
				filledPix = 0;
			}

			// add the right neighbor and its respective coordinates if valid
			if(curX+1 < width)
			{
				dickPix.add(img(curX+1, curY));
				dickPixX.add(curX+1);
				dickPixY.add(curY);
			}
			// add the down neighbor and its respective coordinates if valid
			if(curY+1 < height)
			{
				dickPix.add(img(curX, curY+1));
				dickPixX.add(curX);
				dickPixY.add(curY+1);
			}
			// add the left neighbor and its respective coordinates if valid
			if(curX-1 >= 0)
			{
				dickPix.add(img(curX-1, curY));
				dickPixX.add(curX-1);
				dickPixY.add(curY);
			}
			// add the up neighbor and its respective coordinates if valid
			if(curY-1 >= 0)
			{
				dickPix.add(img(curX, curY-1));
				dickPixX.add(curX);
				dickPixY.add(curY-1);
			}
		}
		processed[curY][curX] = true;
	}
	return anim;
}