/**
* @file SilverCoin.cpp
 * @author Sanika Kapre
 *
 * Class that describes silver coins
 */

using namespace std;

#include "pch.h"
#include "SilverCoin.h"

/**
 * Silver coin constructor
 * @param level the level the coin is in
 */
SilverCoin::SilverCoin(Level *level)
        : Coin(level, L"images/coin10.png", 10)
{
}