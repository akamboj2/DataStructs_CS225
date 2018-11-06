/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

     MosaicCanvas* theCanvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

    // make a vector of average color for each tile
    // push pair into map
    std::map<Point<3>,TileImage*> mymap;
    vector<Point<3>> avg_color;

    for(unsigned i = 0; i < theTiles.size(); ++i){
      mymap.insert(std::pair<Point<3>,TileImage*>(convertToXYZ(theTiles[i].getAverageColor()),&theTiles[i]));
      avg_color.push_back(convertToXYZ(theTiles[i].getAverageColor()));
    }

    // pass to kd tree constructor
    KDTree<3> tree(avg_color);

    // go through every region of source image using getRows getCols, get average color,
    // find NN, use map to find tile, set tile into canvas
    Point<3> theSourceColor;
    Point<3> closestPoint;
    TileImage* closestTile;

    for(int y = 0; y < theSource.getRows(); y++){
      for(int x = 0; x < theSource.getColumns(); x++){

        theSourceColor = convertToXYZ(theSource.getRegionColor(y, x));
        closestPoint = tree.findNearestNeighbor(theSourceColor);
        closestTile = mymap[closestPoint];

        // resize image
        //closestTile.paste(closestTile.image_, 0, 0, closestTile.getResolution());
        // closestTile.generateResizedImage(0, 0, closestTile.getResolution());

        // set tile
        theCanvas->setTile(y, x, closestTile);

      }
    }

    return theCanvas;
}
