/**
 * @file Level.cpp
 * @author Shlok
 */

#include "pch.h"
#include "Level.h"

using namespace std;

/**
 * Handle a node of type item.
 * @param node XML node
 */
void Level::XmlItem(wxXmlNode *node)
{
    // A pointer for the item we are loading
    shared_ptr<Item> item;

    // We have an item. What type?
    auto type = node->GetAttribute(L"type");
    if (type == L"enemy")
    {
        //item = make_shared<enemy>(this);
    }

    if (type == L"power-up")
    {
        //item = make_shared<powerup>(this);
    }


    if (item != nullptr)
    {
        //item->SetLocation(, );
        mItems.push_back(item);

        item->XmlLoad(node);
    }
}