/**
* @file Wall.h
 * @author Sanika Kapre
 *
 * Class that describes caution wall
 */

#ifndef WALL_H
#define WALL_H

#include "Item.h"
#include <wx/graphics.h>

/**
 * Class that describes the walls
 */
class Wall : public Item
{

private:
 /// The wall tile image (one segment of the wall)
 wxBitmap mWallImage;

 /// Total width aof this wall (in virtual pixels)
 double mWallWidth = 0;

 /// Default height of the wall
 double mWallHeight = 0;

 /// Each tile is 64 px tall/wide
 double TILE_SIZE = 64;

 /**
  * Helper that draws the full column of wall tiles.
  * @param graphics Graphics context used for drawing
  * @param startY   Where to start drawing vertically
  * @param numTiles How many tiles tall the wall is
  */
 void DrawWallColumn(wxGraphicsContext* graphics, double startY, int numTiles);

public:
 /**
     * Constructor.
     * @param level  The level this wall belongs to
     * @param image The filename of the wall image
     */
 Wall(Level *level, const std::wstring& image);

 /**
  * Draw the wall on the screen.
  * @param graphics The graphics context used to draw
  */
 void Draw(wxGraphicsContext* graphics) override;

 /**
  * Set the size of this wall.
  * @param width  Total width of the wall
  * @param height Total height of the wall
  */
 void SetWallSize(double width, double height);



 /// Set the custom height
 void SetCustomHeight(double hit) override;


 /// set the custom width
 void SetCustomWidth(double wid) override;

 /// Override to return the actual drawn width
 double GetWidth() const override { return mWallWidth; }

 /// Override to return the actual drawn height
 double GetHeight() const override { return mWallHeight; }

 bool IsSolid() const override { return true; }
};



#endif //WALL_H
