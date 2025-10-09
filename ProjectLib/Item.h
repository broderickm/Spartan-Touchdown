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
    /// function hitTest checks whether an item was hit when coordinates are passed in.
    virtual bool HitTest(int x, int y);

    /// function getX, getY
    /// ive added these getter functions to get the X and Y of the current position for the hitest function
    /// @venkata pandiri
    int GetX(){return mXPos;}
    int GetY(){return mYPos;}

};


#endif //PROJECT1_ITEM_H