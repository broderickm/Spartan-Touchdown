/**
 * @file MovingItem.cpp
 * @author Shlok
 */

#include "pch.h"
#include "MovingItem.h"



/**
 * Constructor
 * @param game, the game we are adding this enemy to
 * @param filename Filename for the image we use
 */
MovingItem::MovingItem(Game* game, const std::wstring& filename): Item(game,filename)
{

}
