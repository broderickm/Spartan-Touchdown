/**
 * @file MovingItem.cpp
 * @author Shlok
 */

#include "pch.h"
#include "MovingItem.h"



/**
 * Constructor
 * @param level the level we are adding this enemy to
 * @param filename Filename for the image we use
 */
MovingItem::MovingItem(Level* level, const std::wstring& filename): Item(level,filename)
{

}

/**
 * Handles the loading of our moving item and attributes from an XML format
 * @param node pointer to a moving item
 */
void MovingItem::XmlLoad(wxXmlNode *node)
{
    Item::XmlLoad(node);

    node->GetAttribute(L"speedX", L"0").ToDouble(&mSpeedX);
    node->GetAttribute(L"speedY", L"0").ToDouble(&mSpeedY);
}
