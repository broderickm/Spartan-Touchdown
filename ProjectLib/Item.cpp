/**
 * @file Item.cpp
 * @author Maggie Broderick
 */

#include "pch.h"
#include "Item.h"

#include <wx/graphics.h>

#include "Game.h"

using namespace std;

/**
 * Destructor.
 */
Item::~Item() = default;

/**
 * Constructor.
 * @param level The level this item is part of
 * @param filename The filename used for the image
 */
Item::Item(Level *level, const std::wstring& filename)
{
    mItemImage = std::make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
    if (mItemImage && mItemImage->IsOk())
    {
        mItemBitmap = std::make_unique<wxBitmap>(*mItemImage);
    }
}

/**
 * Test to see if we hit this object when given a x,y value
 * @param x X position to test
 * @param y Y position to test
 * @return true if hit.
 */
bool Item::HitTest(int x, int y)
{
    /// gets the width of the bitmap
    double wid = mItemBitmap->GetWidth();
    /// gets the height of the bitmap
    double hit = mItemBitmap->GetHeight();


    /// testX finds the x position relative to the top left corner of the image.
    /// testY finds the y position relative to the top left corner of the image.
    /// top left corner cords: (getX() - wid/2, getY() - hit/2), so x - (getx() - wid/2) = x - getx() + wid/2
    /// same logic applies for the y cordinate
    double testX = x - GetX() + wid/2;
    double testY = y - GetY() + hit/2;

    /// check if x and y are outside the image
    if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
    {
        /// we are outside the image.
        return false;
    }


    /// make sure the position we hit relative to the left corner of the image is not transparent.
    return !mItemImage->IsTransparent((int)testX, (int)testY);
}


/**
 * Load the attributes for an item node.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * @param node The Xml node we are loading the item from
 */
void Item::XmlLoad(wxXmlNode *node)
{
    node->GetAttribute(L"x", L"0").ToDouble(&mXPos);
    node->GetAttribute(L"y", L"0").ToDouble(&mYPos);
}