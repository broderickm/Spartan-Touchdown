/**
 * @file Platform.h
 * @author file made by -Annika Valaboju,
 * adding code- sanika kapre
 *
 *
 */

#ifndef PROJECT1_PLATFORM_H
#define PROJECT1_PLATFORM_H

#include "Item.h"
#include <wx/graphics.h>

// #include <string>

/**
 * Platform item that can be grass, metal or snow
 * Platforms can be left, middle, right
 */
class Platform : public Item
{
private:
    /// The three parts of a platform: left, middle, and right images
    wxBitmap mLeftImage;
    wxBitmap mMiddleImage;
    wxBitmap mRightImage;

    /// width and height of the platform
    double mPlatformWidth = 0;
    double mPlatformHeight = 0;

    /// Each small tile in the platform is 64 pixels wide
    static const int TILE_SIZE = 64;

    /**
     * Draws one row of tiles starting from a given X position.
     * @param graphics The drawing surface
     * @param startX Where to start drawing
     * @param numberOfMiddleTiles How many middle tiles to draw
     */
    void DrawPlatformRow(wxGraphicsContext* graphics, double startX, int middleTiles);



public:
    /**
     * Constructor for a platform.
     * @param game The game that owns this platform
     * @param leftFile The left edge image
     * @param middleFile The middle section image
     * @param rightFile The right edge image
     */
    Platform(Game* game,
             const std::wstring& leftFile,
             const std::wstring& middleFile,
             const std::wstring& rightFile);

    /// Draw this platform on the screen
    void Draw(wxGraphicsContext* graphics) override;

    /// Set how big this platform should be
    void SetPlatformSize(double width, double height);
};


#endif //PROJECT1_PLATFORM_H