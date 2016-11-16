/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

/*
    parameters: SourceImage, vector of TileImages
    return:     ptr to MosaicCanvas
*/
MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
	size_t rows = theSource.getRows();
	size_t cols = theSource.getColumns();

	MosaicCanvas * canvas = new MosaicCanvas(rows, cols);

    // build a kdtree based on theTiles. we will call a
    // NNS on it repeatedly to find the best tile image
    // for a given region.
    vector<Point<3>> pts;

    // create a map, which we will use later to convert the
    // results of our NNS to an image.
    map< Point<3>, TileImage > pointsToTileImageMap;

    for (size_t a=0; a<theTiles.size(); a++)
    {
        RGBAPixel tilePixel = theTiles[a].getAverageColor();
        Point<3> point( tilePixel.red, tilePixel.green, tilePixel.blue );
        pointsToTileImageMap[point] = theTiles[a];
        pts.push_back(point);
    }

    KDTree<3> tilesTree(pts);

    // for every region in sourceimage
    // find the tileimage nearest to region
    // set canvas[row][col] = that best image
    for ( size_t i=0; i < rows ; i++ )
    {
        for ( size_t j=0; j < cols ; j++ )
        {
            // get currentRegionAverage
            RGBAPixel currentRegionAverage = theSource.getRegionColor(i,j);
            Point<3> currentRegionPoint(currentRegionAverage.red,
                currentRegionAverage.green, currentRegionAverage.blue);

            // find the best tile for currentRegionAverage
            Point<3> bestTilesPoint = tilesTree.findNearestNeighbor(currentRegionPoint);
            // okay so now we have a point that represents the best possible tiles,
            // we need to find the image in theTiles that corresponds to it.

            // set the canvas to this tile
            canvas->setTile(i,j,pointsToTileImageMap[bestTilesPoint]);
        }
    }

    return canvas;
}

