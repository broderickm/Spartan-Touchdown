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
 * Construct a platform object.
 * @param level The level this platform belongs to.
 * @param leftFile Image file for the left edge.
 * @param middleFile Image file for the middle section.
 * @param rightFile Image file for the right edge.
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
 * Draw one full row of platform tiles.
 * @param graphics The wxWidgets graphics context to draw with.
 * @param startX The starting X coordinate for the row.
 * @param middleTiles The number of middle tiles to draw.
 */
void Platform::DrawPlatformRow(wxGraphicsContext* graphics, double startX, int middleTiles)
{
    double drawY = GetY() - mPlatformHeight / 2.0f;

    // draw left tile
    graphics->DrawBitmap(mLeftImage, startX, drawY, mTileSize, mTileSize);
    startX += mTileSize;

    // draw middle tiles
    for (int i = 0; i < middleTiles; i++)
    {
        graphics->DrawBitmap(mMiddleImage, startX, drawY, mTileSize, mTileSize);
        startX += mTileSize;
    }

    // draw right tile
    graphics->DrawBitmap(mRightImage, startX, drawY, mTileSize, mTileSize);
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

    mTileSize = mLeftImage.GetWidth();

    // give default width and height if not set
    if (mPlatformWidth <= 0) mPlatformWidth = mTileSize * 3;
    if (mPlatformHeight <= 0) mPlatformHeight = mTileSize;

    // number of middle tiles between left and right ends
    int middleTiles = mPlatformWidth / mTileSize - 2;
    if (middleTiles < 0) middleTiles = 0;

    // where drawing starts so that platform stays centered
    double startX = GetX() - (mPlatformWidth / 2.0f);

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

void Platform::SetCustomHeight(double hit)
{
    mPlatformHeight = hit;
}

void Platform::SetCustomWidth(double wid)
{
    mPlatformWidth = wid;
}
