/**
 * @file Item.cpp
 * @author Maggie Broderick
 */

#include "pch.h"
#include "Item.h"
#include "Game.h"

using namespace std;

/**
 * Constructor.
 * @param game The game this item is part of.
 */
Item::Item(Game* game) : mGame(game)
{
}

/**
 * Destructor.
 */
Item::~Item()
{
}
