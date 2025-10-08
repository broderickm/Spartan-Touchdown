/**
 * @file Football.h
 * @author Maggie Broderick
 *
 * A class that describes a football
 */

#ifndef PROJECT1_FOOTBALL_H
#define PROJECT1_FOOTBALL_H
#include <memory>
#include "Item.h"

/**
 *  Class that describes a football
 */
class Football : public Item
{
private:
    /// Tells if the football is still alive
    bool mIsDead = false;

    /// Tells if the football is on ground
    bool mIsOnSurface = true;

    /// Tells if the football is moving right
    bool mIsGoingRight = false;

    /// Tells if the football is moving right
    bool mIsGoingLeft = false;

    /// Left image
    std::unique_ptr<wxImage> mLeftImage;

    /// Left bitmap
    std::unique_ptr<wxBitmap> mLeftBitmap;

    /// Right image
    std::unique_ptr<wxImage> mRightImage;

    /// Right bitmap
    std::unique_ptr<wxBitmap> mRightBitmap;

public:
};


#endif //PROJECT1_FOOTBALL_H