/**
 * @file Item.cpp
 * @author Maggie Broderick
 */

#include "pch.h"
#include "Item.h"
#include "Game.h"

using namespace std;

/**
 * Destructor.
 */
Item::~Item() = default;

/**
 * Constructor.
 * @param game The game this item is part of.
 */
Item::Item(Game* game, const std::wstring& filename)
{
    mItemImage = std::make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
    if (mItemImage && mItemImage->IsOk())
    {
        mItemBitmap = std::make_unique<wxBitmap>(*mItemImage);
    }
}


