/**
* @file Wall.cpp
 * @author Sanika Kapre
 *
 * Class that describes  wall
 */

#include "pch.h"
#include "Wall.h"
#include "Game.h"

/**
 * Make a new wall using one image that repeats vertically.
 */
Wall::Wall(Level *level, const std::wstring& image)
        : Item(level, image),
          mWallImage(image, wxBITMAP_TYPE_ANY)
{
}

/**
 * function that draws one full column of wall tiles.
 */
void Wall::DrawWallColumn(wxGraphicsContext* graphics, double startY, int numTiles)
{
 double drawX = GetX() - mWallWidth / 2;

 // Draw tiles upward from the bottom
 for (int i = 0; i < numTiles; i++)
 {
      double currentY = startY - (i * mTileSize);
      graphics->DrawBitmap(mWallImage, drawX, currentY - mTileSize, mTileSize, mTileSize);
 }
}

/**
 * Draws this wall on the screen.
 */
void Wall::Draw(wxGraphicsContext* graphics)
{
 if (graphics == nullptr)
 {
  return; // nothing to draw on
 }

 mTileSize = mWallImage.GetWidth();

 // Give default width/height if not set yet
 if (mWallWidth <= 0)
 {
      mWallWidth = mTileSize;
 }

 if (mWallHeight <= 0)
 {
      mWallHeight = mTileSize * 4;
 }

 // Number of vertical tiles to fill the height
 int numTiles = static_cast<int>(mWallHeight / mTileSize);
 if (numTiles < 1) numTiles = 1;

 // Start from the bottom so it stays centered on GetY()
 double startY = GetY() + (mWallHeight / 2);

 // Draw the column of wall tiles
 DrawWallColumn(graphics, startY, numTiles);

}

/**
 * Set the wall size
 */
void Wall::SetWallSize(double width, double height)
{
 mWallWidth = width;
 mWallHeight = height;
}

/**
 * Set a custom wall height.
 * @param hit The new height in pixels
 */
void Wall::SetCustomHeight(double hit)
{
  mWallHeight = hit;
}

/**
* Set a custom wall width.
* @param wid The new width in pixels
*/
void Wall::SetCustomWidth(double wid)
{
  mWallWidth = wid;
}
