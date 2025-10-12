/**
 * @file Platform.cpp
 * @author Annika Valaboju
 *code by sanika kapre
 * Class that describes Platforms
 */

#include "pch.h"
#include "Platform.h"
#include "Game.h"


/**
 * Make a new platform using three images:
 * left edge, middle part, and right edge.
 *
 * @param level the level this platform is in
 * @param leftFile the left platform image file
 * @param middleFile the middle platform image file
 * @param rightFile the right platform image file
 */
Platform::Platform(Level *level,
                   const std::wstring& leftFile,
                   const std::wstring& middleFile,
                   const std::wstring& rightFile)
        : Item(level, middleFile),
          mLeftImage(leftFile, wxBITMAP_TYPE_ANY),
          mMiddleImage(middleFile, wxBITMAP_TYPE_ANY),
          mRightImage(rightFile, wxBITMAP_TYPE_ANY)
{
}

/**
 * Helper function that draws one full row of platform tiles
 * @param graphics the virtual pixel graphics used
 * @param startX the starting x position
 * @param middleTiles the number of middle tiles in the platform
 */
void Platform::DrawPlatformRow(wxGraphicsContext* graphics, double startX, int middleTiles)
{
    double drawY = GetY() - mPlatformHeight / 2;

    // draw left tile
    graphics->DrawBitmap(mLeftImage, startX, drawY, TILE_SIZE, TILE_SIZE);
    startX += TILE_SIZE;

    // draw middle tiles
    for (int i = 0; i < middleTiles; i++)
    {
        graphics->DrawBitmap(mMiddleImage, startX, drawY, TILE_SIZE, TILE_SIZE);
        startX += TILE_SIZE;
    }

    // draw right tile
    graphics->DrawBitmap(mRightImage, startX, drawY, TILE_SIZE, TILE_SIZE);
}

/**
 * Draws this platform on the screen
 * @param graphics the virtual pixel graphics used
 */
void Platform::Draw(wxGraphicsContext* graphics)
{
    if (!graphics)
    {
        return; // nothing to draw on
    }

    // give default width and height if not set
    if (mPlatformWidth <= 0) mPlatformWidth = TILE_SIZE * 3;
    if (mPlatformHeight <= 0) mPlatformHeight = TILE_SIZE;

    // number of middle tiles between left and right ends
    int middleTiles = static_cast<int>(mPlatformWidth / TILE_SIZE) - 2;
    if (middleTiles < 0) middleTiles = 0;

    // where drawing starts so that platform stays centered
    double startX = GetX() - (mPlatformWidth / 2);

    // draw full platform row
    DrawPlatformRow(graphics, startX, middleTiles);
}

/**
 * Sets how big this platform should be
 * @param width the width of the platform
 * @param height the height of the platform
 */
void Platform::SetPlatformSize(double width, double height)
{
    mPlatformWidth = width;
    mPlatformHeight = height;
}