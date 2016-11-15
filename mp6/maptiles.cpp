/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
    /**
     * @todo Implement this function!
     */

	int rows = theSource.getRows();
	int cols = theSource.getColumns();

	MosaicCanvas dicksOutForHarambe = new MosaicCanvas(rows, cols);

    return NULL;
}

