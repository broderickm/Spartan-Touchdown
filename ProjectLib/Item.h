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
    /**
     * Constructor.
     * @param game The game this item is part of.
     */
    Item(Game* game);

    /// Destructor.
    virtual ~Item();

    /**
     * Set the item location.
     * @param x X coordinate.
     * @param y Y coordinate.
     */
    void SetLocation(double x, double y);

    /// Get the X location of the item
    double GetX() const { return mXPos; }

    /// Get the Y location of the item
    double GetY() const { return mYPos; }

    /// Get the game this item belongs to
    Game* GetGame() const { return mGame; }

    /**
     * Initialize the item .
     */
    virtual void Initialize() {}
};


#endif //PROJECT1_ITEM_H