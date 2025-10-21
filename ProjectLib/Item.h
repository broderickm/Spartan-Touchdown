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

class Football;
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
    virtual void OnCollide(Football* football){}
    virtual bool IsGoal() const {return false;}
    /// Disable default constructor
    Item() = delete;

    Item(Level* level, const std::wstring& filename);

    // Destructor.
    virtual ~Item()= default;

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
     * Draw this item on the screen.
     * @param graphics The wxWidgets graphics context to draw on.
     */
    virtual void Draw(wxGraphicsContext* graphics);

    /**
     * Update the item
     * @param elapsed Time elapsed since last update in seconds
     */
    virtual void Update(double elapsed) {}

    virtual void XmlLoad(wxXmlNode* node);

    /**
     * Get the width of this item in pixels.
     * @return The item’s width in pixels.
     */
    virtual double GetWidth() const { return mItemBitmap->GetWidth(); }

    /**
     * Get the height of this item in pixels.
     * @return The item’s height in pixels.
     */
    virtual double GetHeight() const { return mItemBitmap->GetHeight(); }

    /**
     * Set a custom width for this item.
     * @param wid The new width in pixels.
     */
    virtual void SetCustomWidth(double wid){}

    /**
     * Set a custom height for this item.
     * @param hit The new height in pixels.
     */
    virtual void SetCustomHeight(double hit){}

    /**
     * Check if this item is solid (blocks movement).
     * @return True if solid, false otherwise.
     */
    virtual bool IsSolid() const { return false; }
};


#endif //PROJECT1_ITEM_H