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
Wall::Wall(Game* game, const std::wstring& image)
        : Item(game, image),
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
  double currentY = startY - (i * TILE_SIZE);
  graphics->DrawBitmap(mWallImage, drawX, currentY - TILE_SIZE, TILE_SIZE, TILE_SIZE);
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

 // Give default width/height if not set yet
 if (mWallWidth <= 0)  mWallWidth = TILE_SIZE;
 if (mWallHeight <= 0) mWallHeight = TILE_SIZE * 4;

 // Number of vertical tiles to fill the height
 int numTiles = static_cast<int>(mWallHeight / TILE_SIZE);
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