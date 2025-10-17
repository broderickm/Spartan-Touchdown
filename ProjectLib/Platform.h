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

    /// Image used for the middle section of the platform
    wxBitmap mMiddleImage;

    /// Image used for the right edge of the platform
    wxBitmap mRightImage;

    /// width of the platform
    double mPlatformWidth = 0;

    /// Height of the platform in pixels
    double mPlatformHeight = 0;

    /// Each small tile in the platform is 64 pixels wide
    double TILE_SIZE = 0;

    /**
     * Draw one full row of platform tiles.
     * @param graphics The wxWidgets graphics context to draw with.
     * @param startX The starting X coordinate for the row.
     * @param middleTiles The number of middle tiles to draw.
     */
    void DrawPlatformRow(wxGraphicsContext* graphics, double startX, int middleTiles);



public:
    /**
     * Construct a platform object.
     * @param level The level this platform belongs to.
     * @param leftFile Image file for the left edge.
     * @param middleFile Image file for the middle section.
     * @param rightFile Image file for the right edge.
     */
    Platform(Level *level,
             const std::wstring& leftFile,
             const std::wstring& middleFile,
             const std::wstring& rightFile);

    /// Draw this platform on the screen
    void Draw(wxGraphicsContext* graphics) override;

    /// Set how big this platform should be
    void SetPlatformSize(double width, double height);


    /**
     * Set a custom height for the platform.
     * @param hit The new height in pixels.
     */
    void SetCustomHeight(double hit) override;

    /**
     * Set a custom width for the platform.
     * @param wid The new width in pixels.
     */
    void SetCustomWidth(double wid) override;

    /**
    * Get the width of the platform.
    * @return The platform’s width in pixels
    */
    double GetWidth() const override { return mPlatformWidth; }

    /**
    * Get the height of the platform.
    * @return The platform’s height in pixels
    */
    double GetHeight() const override { return mPlatformHeight; }

    /**
     * Determine whether the platform is solid (blocks movement).
     * @return True if solid, false otherwise
     */
    bool IsSolid() const override { return true; }
};


#endif //PROJECT1_PLATFORM_H