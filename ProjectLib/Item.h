/**
 * @file Item.h
 * @author Maggie Broderick
 *
 * Class that describes an Item
 */

#ifndef PROJECT1_ITEM_H
#define PROJECT1_ITEM_H

#include <memory>
#include <wx/xml/xml.h>

// Forward reference allowing Game to draw this
class Level;

/**
 * Base class that describes an Item
 */
class Item
{
private:
    /// The level that item is contained in
    Level* mLevel;

    /// X-positons
    double mXPos = 0;

    /// Y-position
    double mYPos = 0;

    /// item image
    std::unique_ptr<wxImage> mItemImage;

    ///item bitmap
    std::unique_ptr<wxBitmap> mItemBitmap;

public:
    /// Disable default constructor
    Item() = delete;

    Item(Level* level, const std::wstring& filename);

    // Destructor.
    virtual ~Item();

    /**
     * Set the item location.
     * @param x X coordinate.
     * @param y Y coordinate.
     */
    void SetLocation(double x, double y) { mXPos = x; mYPos = y;}

    /**
     * Get the X location of the item
     * @return the X positon
     */
    double GetX() const { return mXPos; }

    /**
     * Get the Y location of the item
     * @return the Y position
     */
    double GetY() const { return mYPos; }

    /**
     * Getter for the pointer to the level the item is apart of
     * @return the pointer to the level object
     */
    Level* GetLevel() const { return mLevel; }

    /**
     * Getter for the pointer to the bitmap representing this item
     * @return the pointer to the bitmap
     */
    wxBitmap* GetBitmap() const { return mItemBitmap.get(); }

    /**
     * Setter for the x position
     * @param x position on the x-axis
     */
    void SetX(double x){mXPos = x;}

    /**
     * Setter for the y position
     * @param y position on the y-axis
     */
    void SetY(double y){mYPos = y;}

    /**
     * Initialize the item
     */
    virtual void Initialize() {}

    virtual bool HitTest(int x, int y);

    /**
     * Draws the item on the screen.
     * Derived classes (like Platform, Wall, Coin, GoalPost) will override this.
     * @param graphics The graphics context to draw on
     */

    /// added default implementation to draw, can be overriden by future classes if necessary
    /// but honestly everything draws the same so I'm not sure it'll need to be overridden
    virtual void Draw(wxGraphicsContext* graphics);

    /**
     * Update the item
     * @param elapsed Time elapsed since last update in seconds
     */
    virtual void Update(double elapsed) {}

    virtual void XmlLoad(wxXmlNode* node);

    /// Get width of the item
    virtual double GetWidth() const { return mItemBitmap->GetWidth(); }

    /// Get height of the item
    virtual double GetHeight() const { return mItemBitmap->GetHeight(); }

    /// set image width  for types with custom width and height ( platform, wall )
    virtual void SetCustomWidth(double wid){}

    /// set image custom height for types with custom width and height ( platform, wall )
    virtual void SetCustomHeight(double hit){}

    /// Whether this item blocks physics (platforms, walls, etc)
    virtual bool IsSolid() const { return false; }
};


#endif //PROJECT1_ITEM_H