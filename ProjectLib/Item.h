/**
 * @file Item.h
 * @author Maggie Broderick
 *
 * Class that describes an Item
 */

#ifndef PROJECT1_ITEM_H
#define PROJECT1_ITEM_H
#include <memory>

// Forward reference allowing Game to draw this
class Game;

/**
 * Base class that describes an Item
 */
class Item
{
private:
    /// The game that item is contained in
    Game *mGame;

    /// X-positons
    double mXPos;

    /// Y-position
    double mYPos;

    /// item image
    std::unique_ptr<wxImage> mItemImage;

    ///item bitmap
    std::unique_ptr<wxBitmap> mItemBitmap;


public:
};


#endif //PROJECT1_ITEM_H